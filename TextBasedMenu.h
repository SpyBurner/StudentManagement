#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include <fstream>

#include <functional>
#include <iomanip>
#include <stdlib.h> //*For clearing terminal

using namespace std;

static const int setwSpace = 30;

class TextBasedMenu {
private:
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
        "Lab3 - Nguyen Hiep Tai",
        "         @ Hashkell Clowns",
    };

    string getStudentFromKeyboard() {
        string student;
        cout << "Student name : " << endl;
        fflush(stdin);
        getline(cin, student);
        fflush(stdin);
        return student;
    }

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

class StudentList;

class Student {
private:

    string name;
    float score;
public:
    Student() {
        name = "";
        score = 0;
    }
    Student(string st, float fl) {
        name = st;
        score = fl;
    }
    ~Student() {
    }
    friend StudentList;
};

class StudentList {
private:
    const int BlockSize = 32;
    int size = 32;
    int count = 0;
    Student **studentList;

    void ensureCapacity(int newSize) {
        if (newSize < size)
            return;
        size = (newSize + 32) / 32 * 32;
        Student **data = new Student*[size];
        for (int i = 0; i < count; ++i) {
            data[i] = studentList[i];
        }
        delete[] studentList;
        studentList = data;
    }

public:
    StudentList() {
        studentList = new Student*[size];
    }
    ~StudentList() {
        for (int i = 0; i < count; ++i) {
            delete studentList[i];
        }

        delete[] studentList;
    }

    int getSize() { return count; }
    void printStudents() {
        for (int i = 0; i < count; ++i) {
            cout << left << setw(setwSpace) << studentList[i]->name << right << setw(setwSpace) << studentList[i]->score << endl;
        }
    }
    void printBest() {
        float maxScore = studentList[0]->score;
        vector<Student*> res;

        for (int i = 0; i < count; ++i) {
            if (studentList[i]->score == maxScore)
                res.push_back(studentList[i]);
            if (studentList[i]->score > maxScore) {
                maxScore = studentList[i]->score;
                res.clear();
                res.push_back(studentList[i]);
            }
        }
        for (auto iter : res) {
            cout << left << setw(setwSpace) << iter->name << right << setw(setwSpace) << iter->score << endl;
        }
    }

    void dumpToFile(string filename) {
        ofstream outfile(filename);
        for (int i = 0; i < count; ++i) {
            outfile << studentList[i]->name << endl
                    << studentList[i]->score << endl;
        }
        outfile.close();
    }

    void push(string name, float score) {
        ensureCapacity(count + 1);
        studentList[count] = new Student(name, score);
        count++;
    }

    void updateScore(string name, float newScore) {
        int index = 0;
        for (index = 0; index < count; ++index) {
            if (studentList[index]->name == name)
                break;
        }
        studentList[index]->score = newScore;
    }


    //TODO pointer remove
    bool remove(string name) {
        int index = 0;
        bool found = false;
        for (index = 0; index < count; ++index) {
            if (studentList[index]->name == name) {
                found = true;
                break;
            }
        }

        if (!found)
            return false;

        for (index; index < count; ++index) {
            studentList[index] = studentList[index + 1];
        }
        count--;
        return true;
    }
};