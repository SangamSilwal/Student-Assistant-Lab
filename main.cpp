#include "studentValidation/UserAuth.h"
#include "assigments/Assignments.h"
#include "todo-list/TodoList.h"
#include "utility/utils.h"
#include "utility/colorHeader.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <set>
#include <string>
#include <limits>
#include "calender/calender.h"


// Compilation command:
// gcc main.cpp studentValidation/UserAuth.cpp utility/utils.cpp assigments/Assignment.cpp calender/calender.cpp todo-list/TodoList.cpp sqlite3.c -o app -I. -lstdc++



int main() {
    sqlite3 *db;
    Utility utils;
    
    
    if (sqlite3_open("student.db", &db) != SQLITE_OK) {
        utils.printErrorMessage("[X] Failed to open database");
        return 1;
    }

    UserAuth auth(db);
    Assignment assignment(db);

    
    utils.clearScreen();
    utils.printWelcomeBanner();

    
    if (!utils.getUserRegistration(auth, utils)) {
        sqlite3_close(db);
        return 1;
    }

    std::cout << std::endl;

    
    std::string username;
    if (!utils.getUserLogin(auth, utils, username)) {
        sqlite3_close(db);
        return 1;
    }

    
    int user_id = auth.getUserId(username);
    if (user_id == -1) {
        utils.printErrorMessage("[X] Failed to retrieve user information");
        sqlite3_close(db);
        return 1;
    }

    TodoList todo(db, user_id);

    
    int choice;
    do {
        utils.clearScreen();
        utils.displayMainMenu(utils);

        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            utils.printErrorMessage("[ERROR] Invalid input! Please enter a number between 1-5.");
            utils.waitForUserInput();
            continue;
        }
        std::cin.ignore();

        switch (choice) {
            case 1: {
                utils.clearScreen();
                utils.printSectionHeader("ADD NEW ASSIGNMENT", "[+]");

                std::string title, description, due_date;

                utils.printInputPrompt("Assignment Title: ", "[TITLE]");
                std::getline(std::cin, title);

                utils.printInputPrompt("Description: ", "[DESC]");
                std::getline(std::cin, description);

                utils.printInputPrompt("Due Date (YYYY-MM-DD): ", "[DATE]");
                std::getline(std::cin, due_date);

                std::cout << std::endl;
                if (assignment.addAssignment(user_id, title, description, due_date)) {
                    utils.printSuccessMessage("[SUCCESS] Assignment added successfully!");
                } else {
                    utils.printErrorMessage("[ERROR] Failed to add assignment. Please check your input.");
                }
                
                utils.waitForUserInput();
                break;
            }

            case 2: {
                utils.handleAssignmentMenu(assignment, user_id, utils);
                break;
            }

            case 3: {
                utils.clearScreen();
                auto assignments = assignment.getAssignments(user_id);
                printCalendarWithAssignments(assignments, utils);
                utils.waitForUserInput();
                break;
            }

            case 4: {
                utils.handleTodoMenu(todo, utils);
                break;
            }

            case 5: {
                utils.clearScreen();
                utils.printSectionHeader("GOODBYE!", "[!]");
                utils.printSuccessMessage("[SUCCESS] Thank you for using Student Assignment Management System!");
                utils.printInfoMessage("[INFO] Your data has been saved. See you next time!");
                utils.printLine('*', 70, MAGENTA);
                break;
            }

            default: {
                utils.printErrorMessage("[ERROR] Invalid choice! Please select a number between 1-5.");
                utils.waitForUserInput();
                break;
            }
        }

    } while (choice != 5);

    sqlite3_close(db);
    return 0;
}

