#include "Assignments.h"
#include <iostream>

void Assignment::createAssignmentTable() {
    const char* sql = "CREATE TABLE IF NOT EXISTS assignments ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "student_id INTEGER NOT NULL, "
                      "title TEXT NOT NULL, "
                      "description TEXT, "
                      "due_date TEXT NOT NULL, "
                      "status TEXT DEFAULT 'pending', "
                      "FOREIGN KEY(student_id) REFERENCES users(id)"
                      ");";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error creating assignments table: " << errMsg << "\n";
        sqlite3_free(errMsg);
    }
}

Assignment::Assignment(sqlite3* database) : db(database) {
    createAssignmentTable();
}


Assignment::~Assignment() {}


bool Assignment::addAssignment(int student_id, const std::string& title, const std::string& description, const std::string& due_date) {
    const char* sql = "INSERT INTO assignments (student_id, title, description, due_date, status) VALUES (?, ?, ?, ?, 'pending');";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        return false;
    }

    sqlite3_bind_int(stmt, 1, student_id);
    sqlite3_bind_text(stmt, 2, title.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, description.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, due_date.c_str(), -1, SQLITE_STATIC);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    if (!success) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    return success;
}


std::vector<AssignmentData> Assignment::getAssignments(int student_id) {
    std::vector<AssignmentData> assignments;
    const char* sql = "SELECT id, student_id, title, description, due_date, status FROM assignments WHERE student_id = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        return assignments;
    }

    sqlite3_bind_int(stmt, 1, student_id);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        AssignmentData a;
        a.id = sqlite3_column_int(stmt, 0);
        a.student_id = sqlite3_column_int(stmt, 1);
        a.title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        a.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        a.due_date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        a.status = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        assignments.push_back(a);
    }

    sqlite3_finalize(stmt);
    return assignments;
}


bool Assignment::updateAssignmentStatus(int assignment_id, const std::string& status) {
    const char* sql = "UPDATE assignments SET status = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        return false;
    }

    sqlite3_bind_text(stmt, 1, status.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, assignment_id);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    if (!success) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    return success;
}


bool Assignment::deleteAssignment(int assignment_id) {
    const char* sql = "DELETE FROM assignments WHERE id = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        return false;
    }

    sqlite3_bind_int(stmt, 1, assignment_id);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    if (!success) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    return success;
}
