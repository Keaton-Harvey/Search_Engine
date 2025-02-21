#include "SearchEngine.h"

void SearchEngine::startUI() {
    while (true) {
        UI.startUI();
        userIntChoice = UI.getUserChoice();
        userStringInput = UI.getUserInput();

        if (userIntChoice == "1") {
            // create an index (create the trees)
            start = chrono::high_resolution_clock::now();
            IH.createTheTreeMaps(userStringInput);
            end = chrono::high_resolution_clock::now();
            totalNodesAvlWordsTree = IH.getTotalNodesWordsTree();
            totalArticlesInIndex = IH.getTotalArticles();
            timeIndexFromDir = end - start;
        } else if (userIntChoice == "2") {
            IH.saveTreeWithMapToFile("../build/wordsAVLTree.txt");
            IH.saveTreeWithVectorToFile("../build/personsAVLTree.txt", "../build/orgsAVLTree.txt");

            // persistence thing
        } else if (userIntChoice == "3") {
            // create words, people, orgs
            //  create an index from .txt
            start = chrono::high_resolution_clock::now();
            IH.createWordsTreeFromFile("../build/wordsAVLTree.txt");
            IH.createOrgPerTreeFromFile("../build/personsAVLTree.txt", 1);
            IH.createOrgPerTreeFromFile("../build.orgsAVLTree.txt", 0);
            end = chrono::high_resolution_clock::now();
            timeIndexFromFile = end - start;
        } else if (userIntChoice == "4") {
            queryThingy(userStringInput);

        } else if (userIntChoice == "5") {
            chrono::duration<double> timeID = timeIndexFromDir;
            chrono::duration<double> timeIF = timeIndexFromFile;
            chrono::duration<double> timeQP = timeProcessQuery;
            cout << "\nTiming of Indexing from Directory: " << timeID.count() << endl;
            cout << "Timing of Indexing from File: " << timeIF.count() << endl;
            cout << "Timing of Processing Query: " << timeQP.count() << endl;
            cout << "Total unique words indexed: " << totalNodesAvlWordsTree << endl;
            cout << "Total unique articles for current index: " << totalArticlesInIndex << endl;
            cout << "------------------------------------------------------" << endl;

        } else if (userIntChoice == "9") {
            break;
        }
    }
}

void SearchEngine::indexFromSS(string filePath) {
    IH.createTheTreeMaps(filePath);
    IH.saveTreeWithMapToFile("../build/wordsAVLTree.txt");
    IH.saveTreeWithVectorToFile("../build/personsAVLTree.txt", "../build/orgsAVLTree.txt");
}

void SearchEngine::wordIndexIntoSSFromFile(string filePath) {
    IH.createWordsTreeFromFile(filePath);
}

void SearchEngine::orgPerIndexIntoSSFromFile(string filePath, int whichFile) {
    IH.createOrgPerTreeFromFile(filePath, whichFile);
}

void SearchEngine::queryThingy(string wholeQuery) {
    start = chrono::high_resolution_clock::now();
    QP.processQuery(wholeQuery);
    end = chrono::high_resolution_clock::now();
    timeProcessQuery = end - start;
    map<string, double> pathAndRelCombo;

    if (!QP.getWords().empty()) {
        for (auto& it : QP.getWords()) {
            words.push_back(it);
        }

        for (auto currWord : words) {
            wordMapsVector.push_back(IH.getAWordsMap(currWord));
        }

        if (wordMapsVector.size() > 1) {
            // combine 1 and 2 into temp, them
            pathAndRelCombo = QP.combineWordMaps(wordMapsVector[0], wordMapsVector[1]);
            for (long unsigned int i = 2; i < wordMapsVector.size(); i++) {
                pathAndRelCombo = QP.combineWordMaps(pathAndRelCombo, wordMapsVector[i]);
            }
        } else {
            pathAndRelCombo = wordMapsVector[0];
        }
    }
    if (!QP.getNotWords().empty()) {
        notWords = QP.getNotWords();

        for (auto currWord : notWords) {
            notWordMapsVector.push_back(IH.getAWordsMap(currWord));
        }

        for (auto it : notWordMapsVector) {
            QP.removeNotWordFiles(pathAndRelCombo, it);
        }
    }
    if (!QP.getOrgs().empty()) {
        orgs = QP.getOrgs();
        for (auto org : orgs) {
            orgFilePaths.push_back(IH.getVectorOfOrgFilePaths(org));
        }
        for (auto org : orgFilePaths) {
            pathAndRelCombo = QP.combineOrg(pathAndRelCombo, org);
        }
    }
    if (!QP.getPersons().empty()) {
        persons = QP.getPersons();

        for (auto person : persons) {
            personFilePaths.push_back(IH.getVectorOfPeopleFilePaths(person));
        }
        for (auto person : personFilePaths) {
            pathAndRelCombo = QP.combinePersons(pathAndRelCombo, person);
        }
    }

    vector<pair<string, double>> myVector(pathAndRelCombo.begin(), pathAndRelCombo.end());

    // Define a custom comparator for sorting in descending order based on the second element of the pairs
    auto comparator = [](const pair<string, double>& a, const std::pair<std::string, double>& b) {
        return a.second > b.second;
    };

    // Sort the vector using the custom comparator
    sort(myVector.begin(), myVector.end(), comparator);

    map<string, double> sortedMap(myVector.begin(), myVector.end());

    // Save the top 25 entries
    long unsigned int count = 0;
    map<string, double> results;
    for (const auto& entry : sortedMap) {
        if ((count < 25) && (count < pathAndRelCombo.size())) {
            // Do something with the entry, for example, print to the console
            results.insert(make_pair(entry.first, entry.second));
            count++;
        } else {
            break;  // Break out of the loop after saving the top 25
        }
    }
    cout << "-------------------------------------" << endl;
    for (auto thing : results) {
        ifstream input(thing.first);
        if (!input.is_open()) {
            cerr << "cannot open file: " << thing.first << endl;
            return;
        }

        IStreamWrapper isw(input);
        Document d;
        d.ParseStream(isw);

        auto title = d["thread"]["section_title"].GetString();
        auto url = d["thread"]["url"].GetString();

        cout << "\nTitle: " << title << endl;
        cout << "URL: " << url << endl;
        cout << "----------------------------------------" << endl;
    }

    wordMapsVector.clear();
    notWordMapsVector.clear();
    personFilePaths.clear();
    orgFilePaths.clear();
    words.clear();
    persons.clear();
    orgs.clear();
    notWords.clear();
    QP.clearVectors();
}
