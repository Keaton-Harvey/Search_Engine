#define CATCH_CONFIG_MAIN
#include "AvlTreeMap.h"
#include "IndexHandler.h"
#include "catch2/catch.hpp"

using namespace std;

TEST_CASE("Create a tree and output it") {
    AvlTreeMap<string, vector<string>> stringVecStringTree;
    map<string, double> myMap;
    AvlTreeMap<string, map<string, double>> AvlMapMap;

    // works for vectors
    stringVecStringTree.insert("apple", {"hi", "hello", "hola"});
    stringVecStringTree.insert("avocado", {"hi", "hello", "hola"});
    stringVecStringTree.insert("pear", {"hi", "hello", "hola"});
    stringVecStringTree.insert("orange", {"hi", "hello", "hola"});
    stringVecStringTree.insert("stawberry", {"hi", "hello", "hola"});
    stringVecStringTree.insert("grapefruit", {"hi", "hello", "hola"});
    stringVecStringTree.insert("alzzzzzz", {"hi", "hello", "hola"});

    stringVecStringTree.saveVectorAVLTree("../build/testOutput2.txt");
    ifstream file("../build/testOutput2.txt");
    stringstream buffer;
    buffer << file.rdbuf();
    string fileContent = buffer.str();
    string expectedContent =
        "orange hi hello hola\n"
        "avocado hi hello hola\n"
        "apple hi hello hola\n"
        "alzzzzzz hi hello hola\n"
        "grapefruit hi hello hola\n"
        "pear hi hello hola\n"
        "stawberry hi hello hola\n";
    REQUIRE(fileContent == expectedContent);

    myMap.insert(make_pair("/this/is/where/the/path/would/be", 0.003428931));
    myMap.insert(make_pair("/this/is/where/the/path/would", 0.703428931));
    myMap.insert(make_pair("/this/is/where/the/path", 0.203428931));
    myMap.insert(make_pair("/this/is/where/the", 0.1));

    AvlMapMap.insert("apple", myMap);
    AvlMapMap.insert("banana", myMap);

    AvlMapMap.saveMapAVLTree("../build/testOutput.txt");
    ifstream file2("../build/testOutput.txt");
    stringstream buffer2;
    buffer2 << file.rdbuf();
    string fileContent2 = buffer2.str();

    string expectedContent2 =
        "apple /this/is/where/the 0.1 /this/is/where/the/path 0.203429 /this/is/where/the/path/would 0.703429 /this/is/where/the/path/would/be 0.00342893\n"
        "banana /this/is/where/the 0.1 /this/is/where/the/path 0.203429 /this/is/where/the/path/would 0.703429 /this/is/where/the/path/would/be 0.00342893\n";
    REQUIRE(fileContent2 == expectedContent2);
}
