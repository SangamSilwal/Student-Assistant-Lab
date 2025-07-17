#pragma once
#include <string>
#include "../sqlite3.h"

class UserAuth {
    public:
    UserAuth(const std::string& dbpath);
    ~UserAuth();

    bool registerUser(const std::string& username, const std::string& password);
    bool loginUser(const std::string& username, const std::string& password);
    std::string getHiddenPassword(const std::string& prompt);

    private:
    sqlite3* db;
    void createUserTable();

};