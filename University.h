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

    ~Semester(){
        scoreMap.clear();
    }

    void constructByInput(){
        float temp;

        cout << "Input " << scoreMap[ASSIGNMENT].size() << " ASSIGNMENT score(s), separated by spaces: ";
        for (int i = 0; i < scoreMap[ASSIGNMENT].size(); ++i){
            cin >> temp;
            scoreMap[ASSIGNMENT][i] = temp;
        }

        cout << "Input " << scoreMap[TEST].size() << " TEST score(s), separated by spaces: ";
        for (int i = 0; i < scoreMap[TEST].size(); ++i){
            cin >> temp;
            scoreMap[TEST][i] = temp;
        }

        cout << "Input " << scoreMap[EXAM].size() << " EXAM score(s), separated by spaces: ";
        for (int i = 0; i < scoreMap[EXAM].size(); ++i){
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

    void addSemester(Semester semester){
        semesterList.push_back(semester);
    }

    Semester getSemesterByID(int semID){
        semID--;
        if (semID >= semesterList.size() || semID < 1){
            throw new exception("ID out of range");
        }
        return semesterList.at(semID);
    }

    virtual void addSemesterByInput();
    void removeSemesterByID(int semID){
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

    UniStudent(int id, string name) : Student(id, name) {
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

    ~CollStudent();
};

class StudentList {
protected:
    string filePath;
    list<Student *> stList;

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

    virtual void addStudent(Student *);
    virtual void removeStudentById(int id);
    virtual void listStudent();
    virtual void listBestStudents();
    virtual void saveToFile();
};
