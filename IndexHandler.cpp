#include "IndexHandler.h"

void IndexHandler::createTheTreeMaps(string folder) {
    words.makeEmpty();
    persons.makeEmpty();
    organizations.makeEmpty();

    int totalArtsTemp = 0;
    int totalNodTemp = 0;

    auto it = filesystem::recursive_directory_iterator(folder);

    for (const auto& entry : it) {
        string tempTester = (entry.path().string());

        if (entry.is_regular_file() && entry.path().extension().string() == ".json") {
            totalArtsTemp++;
            myParser.parser(entry.path().string());
            wordsAndRelRank = myParser.getWordsAndRelRank();
            myParser.clearWordsAndRelRank();

            for (auto pair : wordsAndRelRank) {
                map<string, double>* word = words.find(pair.first);
                if (word == nullptr) {
                    // insert for first time
                    map<string, double> pathAndRelRank;
                    pathAndRelRank[(entry.path().string())] = pair.second;
                    words.insert(pair.first, pathAndRelRank);
                    totalNodTemp++;
                } else {
                    // edit map to insert the new docID and freq
                    (*word)[(entry.path().string())] = pair.second;
                }
            }

            ifstream input(entry.path().string());
            if (!input.is_open()) {
                cerr << "cannot open file: " << entry.path().string() << endl;
                return;
            }

            IStreamWrapper isw(input);
            Document d;
            d.ParseStream(isw);

            auto peoples = d["entities"]["persons"].GetArray();
            for (auto& p : peoples) {
                // add each name to map
                string temp = p["name"].GetString();

                istringstream iss(temp);
                vector<string> namesBrokenApart;
                string currName;

                while (iss >> currName) {
                    namesBrokenApart.push_back(currName);
                    vector<string>* person = persons.find(currName);

                    if (person == nullptr) {
                        // this person is already in the map
                        vector<string> paths;
                        paths.push_back(entry.path().string());
                        persons.insert(currName, paths);

                    } else {
                        // the person is being added for the first time
                        for (auto path : *person) {
                            if (find((*person).begin(), (*person).end(), path) == (*person).end()) {
                                (*person).push_back(entry.path().string());
                            }
                        }
                    }
                }
            }

            // do same as people but for orgs

            auto orggs = d["entities"]["organizations"].GetArray();
            for (auto& o : orggs) {
                string temp = o["name"].GetString();

                istringstream iss(temp);
                vector<string> orgsBrokenApart;
                string currOrgName;

                while (iss >> currOrgName) {
                    orgsBrokenApart.push_back(currOrgName);
                    vector<string>* org = organizations.find(currOrgName);

                    if (org == nullptr) {
                        vector<string> paths;
                        paths.push_back(entry.path().string());
                        organizations.insert(currOrgName, paths);
                    } else {
                        for (auto path : *org) {
                            if (find((*org).begin(), (*org).end(), path) == (*org).end()) {
                                (*org).push_back(entry.path().string());
                            }
                        }
                    }
                }
            }
        }
    }
    totalArticles = totalArtsTemp;
    totalNodes = totalNodTemp;
}

void IndexHandler::saveTreeWithVectorToFile(string fileName, string fileName2) {
    persons.saveVectorAVLTree(fileName);
    organizations.saveVectorAVLTree(fileName2);
}

void IndexHandler::saveTreeWithMapToFile(string fileName) {
    words.saveMapAVLTree(fileName);
}

void IndexHandler::createWordsTreeFromFile(string fileName) {
    words.makeEmpty();
    map<string, double> pathAndScore;

    ifstream fileIn(fileName);
    if (!fileIn.is_open()) {
        cerr << "File could not be open in createTreeMapsFromFile" << endl;
    } else {
        string line;
        string word, path;
        double score;
        while (getline(fileIn, line)) {
            istringstream iss(line);
            iss >> word;

            while (iss >> path >> score) {
                pathAndScore.insert(make_pair(path, score));
            }
            words.insert(word, pathAndScore);
        }
    }
}

void IndexHandler::createOrgPerTreeFromFile(string fileName, int which) {
    persons.makeEmpty();
    organizations.makeEmpty();
    vector<string> orgPerVector;

    ifstream fileIn(fileName);
    if (!fileIn.is_open()) {
        cerr << "File could not be open in createTreeMapsFromFile" << endl;
    } else {
        string line, orgPer, path;
        while (getline(fileIn, line)) {
            istringstream iss(line);
            iss >> orgPer;

            while (iss >> path) {
                orgPerVector.push_back(path);
            }

            if (which == 1) {
                persons.insert(orgPer, orgPerVector);
            } else {
                organizations.insert(orgPer, orgPerVector);
            }
        }
    }
}

map<string, double> IndexHandler::getAWordsMap(string wordToFind) {
    // returns a map of every path and their respective relRank
    map<string, double>* word = words.find(wordToFind);
    map<string, double> mapToReturn = *word;

    return mapToReturn;
}

vector<string> IndexHandler::getVectorOfOrgFilePaths(string orgName) {
    vector<string>* org = organizations.find(orgName);
    vector<string> orgToReturn = *org;
    return orgToReturn;
}

vector<string> IndexHandler::getVectorOfPeopleFilePaths(string personName) {
    vector<string>* person = persons.find(personName);
    vector<string> personToReturn = *person;
    return personToReturn;
}
