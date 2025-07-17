#include "UserAuth.h"
#include <iostream>
#include <conio.h> 

UserAuth::UserAuth(const std::string& dbpath) : db(nullptr) {
    if (sqlite3_open(dbpath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Cannot open database.\n";
        db = nullptr;
    } else {
        createUserTable();
    }
}

UserAuth::~UserAuth() {
    if (db) sqlite3_close(db);
}


/**
 * UserAuth::createUserTable function has const char* sql query
 * It also has char* errMsg = nullptr
 * from the sqlite.c we use sqlite3_exec which takes db_name, sql query and nullptr for unnecessay callback function
 * if the resposne is not equal to SQLITE_OK then this will return an error otherwise create a Table if it doesnot exists
 */
void UserAuth::createUserTable() {
    const char* sql = "CREATE TABLE IF NOT EXISTS users("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "username TEXT UNIQUE NOT NULL, "
                      "password TEXT NOT NULL);";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Table creation failed: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}


/**
 * UserAuth::registerUser takes username and password and return boolean as success or false
 * sqlite3_stmt* stmt --> is a type defined in sqlite which contain compiled SQL queries
 * SQLITE_STATIC --> It tells how long the statement will remain valid in the sqllite memory
 * sqlite3_step --> It execute the Query
 * sqlite3_finalize --> It finalize the resources associated with sqllite
 */
bool UserAuth::registerUser(const std::string& username, const std::string& password) {
    const char* sql = "INSERT INTO users (username, password) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

/**
 * The UserAuth::loginUser method attempts to authenticate a user by checking the provided username and password against a database using an SQL query.
 *  It prepares and executes the query, binds the input parameters, and returns true if a matching record is found, otherwise false
 */
bool UserAuth::loginUser(const std::string& username, const std::string& password) {
    const char* sql = "SELECT id FROM users WHERE username = ? AND password = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    bool found = (sqlite3_step(stmt) == SQLITE_ROW);
    sqlite3_finalize(stmt);
    return found;
}


/**
 * UserAuth::getHiddenPassword is a method that prompts the user for a password using the provided prompt string, hides the input by displaying asterisks (*), and returns the entered password as a std::string. 
 * It handles backspace for deleting characters, exits the program if the user presses Ctrl+C, and concludes input upon pressing Enter.
 */
std::string UserAuth::getHiddenPassword(const std::string& prompt) {
    std::string password;
    char ch;
    std::cout << prompt;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b";
            }
        } else if (ch == 3) {
            exit(0);
        } else {
            password.push_back(ch);
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return password;
}