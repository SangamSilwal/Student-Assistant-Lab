#include "TodoList.h"
#include <iostream>

const std::string RESET   = "\033[0m";
const std::string GREEN   = "\033[32m";
const std::string YELLOW  = "\033[33m";
const std::string RED     = "\033[31m";

TodoList::TodoList(sqlite3 *db, int userId) {
    this->db = db;
    this->userId = userId;

    const char *create_table_sql =
        "CREATE TABLE IF NOT EXISTS todo("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "task TEXT NOT NULL,"
        "status TEXT DEFAULT 'pending',"
        "user_id INTEGER,"
        "FOREIGN KEY(user_id) REFERENCES users(id));";

    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, create_table_sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error (todo table): " << errMsg << "\n";
        sqlite3_free(errMsg);
    }
}

void TodoList::addTask(const std::string &task) {
    std::string sql = "INSERT INTO todo (task, status, user_id) VALUES('" + task + "', 'pending', " + std::to_string(userId) + ");";
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error (addTask): " << errMsg << "\n";
        sqlite3_free(errMsg);
    } else {
        std::cout << "Task added.\n";
    }
}

void TodoList::removeTask(int id) {
    std::string sql = "DELETE FROM todo WHERE id=" + std::to_string(id) + " AND user_id=" + std::to_string(userId) + ";";
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error (removeTask): " << errMsg << "\n";
        sqlite3_free(errMsg);
    } else {
        std::cout << "Task removed.\n";
    }
}

void TodoList::markTaskDone(int id) {
    std::string sql = "UPDATE todo SET status='done' WHERE id=" + std::to_string(id) + " AND user_id=" + std::to_string(userId) + ";";
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error (markTaskDone): " << errMsg << "\n";
        sqlite3_free(errMsg);
    } else {
        std::cout << "Task marked as done.\n";
    }
}

int TodoList::callback(void *NotUsed, int argc, char **argv, char **azColName) {
    std::string id, task, status;

    for (int i = 0; i < argc; i++) {
        std::string colName = azColName[i];
        std::string value = argv[i] ? argv[i] : "NULL";

        if (colName == "id") id = value;
        else if (colName == "task") task = value;
        else if (colName == "status") status = value;
    }

    std::string color;
    if (status == "pending") color = YELLOW;
    else if (status == "done") color = GREEN;
    else color = RED;

    std::cout << color << id << ". " << task << " [" << status << "]" << RESET << "\n";
    return 0;
}

void TodoList::viewTasks() {
    std::string sql = "SELECT id, task, status FROM todo WHERE user_id=" + std::to_string(userId) + ";";
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error (viewTasks): " << errMsg << "\n";
        sqlite3_free(errMsg);
    }
}