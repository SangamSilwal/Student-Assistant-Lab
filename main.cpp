
#include "studentValidation/UserAuth.h"
#include <iostream>

int main() {
    UserAuth auth("student.db");

    std::string username, password;
    std::cout << "Register\nUsername: ";
    std::cin >> username;
    password = auth.getHiddenPassword("Password: ");

    if (auth.registerUser(username, password))
        std::cout << "Registration successful!\n";
    else
        std::cout << "Registration failed!\n";

    std::cout << "Login\nUsername: ";
    std::cin >> username;
    password = auth.getHiddenPassword("Password: ");

    if (auth.loginUser(username, password))
        std::cout << "Login successful!\n";
    else
        std::cout << "Login failed!\n";

    return 0;
}