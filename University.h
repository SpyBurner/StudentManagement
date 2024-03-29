#include <iomanip>
#include <iostream>

#include <list>
#include <unordered_map>
#include <vector>

using namespace std;

const int tabSpace = 25;

enum ScoreType {
    ASSIGNMENT,
    TEST,
    EXAM
};

class Semester {
private:
    unordered_map<ScoreType, vector<float>> scoreMap;

    void insertType(int count, ScoreType type) {
        vector<float> temp;
        for (int i = 0; i < count; ++i) {
            temp.push_back(0);
        }
        scoreMap.emplace(type, temp);
    }

public:
    Semester(int n1, int n2, int n3) {
        insertType(n1, ASSIGNMENT);
        insertType(n2, TEST);
        insertType(n3, EXAM);

        constructByInput();
    }

    Semester(vector<int> TEMPLATE) {
        insertType(TEMPLATE[0], ASSIGNMENT);
        insertType(TEMPLATE[1], TEST);
        insertType(TEMPLATE[2], EXAM);

        constructByInput();
    }

    ~Semester() {
        scoreMap.clear();
    }

    void constructByInput() {
        float temp;

        cout << endl
             << "Input " << scoreMap[ASSIGNMENT].size() << " ASSIGNMENT score(s), separated by spaces: ";
        for (int i = 0; i < scoreMap[ASSIGNMENT].size(); ++i) {
            cin >> temp;
            scoreMap[ASSIGNMENT][i] = temp;
        }

        cout << endl
             << "Input " << scoreMap[TEST].size() << " TEST score(s), separated by spaces: ";
        for (int i = 0; i < scoreMap[TEST].size(); ++i) {
            cin >> temp;
            scoreMap[TEST][i] = temp;
        }

        cout << endl
             << "Input " << scoreMap[EXAM].size() << " EXAM score(s), separated by spaces: ";
        for (int i = 0; i < scoreMap[EXAM].size(); ++i) {
            cin >> temp;
            scoreMap[EXAM][i] = temp;
        }
    }

    //! INLINE PRINT
    void print() {
        cout << "ASSIGNMENT(s): ";
        for (auto iter : scoreMap[ASSIGNMENT]) {
            cout << iter << " ";
        }

        cout << " | ";

        cout << "TEST(s): ";
        for (auto iter : scoreMap[TEST]) {
            cout << iter << " ";
        }

        cout << " | ";

        cout << "EXAM(s): ";
        for (auto iter : scoreMap[EXAM]) {
            cout << iter << " ";
        }
    }
};

class Student {
protected:
    int id;
    string name;

    vector<Semester> semesterList;

public:
    Student() {}
    Student(int id, string name) : id(id), name(name) {}
    ~Student() {}

    int setID(int id) { this->id = id; }

    int getID() { return id; }
    string getName() { return name; }

    Semester getSemesterByID(int semID) {
        semID--;
        if (semID >= semesterList.size() || semID < 1) {
            throw "ID out of range";
        }
        return semesterList.at(semID);
    }

    void addSemester(Semester semester) {
        semesterList.push_back(semester);
    }

    void addDataToTemplate() {
        for (auto iter = semesterList.begin(); iter < semesterList.end(); ++iter) {
            cout << "Semester: " << semesterList.end() - iter << endl;
            iter->constructByInput();
        }
    }

    void removeSemesterByID(int semID) {
        semID--;
        semesterList.erase(semesterList.begin() + semID);
    }

    void print() {
        cout << setw(tabSpace) << left << id
             << setw(tabSpace) << left << name << endl;
        int semID = 0;
        for (auto iter : semesterList) {
            cout << "Semester " << ++semID << ": ";
            iter.print();
            cout << endl;
        }
        cout << "----o----";
    }
};

class UniStudent : public Student {
private:
    vector<int> semesterTemplate = {3, 2, 1};

public:
    UniStudent() : Student() {
    }

    UniStudent(int id, string name, int semCount) : Student(id, name) {
        for (int i = 0; i < semCount; ++i) {
            semesterList.emplace_back(semesterTemplate);
        }
    }

    ~UniStudent();
};

class CollStudent : public Student {
private:
    vector<int> semesterTemplate = {1, 1, 1};

public:
    CollStudent() : Student() {
    }

    CollStudent(int id, string name) : Student(id, name) {
    }

    CollStudent(int id, string name, int semCount) : Student(id, name) {
        for (int i = 0; i < semCount; ++i) {
            semesterList.emplace_back(semesterTemplate);
        }
    }

    ~CollStudent();
};

class CollegeStudentList {
private:
    list<CollStudent> stList;
    int timelineId = 0;

public:
    CollegeStudentList() {}
    ~CollegeStudentList() {}

    void addStudent(CollStudent student) {
        stList.push_back(student);
    }

    bool removeStudentById(int id) {
        for (list<CollStudent>::iterator iter = stList.begin(); iter != stList.end(); ++iter) {
            if (iter->getID() == id) {
                stList.erase(iter);
                return true;
            }
        }
        return false;
    }

    void listStudent() {
        for (auto iter : stList) {
            iter.print();
        }
    }
};

class UniStudentList {
private:
    list<UniStudent> stList;
    int timelineId = 0;

public:
    UniStudentList() {}
    ~UniStudentList() {}

    void addStudent(UniStudent student) {
        student.setID(timelineId++);
        stList.push_back(student);
    }

    bool removeStudentById(int id) {
        for (list<UniStudent>::iterator iter = stList.begin(); iter != stList.end(); ++iter) {
            if (iter->getID() == id) {
                stList.erase(iter);
                return true;
            }
        }
        return false;
    }

    void listStudent() {
        for (auto iter : stList) {
            iter.print();
        }
    }
};