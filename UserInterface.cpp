#include "UserInterface.h"

void UserInterface::startUI() {
    int numPicked;

    do {
        cout << "Please choose an option:" << endl;
        cout << "(1) Create an index from a directory with documents."
             << "\n(2) Write the index to a file."
             << "\n(3) Read an index from a file."
             << "\n(4) Enter a query."
             << "\n(5) Output statistics of the search engine."
             << "\nPlease enter only 1, 2, 3, 4, or 5." << endl;
        cout << "Enter 9 to exit.\n\n";

        cout << "Enter Choice:";
        getline(cin, userChoice);
        if (userChoice == "9") {
            break;
        }

        if (isANumber(userChoice)) {
            numPicked = stoi(userChoice);
        }

        if ((numPicked < 1) || (numPicked > 5)) {
            cout << "\nInvaild choice, please try again.\n\n\n";
        }

    } while ((numPicked < 1) || (numPicked > 5));

    if (numPicked == 1) {
        cout << "Enter the directory you would like indexed:";
        getline(cin, userInput);
    } else if (numPicked == 2) {
        cout << "Saving to file" << endl;

    } else if (numPicked == 3) {
        cout << "Reading in saved index from file." << endl;
    } else if (numPicked == 4) {
        cout << "Enter your query with the following format:" << endl;
        cout << "(\"<words to search>\" \"ORG:<some organization name>\" \"PERSON:<some person's name>\" \"-<word not present in result>\")" << endl;
        getline(cin, userInput);
    }
}

bool UserInterface::isANumber(const string& str) {
    for (char ch : str) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return true;
}
