#include "studentValidation/UserAuth.h"
#include "assigments/Assignments.h"
#include "todo-list/TodoList.h"
#include "utility/utils.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <set>
#include <string>
#include <limits>
#include "calender/calender.h"

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define BOLD "\033[1m"

int main()
{
    sqlite3 *db;
    Utility utils;
    if (sqlite3_open("student.db", &db) != SQLITE_OK)
    {
        utils.printErrorMessage("Failed to open database");
        return 1;
    }

    UserAuth auth(db);
    Assignment assignment(db);

    utils.printWelcomeBanner();

    utils.printSectionHeader("USER REGISTRATION", "[+]");

    std::string username, password;
    utils.printInputPrompt("Enter Username: ", "[USER]");
    std::cin >> username;
    std::cin.ignore();

    password = auth.getHiddenPassword("[PASS] Enter Password: ");

    if (auth.registerUser(username, password))
    {
        utils.printSuccessMessage("Registration completed successfully!");
    }
    else
    {
        utils.printErrorMessage("Registration failed! Username might already exist.");
    }

    std::cout << std::endl;

    utils.printSectionHeader("USER LOGIN", "[>]");

    utils.printInputPrompt("Enter Username: ", "[USER]");
    std::cin >> username;
    std::cin.ignore();

    password = auth.getHiddenPassword("[PASS] Enter Password: ");

    if (!auth.loginUser(username, password))
    {
        utils.printErrorMessage("Login failed! Invalid credentials.");
        sqlite3_close(db);
        return 1;
    }

    utils.printSuccessMessage("Welcome back, " + username + "! Login successful.");

    int user_id = auth.getUserId(username);
    if (user_id == -1)
    {
        utils.printErrorMessage("Failed to retrieve user information");
        sqlite3_close(db);
        return 1;
    }

    TodoList todo(db, user_id);

    int choice;
    do
    {
        utils.printMenu();

        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            utils.printErrorMessage("Invalid input! Please enter a number between 1-4.");
            continue;
        }
        std::cin.ignore();

        switch (choice)
        {
        case 1:
        {
            utils.printSectionHeader("ADD NEW ASSIGNMENT", "[+]");

            std::string title, description, due_date;

            utils.printInputPrompt("Assignment Title: ", "[TITLE]");
            std::getline(std::cin, title);

            utils.printInputPrompt("Description: ", "[DESC]");
            std::getline(std::cin, description);

            utils.printInputPrompt("Due Date (YYYY-MM-DD): ", "[DATE]");
            std::getline(std::cin, due_date);

            if (assignment.addAssignment(user_id, title, description, due_date))
            {
                utils.printSuccessMessage("Assignment added successfully!");
            }
            else
            {
                utils.printErrorMessage("Failed to add assignment. Please check your input.");
            }
            break;
        }

        case 2:
        {
            utils.printSectionHeader("YOUR ASSIGNMENTS", "[*]");

            auto assignments = assignment.getAssignments(user_id);
            if (assignments.empty())
            {
                utils.printInfoMessage("No assignments found. Add some assignments to get started!");
            }
            else
            {
                std::cout << BLUE << "[COUNT] " << RESET << "Total Assignments: " << YELLOW << assignments.size() << RESET << std::endl;
                utils.printLine('-', 60, BLUE);

                for (size_t i = 0; i < assignments.size(); i++)
                {
                    const auto &a = assignments[i];
                    std::cout << YELLOW << "Assignment #" << (i + 1) << RESET << std::endl;
                    std::cout << CYAN << " ID: " << RESET << a.id << std::endl;
                    std::cout << CYAN << " Title: " << RESET << a.title << std::endl;
                    std::cout << CYAN << " Description: " << RESET << a.description << std::endl;
                    std::cout << CYAN << " Due Date: " << RESET << a.due_date << std::endl;

                    if (i < assignments.size() - 1)
                    {
                        utils.printLine('.', 40, BLUE);
                    }
                }
            }
            utils.printLine('=', 60, MAGENTA);
            break;
        }

        case 3:
        {
            auto assignments = assignment.getAssignments(user_id);
            printCalendarWithAssignments(assignments, utils);
            break;
        }
        case 4:
        {
            utils.clearScreen();
            int choice;
            while (true)
            {
                utils.printSectionHeader("YOUR ASSIGNMENTS", "[*]");
                std::cout << CYAN << "1. Add Work" << RESET << std::endl;
                std::cout << CYAN << "2. Remove Work" << RESET << std::endl;
                std::cout << CYAN << "3. View Work" << RESET << std::endl;
                std::cout << CYAN << "4. Mark Task Done" << RESET << std::endl;
                std::cout << "Choose: ";
                std::cin >> choice;
                std::cin.ignore();

                if (choice == 1)
                {
                    std::string task;
                    std::cout << "Enter task: ";
                    std::getline(std::cin, task);
                    todo.addTask(task);
                }
                else if (choice == 2)
                {
                    int id;
                    std::cout << "Enter task ID to remove: ";
                    std::cin >> id;
                    todo.removeTask(id);
                }
                else if (choice == 3)
                {
                    todo.viewTasks();
                }
                else if (choice == 4)
                {
                    int id;
                    std::cout << "Enter task ID to mark done: ";
                    std::cin >> id;
                    std::cin.ignore();
                    todo.markTaskDone(id);
                }
            }

            break;
        }

        case 5:
        {
            utils.printSectionHeader("GOODBYE!", "[!]");
            utils.printSuccessMessage("Thank you for using Student Assignment Management System!");
            utils.printInfoMessage("Your data has been saved. See you next time!");
            utils.printLine('*', 70, MAGENTA);
            break;
        }

        default:
        {
            utils.printErrorMessage("Invalid choice! Please select a number between 1-4.");
            break;
        }
        }

        if (choice != 4)
        {
            std::cout << std::endl
                      << YELLOW << "[PAUSE] " << RESET << "Press Enter to continue...";
            std::cin.get();
            utils.clearScreen();
        }

    } while (choice != 4);

    sqlite3_close(db);
    return 0;
}