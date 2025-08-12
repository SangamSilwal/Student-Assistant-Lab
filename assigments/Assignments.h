#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <string>
#include <vector>
#include <sqlite3.h>

struct AssignmentData {
    int id;
    int student_id;
    std::string title;
    std::string description;
    std::string due_date;
    std::string status;
};

class Assignment {
private:
    sqlite3* db;
    void createAssignmentTable();

public:
    Assignment(sqlite3* database);
    ~Assignment();

    bool addAssignment(int student_id, const std::string& title, const std::string& description, const std::string& due_date);
    std::vector<AssignmentData> getAssignments(int student_id);
    bool updateAssignmentStatus(int assignment_id, const std::string& status);
    bool deleteAssignment(int assignment_id);
};

#endif 
