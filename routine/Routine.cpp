#include "Routine.h"
#include <iostream>

void Routine::createRoutineTable() {
    const char* sql =
        "CREATE TABLE IF NOT EXISTS routines ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "student_id INTEGER NOT NULL, "
        "day TEXT NOT NULL, "
        "start_time TEXT NOT NULL, "
        "end_time TEXT NOT NULL, "
        "subject TEXT NOT NULL, "
        "FOREIGN KEY(student_id) REFERENCES users(id)"
        ");";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error creating routines table: " << errMsg << "\n";
        sqlite3_free(errMsg);
    }
}

Routine::Routine(sqlite3* database) : db(database) {
    createRoutineTable();
}

Routine::~Routine() {}

bool Routine::addRoutine(int student_id, const std::string& day, const std::string& start_time, const std::string& end_time, const std::string& subject) {
    const char* sql = "INSERT INTO routines (student_id, day, start_time, end_time, subject) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare addRoutine statement: " << sqlite3_errmsg(db) << "\n";
        return false;
    }

    sqlite3_bind_int(stmt, 1, student_id);
    sqlite3_bind_text(stmt, 2, day.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, start_time.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, end_time.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, subject.c_str(), -1, SQLITE_STATIC);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    if (!success) {
        std::cerr << "Failed to execute addRoutine statement: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    return success;
}

std::vector<RoutineData> Routine::getRoutines(int student_id) {
    std::vector<RoutineData> routines;
    const char* sql = "SELECT id, student_id, day, start_time, end_time, subject FROM routines WHERE student_id = ? ORDER BY day, start_time;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare getRoutines statement: " << sqlite3_errmsg(db) << "\n";
        return routines;
    }

    sqlite3_bind_int(stmt, 1, student_id);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        RoutineData r;
        r.id = sqlite3_column_int(stmt, 0);
        r.student_id = sqlite3_column_int(stmt, 1);
        r.day = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2) ? sqlite3_column_text(stmt, 2) : (const unsigned char*)"");
        r.start_time = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3) ? sqlite3_column_text(stmt, 3) : (const unsigned char*)"");
        r.end_time = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4) ? sqlite3_column_text(stmt, 4) : (const unsigned char*)"");
        r.subject = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5) ? sqlite3_column_text(stmt, 5) : (const unsigned char*)"");
        routines.push_back(r);
    }

    sqlite3_finalize(stmt);
    return routines;
}

bool Routine::updateRoutine(int routine_id, const std::string& day, const std::string& start_time, const std::string& end_time, const std::string& subject) {
    const char* sql = "UPDATE routines SET day = ?, start_time = ?, end_time = ?, subject = ? WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare updateRoutine statement: " << sqlite3_errmsg(db) << "\n";
        return false;
    }

    sqlite3_bind_text(stmt, 1, day.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, start_time.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, end_time.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, subject.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, routine_id);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    if (!success) {
        std::cerr << "Failed to execute updateRoutine statement: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    return success;
}

bool Routine::deleteRoutine(int routine_id) {
    const char* sql = "DELETE FROM routines WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare deleteRoutine statement: " << sqlite3_errmsg(db) << "\n";
        return false;
    }

    sqlite3_bind_int(stmt, 1, routine_id);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    if (!success) {
        std::cerr << "Failed to execute deleteRoutine statement: " << sqlite3_errmsg(db) << "\n";
    }

    sqlite3_finalize(stmt);
    return success;
}