#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "porter2_stemmer.h"

using namespace std;

class QueryProcessor {
   private:
    vector<string> words;
    vector<string> persons;
    vector<string> orgs;
    vector<string> notWords;

   public:
    void processQuery(string entireQuery);
    string setLowerCase(string currWord);
    map<string, double> combineWordMaps(map<string, double> map1, map<string, double> map2);
    void removeNotWordFiles(map<string, double>& combinedGoodWord, map<string, double> notWords);
    map<string, double> combineOrg(map<string, double> wordRankMap, vector<string> orgPaths);
    map<string, double> combinePersons(map<string, double> wordRankMap, vector<string> personPaths);

    const vector<string>& getWords() const {
        return words;
    }

    const vector<string>& getPersons() const {
        return persons;
    }

    const vector<string>& getOrgs() const {
        return orgs;
    }

    const vector<string>& getNotWords() const {
        return notWords;
    }
    void clearVectors();
};

#endif