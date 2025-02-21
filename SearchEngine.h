#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H
#include "IndexHandler.h"
#include "QueryProcessor.h"
#include "UserInterface.h"

using namespace std;

// this class will
// Use all the class and their logic (Index Handler, Query Processor, and UI)
// In order to perform a search and return the search to the UI
// UI will be the TERMINAL
class SearchEngine {
   private:
    UserInterface UI;
    QueryProcessor QP;
    IndexHandler IH;
    vector<string> words, persons, orgs, notWords;
    chrono::nanoseconds timeIndexFromDir;
    chrono::nanoseconds timeIndexFromFile;
    chrono::nanoseconds timeProcessQuery;
    chrono::time_point<chrono::high_resolution_clock> start, end;
    int totalNodesAvlWordsTree = 0;
    int totalArticlesInIndex = 0;

    vector<map<string, double>> wordMapsVector, notWordMapsVector;
    vector<vector<string>> personFilePaths, orgFilePaths;

    string userIntChoice;
    string userStringInput;

   public:
    void startUI();
    void indexFromSS(string filePath);
    void wordIndexIntoSSFromFile(string filePath);
    void orgPerIndexIntoSSFromFile(string filePath, int whichFile);
    void queryThingy(string wholeQuery);
};

#endif