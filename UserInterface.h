#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <cctype>
#include <iostream>

using namespace std;

class UserInterface {
   private:
    string userChoice;
    string userInput;

   public:
    void startUI();

    string getUserChoice() { return userChoice; };
    string getUserInput() { return userInput; };
    bool isANumber(const string &str);
};

#endif