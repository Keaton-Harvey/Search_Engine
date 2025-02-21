#ifndef AVLTREEMAP_H
#define AVLTREEMAP_H

// we define DEBUG in the main function.
#define DEBUG

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <unordered_set>

using namespace std;

template <typename KeyType, typename ValueType>
class AvlTreeMap {
   private:
    struct AvlNode {
        KeyType word;
        ValueType documents;
        AvlNode *left;
        AvlNode *right;
        int height;  // AVL tree: keeping track of the height is the difference to a unbalanced binary search tree

        AvlNode(const KeyType &theKey, const ValueType &theValue, AvlNode *lt, AvlNode *rt, int h)
            : word{theKey}, documents{theValue}, left{lt}, right{rt}, height{h} {}
    };

    AvlNode *root;

    static const int ALLOWED_IMBALANCE = 1;  // 1 is the default; more will make balancing cheaper
                                             // but the search less efficient.

   public:
    AvlTreeMap() : root{nullptr} {
    }

    AvlTreeMap(const AvlTreeMap &rhs) : root{nullptr} {
        root = clone(rhs.root);
    }

    ~AvlTreeMap() {
        makeEmpty();
    }

    AvlTreeMap &operator=(const AvlTreeMap &rhs) {
        if (this == &rhs) {
            return *this;
        }
        makeEmpty();
        root = clone(rhs.root);
        return *this;
    }

    bool contains(const KeyType &word) const {
        return contains(word, root);
    }

    ValueType *find(const KeyType &word) const {
        return find(word, root);
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void prettyPrintTree() const {
        prettyPrintTree("", root, false);
    }

    void makeEmpty() {
        makeEmpty(root);
    }

    void insert(const KeyType &word, const ValueType &documents) {
        insert(word, documents, root);
    }

    void saveVectorAVLTree(string filePath) {
        ofstream outFile;
        outFile.open(filePath);
        if (outFile.is_open()) {
            saveVector(root, outFile);
            outFile.close();
            std::cout << "AVL tree saved to " << filePath << std::endl;
        } else {
            std::cerr << "Error opening file for writing." << std::endl;
        }
    }

    void saveMapAVLTree(string filePath) {
        ofstream outFile;
        outFile.open(filePath);
        if (outFile.is_open()) {
            saveMap(root, outFile);
            outFile.close();
            cout << "AVL tree of map saved to " << filePath << endl;
        } else {
            cerr << "Error opening file for writing in saveMapAVLTree" << endl;
        }
    }

#ifdef DEBUG

    int check_balance() {
        return check_balance(root);
    }
#endif

   private:
    void insert(const KeyType &key, const ValueType &value, AvlNode *&t) {
        if (t == nullptr) {
            t = new AvlNode{key, value, nullptr, nullptr, 0};
            return;  // a single node is always balanced
        }

        if (key < t->word)
            insert(key, value, t->left);
        else if (t->word < key)
            insert(key, value, t->right);
        else {
        }  // Duplicate; do nothing

        balance(t);
    }

    bool contains(const KeyType &key, AvlNode *t) const {
        if (t == nullptr)
            return false;

        if (key == t->word)
            return true;  // Element found.
        else if (key < t->word)
            return contains(key, t->left);
        else
            return contains(key, t->right);
    }

    ValueType *find(const KeyType &key, AvlNode *t) const {
        if (t == nullptr)
            return nullptr;

        if (key == t->word)
            return &t->documents;  // Element found.
        else if (key < t->word)
            return find(key, t->left);
        else
            return find(key, t->right);
    }

    void makeEmpty(AvlNode *&t) {
        if (t == nullptr)
            return;

        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = nullptr;
    }

    AvlNode *clone(AvlNode *t) const {
        if (t == nullptr)
            return nullptr;

        return new AvlNode{t->word, t->documents, clone(t->left), clone(t->right), t->height};
    }

    void prettyPrintTree(const std::string &prefix, const AvlNode *node, bool isRight) const {
        if (node == nullptr)
            return;

        std::cout << prefix;

        std::cout << (isRight ? "├──" : "└──");
        // print the value of the node
        std::cout << node->word << std::endl;

        // enter the next tree level - left and right branch
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->right, true);
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->left, false);
    }

    int height(AvlNode *t) const {
        return t == nullptr ? -1 : t->height;
    }

    void balance(AvlNode *&t) {
        // special case: empty tree
        if (t == nullptr)
            return;

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)  // unbalancing insertion was left
        {
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t);  // case 1 (outside)
            else
                doubleWithLeftChild(t);                                     // case 2 (inside)
        } else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)  // unbalancing insertion was right
        {
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t);  // case 4 (outside)
            else
                doubleWithRightChild(t);  // case 3 (inside)
        }
        // else ... no imbalance was created

        // update height
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    void saveVector(AvlNode *node, std::ofstream &outFile) {
        if (node == nullptr) {
            return;
        } else {
            outFile << node->word;
            outFile << " ";
            for (auto &path : node->documents) {
                outFile << path << " ";
            }
            outFile << endl;
        }

        saveVector(node->left, outFile);
        saveVector(node->right, outFile);
    }

    void saveMap(AvlNode *node, ofstream &outFile) {
        if (node == nullptr) {
            return;
        } else {
            outFile << node->word;
            for (const auto &pair : node->documents) {  // for each pair in the map linked to the word found in node->word
                const KeyType &path = pair.first;
                double relScore = pair.second;
                outFile << " " << path << " " << relScore;
            }
            outFile << endl;

            saveMap(node->left, outFile);
            saveMap(node->right, outFile);
        }
    }

    int max(int lhs, int rhs) const {
        return lhs > rhs ? lhs : rhs;
    }

    void rotateWithLeftChild(AvlNode *&k2) {
#ifdef DEBUG

#endif

        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
#ifdef DEBUG
#endif
    }

    void rotateWithRightChild(AvlNode *&k1) {
#ifdef DEBUG

#endif

        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
#ifdef DEBUG
#endif
    }

    void doubleWithLeftChild(AvlNode *&k3) {
#ifdef DEBUG
        // cout << "doubleWithLeftChild" << endl;
#endif
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    void doubleWithRightChild(AvlNode *&k1) {
#ifdef DEBUG
        // cout << "doubleWithRightChild" << endl;
#endif
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }

#ifdef DEBUG

    int check_balance(AvlNode *node) {
        if (node == nullptr) {
            return -1;
        }

        // use LRN traversal to check the balance of the tree
        int lHeight = check_balance(node->left) + 1;
        int rHeight = check_balance(node->right) + 1;

        if (std::abs(lHeight - rHeight) > ALLOWED_IMBALANCE) {
            throw std::runtime_error("tree is not balanced in node with key " + node->word);
        }

        int trueNodeHeight = std::max(lHeight, rHeight);

        if (trueNodeHeight != node->height) {
            throw std::runtime_error("node does not have correct height value in node with key " + node->word + ".");
        }

        return trueNodeHeight;
    }
#endif
};

#endif