#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <unordered_set>

#include "AvlTreeMap.h"
#include "DocumentParser.h"

// RapidJSON headers we need for our parsing.
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

using namespace rapidjson;
using namespace std;

class IndexHandler {
   private:
    map<string, double> wordsAndRelRank;
    int totalNodes = 0;
    int totalArticles = 0;

    AvlTreeMap<string, map<string, double>> words;
    AvlTreeMap<string, vector<string>> persons;
    AvlTreeMap<string, vector<string>> organizations;
    DocumentParser myParser;

   public:
    void createTheTreeMaps(string folder);
    void saveTreeWithVectorToFile(string fileName, string fileName2);
    void saveTreeWithMapToFile(string fileName);
    void createWordsTreeFromFile(string fileName);
    void createOrgPerTreeFromFile(string fileName, int which);

    int getTotalArticles() {
        return totalArticles;
    }

    int getTotalNodesWordsTree() {
        return totalNodes;
    }

    map<string, double> getAWordsMap(string wordToFind);
    vector<string> getVectorOfOrgFilePaths(string orgName);
    vector<string> getVectorOfPeopleFilePaths(string personName);
};

#endif