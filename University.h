#include "TextBasedMenu.h"
#include <iostream>
#include <list>

using namespace std;

class Semester {
private:
    enum ScoreType;

    unordered_map<ScoreType, vector<float>> scoreMap;

    void insertType(int count, ScoreType type) {
        vector<float> temp;
        for (int i = 0; i < count; ++i) {
            temp.push_back(0);
        }
        scoreMap.emplace(type, temp);
    }

public:
    enum ScoreType {
        ASSIGNMENT,
        TEST,
        EXAM
    };

    Semester(int n1, int n2, int n3) {
        insertType(n1, ASSIGNMENT);
        insertType(n2, TEST);
        insertType(n3, EXAM);
    }

    Semester(vector<int> TEMPLATE) {
        insertType(TEMPLATE[0], ASSIGNMENT);
        insertType(TEMPLATE[1], TEST);
        insertType(TEMPLATE[2], EXAM);
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

    int getID() { return id; }
    string getName() { return name; }

    Semester getSemesterByID(int semID) {
        semID--;
        if (semID >= semesterList.size() || semID < 1) {
            throw new exception("ID out of range");
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

class StudentList {
protected:
    string filePath;
    list<Student *> stList;

    int timelineID = 0;

public:
    template <class T>

    StudentList() {}
    StudentList(string filePath) {
        this->filePath = filePath;
    }
    ~StudentList() {
        for (auto iter : stList) {
            delete iter;
        }
    }

    void addStudent(Student* student){
        stList.push_back(student);
    }

    void removeStudentById(int id){
        for (auto iter : stList){
            if (iter->getID() == id){
                delete iter;
                stList.erase(iter)
                return;
            }
        }
    }
    void listStudent();
    void listBestStudents();
    void saveToFile();
};
