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
        cout << "Exit" << endl;

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

class MasterMenu : public TextBasedMenu {
private:
    TextBasedMenu collegeMenu, uniMenu;

    CollegeStudentList colList;
    UniStudentList uniList;

    void startAMenu(TextBasedMenu subMenu) {
        while (true) {
            bool res = subMenu.operate();
            if (!res)
                break;
        }
    }

public:
    MasterMenu() {
        addOption("Manage University students", [this]() -> void { startAMenu(MasterMenu::uniMenu); });
        addOption("Manage College students", [this]() -> void { startAMenu(MasterMenu::collegeMenu); });

#pragma region Uni Menu

        uniMenu.addOption("Add student", [this]() -> void {
            this->uniMenu.DrawTextBox("Add student");
            string name;

            cout << "Student name: " << endl;
            fflush(stdin);
            getline(cin, name);
            UniStudent student(0, name, 8);

            this->uniList.addStudent(student);

            cout << "Added successfully";
        });

        uniMenu.addOption("Remove student", [this]() -> void {
            this->uniMenu.DrawTextBox("Remove student");
            int id;
            cout << "Student id: " << endl;
            cin >> id;

            bool res = this->uniList.removeStudentById(id);
            cout << (res) ? "Remove successfully" : "Remove unsuccessfully, please check input";
            waitForEnter();
        });

        uniMenu.addOption("List student", [this]() -> void {
            this->uniMenu.DrawTextBox("list student");
            this->uniList.listStudent();
            waitForEnter();
        });

#pragma endregion

#pragma region College Menu

        collegeMenu.addOption("Add student", [this]() -> void {
            this->collegeMenu.DrawTextBox("Add student");
            string name;

            cout << "Student name: " << endl;
            fflush(stdin);
            getline(cin, name);
            CollStudent student(0, name, 8);

            this->colList.addStudent(student);

            cout << "Added successfully";
        });

        collegeMenu.addOption("Remove student", [this]() -> void {
            this->collegeMenu.DrawTextBox("Remove student");
            int id;
            cout << "Student id: " << endl;
            cin >> id;

            bool res = this->colList.removeStudentById(id);
            cout << (res) ? "Remove successfully" : "Remove unsuccessfully, please check input";
            waitForEnter();
        });

        collegeMenu.addOption("List student", [this]() -> void {
            this->collegeMenu.DrawTextBox("list student");
            this->colList.listStudent();
            waitForEnter();
        });

#pragma endregion
    }

};