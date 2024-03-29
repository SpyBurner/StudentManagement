#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include <fstream>

#include <functional>
#include <iomanip>
#include <stdlib.h> //*For clearing terminal

#include "University.h"

using namespace std;

static const int setwSpace = 30;

class TextBasedMenu {
protected:
    //?Options
    class Option {
    public:
        string optionText;
        function<void()> operation;

        Option(string optionText, function<void()> operation) {
            this->optionText = optionText;
            this->operation = operation;
        }
    };
    vector<Option> optionList;

    //?Menu generation
    //*Max 50 characters per line
    string lines[3] = {
        "",
        "Lab5 - Nguyen Hiep Tai",
        "         @ Hashkell Clowns",
    };

    bool printOptions = true;

public:
    int optionCount;
    string message = "";

    TextBasedMenu() {
        optionCount = optionList.size();
    }
    ~TextBasedMenu() {
    }

    //! Static methods
    static void waitForEnter() {
        cout << endl
             << "Press enter key to return...";
        fflush(stdin);
        cin.get();
    }
    static bool isNumber(string st) {
        for (auto ch : st) {
            if (!isdigit(ch))
                return false;
        }
        return true;
    }

    //! Text box max text length = 50 per line
    void DrawTextBox(string line) {
        // CLear terminal
        cout << flush;
        system("CLS");
        cout << message << endl;
        message.clear();

        // Print logo
        cout << "+--------------------------------------------------+" << endl;
        cout << "|" << setw(51) << "|" << endl;

        string firstHalf(line.begin(), line.begin() + line.length() / 2);
        string secondHalf(line.begin() + line.length() / 2, line.end());
        cout << "|" << setw(25) << firstHalf << left << setw(25) << secondHalf << "|" << endl;
        cout << right;

        cout << "|" << setw(51) << "|" << endl;
        cout << "+--------------------------------------------------+" << endl;
    }

    void DrawLogo() {
        // CLear terminal
        cout << flush;
        system("CLS");
        cout << message << endl;
        message.clear();

        // Print logo
        cout << "+--------------------------------------------------+" << endl;
        for (int i = 0; i < 3; ++i) {
            if (lines[i].length() == 0) {
                cout << "|" << setw(51) << "|" << endl;
                continue;
            }

            string firstHalf(lines[i].begin(), lines[i].begin() + lines[i].length() / 2);
            string secondHalf(lines[i].begin() + lines[i].length() / 2, lines[i].end());
            cout << "|" << setw(25) << firstHalf << left << setw(25) << secondHalf << "|" << endl;
            cout << right;
        }
        cout << "+--------------------------------------------------+" << endl;

        if (!printOptions)
            return;

        // Print options
        int index = 1;
        for (auto iter : optionList) {
            cout << setw(3) << index << ". "; // Print index;
            cout << iter.optionText << endl;
            index++;
        }
        // Print exit
        cout << setw(3) << index << ". "; // Print index;
        cout << "Exit and save" << endl;

        cout << endl;
    }

    void executeOption(int index) {
        optionList[index - 1].operation();
    }

    bool operate() {
        DrawLogo();
        string input;
        cout << "Choose an option: ";

        fflush(stdin);
        getline(cin, input);

        if (!isNumber(input) || input.empty()) {
            message = "Please input a number!";
            return true;
        }
        int inputNumber = stoi(input);
        if (inputNumber > optionCount + 1 || inputNumber <= 0) {
            message = "Chosen option does not exist!";
            return true;
        }

        // Exit
        if (inputNumber == optionCount + 1)
            return false;

        executeOption(inputNumber);
        return true;
    }

    vector<Option> getOptions() {
        return optionList;
    }

    void addOption(string optionText, function<void()> operation) {
        optionList.emplace_back(optionText, operation);
        optionCount++;
    }

    void removeOption(int index) {
        optionList.erase(optionList.begin() + index);
        optionCount--;
    }
};

class MasterMenu : public TextBasedMenu{
};