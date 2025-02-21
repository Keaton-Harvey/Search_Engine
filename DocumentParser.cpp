#include "DocumentParser.h"

#include <cctype>
#include <cstring>
#include <sstream>

void DocumentParser::parser(const string filename) {
    wordsFromDoc.clear();
    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "cannot open file: " << filename << endl;
        return;
    }

    IStreamWrapper isw(input);
    Document d;
    d.ParseStream(isw);

    string text = d["text"].GetString();
    string line;

    istringstream iss(text);

    while (getline(iss, line)) {
        string token;
        for (unsigned long int i = 0; i < line.length(); i++) {
            if (isalpha(line[i]) == false) {
                if (token.empty() == true) {
                    continue;
                }
                token = removePunctAndLower(token);
                if (!token.empty()) {
                    wordsFromDoc.push_back(token);
                }
                token.clear();
            } else {
                token = token + line[i];
            }
        }
        if (!token.empty()) {
            token = removePunctAndLower(token);
            if (!token.empty()) {
                wordsFromDoc.push_back(token);
            }
        }
    }
    wordCount = wordsFromDoc.size();

    wordsFromDoc = removeStopWords(wordsFromDoc, stopWords);
    StemFunct(wordsFromDoc);

    // loop through words, add to map with relRank 1, if already in map, instead of adding, increase rel rank int by 1.
    for (long unsigned int i = 0; i < wordsFromDoc.size(); i++) {
        if (wordsAndRelRank.find(wordsFromDoc.at(i)) == wordsAndRelRank.end()) {
            // it didnt find the word in the map
            wordsAndRelRank.insert(make_pair(wordsFromDoc.at(i), 1));

        } else {
            // it found the word in the map
            wordsAndRelRank[wordsFromDoc.at(i)] += 1;
        }
        // also count total number of words then at the end set rel rank to numTimes/totalNumWords
    }

    // iterate through the map (wordsAndRelRank) and set the relRanks to the numberOfTimesTheWordAppeared/totalWords
    for (auto &pair : wordsAndRelRank) {
        pair.second = (pair.second / wordCount);
    }
    wordCount = 0;
}

string DocumentParser::removePunctAndLower(string word) {
    string result = word;
    std::vector<char> punctuationMarks = {
        '.',
        ',',
        '!',
        '?',
        ':',
        ';',
        '"',
        '\'',
        '(',
        ')',
        '{',
        '}',
        '[',
        ']',
        '@',
        '*',
        '~',
        '/',
        '-',
        '#',
        '$',
        '&',
        '%',
        '0',
        '1',
        '2',
        '3',
        '4',
        '5',
        '6',
        '7',
        '8',
        '9',

    };

    for (char c : punctuationMarks) {
        result.erase(remove(result.begin(), result.end(), c), result.end());
    }
    for (char &c : result) {
        c = tolower(c);
    }
    return result;
}

vector<string> DocumentParser::removeStopWords(const vector<string> wordsFromDoc, const unordered_set<string> stopWords) {
    vector<string> removedStopWords;
    for (const auto &word : wordsFromDoc) {
        if (stopWords.find(word) == stopWords.end()) {
            removedStopWords.push_back(word);
        }
    }
    return removedStopWords;
}

void DocumentParser::clearWordsAndRelRank() {
    wordsAndRelRank.clear();
}

void DocumentParser::StemFunct(vector<string> &wordsFromDoc) {
    for (string &s : wordsFromDoc) {
        Porter2Stemmer::stem(s);
    }
}