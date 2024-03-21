#include "TextBasedMenu.h"
TextBasedMenu menu;
StudentList stList;

void INIT() {

    //*Read students from file
    ifstream file("studentData.txt");

    // File doesnt exist
    if (!file.is_open()) {
        file.close();
        ofstream temp("studentData.txt");
        temp << "\0";
        temp.close();
        file.open("studentData.txt");
    }

    while (!file.eof()) {
        string student;
        string score;
        getline(file, student);
        getline(file, score);
        if (student.empty())
            break;
        stList.push(student, stof(score));
    }

    file.close();
}

void EXIT() {
    //! Save student data to file
    stList.dumpToFile("studentData.txt");
}

//*Operations
void AddStudent() {
    menu.DrawTextBox("Add student");
    string name;
    float score;

    cout << "Input student name: ";
    fflush(stdin);
    getline(cin, name);

    cout << "Input student score (float): ";
    fflush(stdin);
    cin >> score;

    stList.push(name, score);

    menu.DrawTextBox("Add student");
    cout << "Added successfully!";
    TextBasedMenu::waitForEnter();
}

void RemoveStudent() {
    menu.DrawTextBox("Remove student");
    string name;
    float score;

    cout << "Input student name: ";
    fflush(stdin);
    getline(cin, name);

    bool res = stList.remove(name);

    menu.DrawTextBox("Remove student");
    if (res) cout << "Remove successfully!";
    else cout << "Remove failed!";
    TextBasedMenu::waitForEnter();
}

void ListStudent() {
    menu.DrawTextBox("List students");
    if (stList.getSize() == 0) {
        cout << "Nothing here...";

    } else {
        cout << left << setw(setwSpace) << "Name" << right <<setw(setwSpace)  << "Score" << endl;
        stList.printStudents();
    }

    TextBasedMenu::waitForEnter();
}

void DisplayBestStudent() {
    menu.DrawTextBox("Best students");

    if (stList.getSize() == 0) {
        cout << "Nothing here...";

    } else {
        cout << left << setw(setwSpace) << "Name" << right <<setw(setwSpace)  << "Score" << endl;
        stList.printBest();
    }

    TextBasedMenu::waitForEnter();
}

int main(int argc, char const *argv[]) {
    INIT();

    menu.addOption("Add student", []() { AddStudent(); });
    menu.addOption("Remove student", []() { RemoveStudent(); });
    menu.addOption("List students", []() { ListStudent(); });
    menu.addOption("Display best student(s)", []() { DisplayBestStudent(); });

    while (true) {
        bool work = menu.operate();
        if (!work)
            break;
    }

    EXIT();
    return 0;
}
