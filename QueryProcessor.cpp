#include "QueryProcessor.h"

void QueryProcessor::processQuery(string entireQuery) {
    vector<string> query;
    istringstream iss(entireQuery);
    string word;
    string sub;

    while (iss >> word) {
        if (word.length() >= 7 && word.substr(0, 7) == "PERSON:") {
            persons.push_back(setLowerCase(word.substr(7)));
        } else if (word.length() >= 4 && word.substr(0, 4) == "ORG:") {
            orgs.push_back(word.substr(4));
        } else if (word[0] == '-') {
            sub = word.substr(1);
            Porter2Stemmer::stem(sub);
            notWords.push_back(setLowerCase(sub));
        } else {
            Porter2Stemmer::stem(word);
            words.push_back(setLowerCase(word));
        }
    }
}

string QueryProcessor::setLowerCase(string currWord) {
    string temp = "";
    for (char &c : currWord) {
        c = tolower(c);
        temp = temp + c;
    }
    return temp;
}

map<string, double> QueryProcessor::combineWordMaps(map<string, double> map1, map<string, double> map2) {
    map<string, double> sharedMap;
    for (auto &pair : map1) {
        for (auto &nextPair : map2) {
            if (pair.first == nextPair.first) {
                sharedMap.insert(make_pair(pair.first, ((pair.second + nextPair.second) / 2)));
                break;
            }
        }
    }

    return sharedMap;
}

void QueryProcessor::removeNotWordFiles(map<string, double> &combinedGoodWord, map<string, double> notWords) {
    for (auto &pair : notWords) {
        for (auto &nextPair : combinedGoodWord) {
            if (pair.first == nextPair.first) {
                combinedGoodWord.erase(nextPair.first);
                break;
            }
        }
    }
}

map<string, double> QueryProcessor::combineOrg(map<string, double> wordRankMap, vector<string> orgPaths) {
    map<string, double> wordRankOrgMap;
    for (auto &pair : wordRankMap) {
        for (auto &it : orgPaths) {
            if (pair.first == it) {
                wordRankOrgMap.insert(pair);
            }
        }
    }
    return wordRankOrgMap;
}

map<string, double> QueryProcessor::combinePersons(map<string, double> wordRankMap, vector<string> personPaths) {
    map<string, double> wordRankPersonMap;
    for (auto &pair : wordRankMap) {
        for (auto &it : personPaths) {
            if (pair.first == it) {
                wordRankPersonMap.insert(pair);
            }
        }
    }
    return wordRankPersonMap;
}

void QueryProcessor::clearVectors() {
    words.clear();
    notWords.clear();
    persons.clear();
    orgs.clear();
}
