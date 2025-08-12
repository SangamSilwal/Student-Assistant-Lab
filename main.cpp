#include "studentValidation/UserAuth.h"
#include "assigments/Assignments.h"
#include "todo-list/TodoList.h"
#include "pomodoroTimer/PomodoroTimer.h"
#include "utility/utils.h"
#include "utility/colorHeader.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <set>
#include <string>
#include <limits>
#include "calender/calender.h"
#include "routine/Routine.h"

// Compilation command:
// gcc main.cpp studentValidation/UserAuth.cpp utility/utils.cpp assigments/Assignment.cpp calender/calender.cpp todo-list/TodoList.cpp sqlite3.c -o app -I. -lstdc++

int main()
{
    sqlite3 *db;
    Utility utils;

    if (sqlite3_open("student.db", &db) != SQLITE_OK)
    {
        utils.printErrorMessage("[X] Failed to open database");
        return 1;
    }

    UserAuth auth(db);
    Assignment assignment(db);
    Routine routine(db);

    utils.clearScreen();
    utils.printWelcomeBanner();

    int choiceOpen = 0;
    std::string username;
    bool loggedIn = false;

    do
    {
        utils.printInputPrompt("1 To Login", "[>]");
        utils.printInputPrompt("2 To Register", "[>]");
        utils.printInputPrompt("3 To Exit", "[>]");
        std::cout << "\nEnter choice: ";
        std::cin >> choiceOpen;

        switch (choiceOpen)
        {
        case 1:
            utils.clearScreen();
            utils.printSectionHeader("Login", "[+]");
            if (!utils.getUserLogin(auth, utils, username))
            {
                utils.printErrorMessage("[X] Login failed");
            }
            else
            {
                int user_id = auth.getUserId(username);
                if (user_id == -1)
                {
                    utils.printErrorMessage("[X] Failed to retrieve user information");
                }
                else
                {
                    loggedIn = true;
                    utils.printSuccessMessage("[SUCCESS] Login successful");
                }
            }
            break;

        case 2:
            utils.clearScreen();
            utils.printSectionHeader("Register", "[+]");
            if (!utils.getUserRegistration(auth, utils))
            {
                utils.printErrorMessage("[X] Registration failed");
            }
            else
            {
                utils.printSuccessMessage("[SUCCESS] Registration successful");
            }
            break;

        case 3:
            utils.printInfoMessage("[X] Exiting...");
            sqlite3_close(db);
            return 0;

        default:
            utils.printErrorMessage("[X] Invalid choice. Try again.");
            return 1;
        }

    } while (!loggedIn);

    int user_id = auth.getUserId(username);
    TodoList todo(db, user_id);

    int choice;
    do
    {
        utils.clearScreen();
        utils.displayMainMenu(utils);

        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            utils.printErrorMessage("[ERROR] Invalid input! Please enter a number between 1-5.");
            utils.waitForUserInput();
            continue;
        }
        std::cin.ignore();

        switch (choice)
        {
        case 1:
        {
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
            if (assignment.addAssignment(user_id, title, description, due_date))
            {
                utils.printSuccessMessage("[SUCCESS] Assignment added successfully!");
            }
            else
            {
                utils.printErrorMessage("[ERROR] Failed to add assignment. Please check your input.");
            }

            utils.waitForUserInput();
            break;
        }

        case 2:
        {
            utils.handleAssignmentMenu(assignment, user_id, utils);
            break;
        }

        case 3:
        {
            utils.clearScreen();
            auto assignments = assignment.getAssignments(user_id);
            printCalendarWithAssignments(assignments, utils);
            utils.waitForUserInput();
            break;
        }

        case 4:
        {
            utils.handleTodoMenu(todo, utils);
            break;
        }
        case 5:
        {
            utils.clearScreen();
            int rChoice;
            bool inRoutineMenu = true; // flag to control the routine menu loop

            while (inRoutineMenu)
            {
                utils.printSectionHeader("ROUTINE MANAGEMENT", "[R]");
                std::cout << CYAN
                          << "1. Add Routine\n2. View Routines\n3. Update Routine\n4. Delete Routine\n5. Back"
                          << RESET << "\n";
                std::cout << "Choose: ";
                std::cin >> rChoice;
                std::cin.ignore();

                if (rChoice == 1)
                {
                    std::string day, start, end, subject;
                    std::cout << "Day: ";
                    std::getline(std::cin, day);
                    std::cout << "Start Time: ";
                    std::getline(std::cin, start);
                    std::cout << "End Time: ";
                    std::getline(std::cin, end);
                    std::cout << "Subject: ";
                    std::getline(std::cin, subject);

                    if (routine.addRoutine(user_id, day, start, end, subject))
                        utils.printSuccessMessage("Routine added.");
                    else
                        utils.printErrorMessage("Failed to add routine.");
                }
                else if (rChoice == 2)
                {
                    auto routines = routine.getRoutines(user_id);
                    if (routines.empty())
                        utils.printInfoMessage("No routines found.");
                    else
                        for (const auto &r : routines)
                            std::cout << YELLOW << "ID: " << r.id << RESET
                                      << " | " << r.day << " | " << r.start_time
                                      << "-" << r.end_time << " | " << r.subject << "\n";
                }
                else if (rChoice == 3)
                {
                    int id;
                    std::string day, start, end, subject;
                    std::cout << "ID: ";
                    std::cin >> id;
                    std::cin.ignore();
                    std::cout << "New Day: ";
                    std::getline(std::cin, day);
                    std::cout << "New Start: ";
                    std::getline(std::cin, start);
                    std::cout << "New End: ";
                    std::getline(std::cin, end);
                    std::cout << "New Subject: ";
                    std::getline(std::cin, subject);

                    if (routine.updateRoutine(id, day, start, end, subject))
                        utils.printSuccessMessage("Updated.");
                    else
                        utils.printErrorMessage("Failed to update.");
                }
                else if (rChoice == 4)
                {
                    int id;
                    std::cout << "ID: ";
                    std::cin >> id;
                    std::cin.ignore();
                    if (routine.deleteRoutine(id))
                        utils.printSuccessMessage("Deleted.");
                    else
                        utils.printErrorMessage("Failed to delete.");
                }
                else if (rChoice == 5)
                {
                    utils.printSuccessMessage("[>] Returning to main menu...");
                    SLEEP(800);
                    inRoutineMenu = false; // break out of routine menu loop
                }
                else
                {
                    utils.printErrorMessage("Invalid choice. Try again.");
                }
            }

            break;
        }

        
        case 6:
        {
            utils.clearScreen();
            utils.printSectionHeader("POMODORO TIMER", "[P]");

            int workMin, breakMin;
            std::cout << "Enter work duration (minutes): ";
            std::cin >> workMin;
            std::cout << "Enter break duration (minutes): ";
            std::cin >> breakMin;
            std::cin.ignore();

            PomodoroTimer pomodoro(workMin, breakMin);

            pomodoro.setWorkStartCallback([&]() {
                utils.printInfoMessage("Work phase started! Stay focused.");
            });
            pomodoro.setBreakStartCallback([&]() {
                utils.printInfoMessage("Break time! Relax.");
            });
            pomodoro.setTimerUpdateCallback([&](int remaining) {
                int m = remaining / 60, s = remaining % 60;
                std::cout << "\rTime Left: " << m << "m " << s << "s   " << std::flush;
            });

            pomodoro.start();

            while (pomodoro.isRunning())
            {
                pomodoro.update();
            }

            break;
        }

        case 7:
        {
            utils.clearScreen();
            utils.printSectionHeader("GOODBYE!", "[!]");
            utils.printSuccessMessage("[SUCCESS] Thank you for using Student Assignment Management System!");
            utils.printInfoMessage("[INFO] Your data has been saved. See you next time!");
            utils.printLine('*', 70, MAGENTA);
            break;
        }

        default:
        {
            utils.printErrorMessage("[ERROR] Invalid choice! Please select a number between 1-5.");
            utils.waitForUserInput();
            break;
        }
        }

    } while (choice != 7);

    sqlite3_close(db);
    return 0;
}
