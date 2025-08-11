#pragma once
#include <string>
#include "../sqlite3.h"

class UserAuth {
    public:
    UserAuth(sqlite3* database);
    ~UserAuth();

    bool registerUser(const std::string& username, const std::string& password);
    bool loginUser(const std::string& username, const std::string& password);
    std::string getHiddenPassword(const std::string& prompt);
    int getUserId(const std::string& username);

    private:
    sqlite3* db;
    void createUserTable();

};