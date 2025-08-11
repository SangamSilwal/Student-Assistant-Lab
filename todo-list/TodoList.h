#ifndef TODOLIST_H
#define TODOLIST_H

#include <string>
#include <sqlite3.h>

class TodoList {
public:
    TodoList(sqlite3 *db, int userId);
    void addTask(const std::string &task);
    void removeTask(int id);
    void markTaskDone(int id);
    void viewTasks();

private:
    sqlite3 *db;
    int userId;
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};

#endif