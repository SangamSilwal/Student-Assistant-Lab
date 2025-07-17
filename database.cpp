#include <iostream>
#include "sqlite3.h"

int main() {
    sqlite3* db;
    char* errorMessage = 0;

    // Open database (it will create it if it doesn't exist)
    int exit = sqlite3_open("student.db", &db);

    if (exit) {
        std::cerr << "Error opening DB: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    } else {
        std::cout << "Opened database successfully!" << std::endl;
    }

    // SQL command to create a table
    const char* createTableQuery = "CREATE TABLE IF NOT EXISTS students("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                   "name TEXT NOT NULL, "
                                   "age INTEGER NOT NULL);";

    // Execute SQL
    exit = sqlite3_exec(db, createTableQuery, NULL, 0, &errorMessage);

    if (exit != SQLITE_OK) {
        std::cerr << "Error creating table: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    } else {
        std::cout << "Table created successfully!" << std::endl;
    }

    sqlite3_close(db);
    return 0;
}
