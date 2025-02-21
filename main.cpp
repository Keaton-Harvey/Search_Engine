#include "SearchEngine.h"

using namespace std;

int main() {
    cout << "Usage:\n"
         << "\tIndex all files in <directory> and store the index in one or several files:\n"
         << "\tsupersearch index <directory>\n\n"
         << "\tLoad the existing index and perform the following query:\n"
         << "\tsupersearch query \"social network PERSON:cramer\"\n\n"
         << "\tStart a simple text-based user interface that lets the user create an index,\n\tsave/load the index and perform multiple queries:\n"
         << "\tsupersearch ui\n\n";

    string userCommand;
    SearchEngine SE;
    cout << "Please enter a command as described above:";
    getline(cin, userCommand);
    cout << "" << endl;
    istringstream iss(userCommand);
    string firstWord, secondWord;
    iss >> firstWord;
    iss >> secondWord;

    if (firstWord != "supersearch") {
        cout << "ERROR: Invaild entry" << endl;
        return -1;
    } else if (secondWord == "index") {
        string indexPath;
        iss >> indexPath;
        SE.indexFromSS(indexPath);

    } else if (secondWord == "query") {
        SE.wordIndexIntoSSFromFile("../build/wordsAVLTree.txt");
        SE.orgPerIndexIntoSSFromFile("../build/personsAVLTree.txt", 1);
        SE.orgPerIndexIntoSSFromFile("../build/orgsAVLTree.txt", 0);
        string userQuery;
        iss >> userQuery;
        SE.queryThingy(userQuery);

    } else if (secondWord == "ui") {
        SE.startUI();
    }

    return 0;
}