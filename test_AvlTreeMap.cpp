#define CATCH_CONFIG_MAIN
#include "AvlTreeMap.h"
#include "catch2/catch.hpp"

using namespace std;

TEST_CASE("Check if AvlTreeMap works", "[AvlTreeMap]") {
    AvlTreeMap<string, int> testTree;

    SECTION("Checking the insert, isEmpty and contains") {
        REQUIRE(testTree.isEmpty());

        testTree.insert("apple", 6);
        testTree.insert("orange", 4);
        testTree.insert("banana", 2);

        REQUIRE(!testTree.isEmpty());
        REQUIRE(testTree.contains("apple"));
        REQUIRE(testTree.contains("banana"));
        REQUIRE(testTree.contains("orange"));
        REQUIRE(!testTree.contains("kiwi"));
    }

    SECTION("Checking prettyprint") {
        testTree.insert("apple", 5);
        testTree.insert("avocado", 9);
        testTree.insert("pear", 2);
        testTree.insert("orange", 1);
        testTree.insert("stawberry", 8);
        testTree.insert("grapefruit", 6);
        testTree.insert("alzzzzzz", 3);

        testTree.prettyPrintTree();
    }

    SECTION("Find") {
        AvlTreeMap<string, vector<string>> test;
        test.insert("apple", {"hi", "hello", "hola"});

        const auto* result = test.find("apple");
        REQUIRE(result != nullptr);
        REQUIRE(*result == vector<string>{"hi", "hello", "hola"});

        const auto* notFoundResult = test.find("banana");
        REQUIRE(notFoundResult == nullptr);
    }

#ifdef DEBUG
    SECTION("Check Balance") {
        AvlTreeMap<string, vector<string>> tree;
        tree.insert("apple", {"hi", "hello", "hola"});
        tree.insert("banana", {"hi", "hello", "hola"});
        tree.insert("orange", {"hi", "hello", "hola"});

        // Will throw if the tree is not balanced
        tree.check_balance();
    }
#endif
}