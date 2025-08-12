#include "TodoList.h"
#include "utility/utils.h"
#include <iostream>


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


TaskStats TodoList::getStatistics() {
    TaskStats stats = {0, 0, 0};
    
    const char* sql = "SELECT COUNT(*) as total, "
                      "SUM(CASE WHEN status = 'done' THEN 1 ELSE 0 END) as completed, "
                      "SUM(CASE WHEN status = 'pending' THEN 1 ELSE 0 END) as pending "
                      "FROM todo WHERE user_id = ?;";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        return stats;
    }
    
   
    sqlite3_bind_int(stmt, 1, userId);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        stats.totalTasks = sqlite3_column_int(stmt, 0);
        stats.completedTasks = sqlite3_column_int(stmt, 1);
        stats.pendingTasks = sqlite3_column_int(stmt, 2);
    } else {
        std::cerr << "Failed to get statistics: " << sqlite3_errmsg(db) << "\n";
    }
    
    sqlite3_finalize(stmt);
    return stats;
}


void TodoList::displayStatistics() {
    Utility utils;
    TaskStats stats = getStatistics();

    int total = stats.totalTasks;
    int completed = stats.completedTasks;
    int pending = stats.pendingTasks;

   
    double completedPercent = (total > 0) ? (completed * 100.0 / total) : 0;
    double pendingPercent   = (total > 0) ? (pending   * 100.0 / total) : 0;

    
    std::cout << CYAN << "||" << BOLD << YELLOW << "         [T] TASK STATISTICS       " 
              << RESET << CYAN << "||" << RESET << std::endl;
    std::cout << CYAN << "|| " << WHITE  << "Total Tasks:      " << BOLD << std::setw(15) << total     << RESET << CYAN << " ||" << RESET << std::endl;
    std::cout << CYAN << "|| " << GREEN  << "Completed:        " << BOLD << std::setw(15) << completed << RESET << CYAN << " ||" << RESET << std::endl;
    std::cout << CYAN << "|| " << YELLOW << "Pending:          " << BOLD << std::setw(15) << pending   << RESET << CYAN << " ||" << RESET << std::endl;

    
    int barWidth = 50; 
    int completedBars = (total > 0) ? (completed * barWidth / total) : 0;
    int pendingBars   = barWidth - completedBars;

    
    std::cout << "\nProgress: ";
    std::cout << GREEN;
    for (int i = 0; i < completedBars; i++) std::cout << "#"; 
    std::cout << GREY; 
    for (int i = 0; i < pendingBars; i++) std::cout << "-"; 
    std::cout << RESET;

    std::cout << "  " << std::fixed << std::setprecision(1) 
              << completedPercent << "% done, "
              << pendingPercent << "% pending\n";

    utils.waitForUserInput();

    
}