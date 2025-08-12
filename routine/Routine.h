#ifndef ROUTINE_H
#define ROUTINE_H

#include <string>
#include <vector>
#include <sqlite3.h>

struct RoutineData {
    int id;
    int student_id;
    std::string day;
    std::string start_time;
    std::string end_time;
    std::string subject;
};

class Routine {
private:
    sqlite3* db;
    void createRoutineTable();

public:
    Routine(sqlite3* database);
    ~Routine();

    bool addRoutine(int student_id, const std::string& day, const std::string& start_time, const std::string& end_time, const std::string& subject);
    std::vector<RoutineData> getRoutines(int student_id);
    bool updateRoutine(int routine_id, const std::string& day, const std::string& start_time, const std::string& end_time, const std::string& subject);
    bool deleteRoutine(int routine_id);
};

#endif // ROUTINE_H