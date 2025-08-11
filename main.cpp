#include "studentValidation/UserAuth.h"
#include "assigments/Assignments.h"
#include "utility/utils.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <set>
#include <string>
#include <limits>


#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"



int getDayFromDate(const std::string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') return -1;
    try {
        return std::stoi(date.substr(8, 2));
    } catch (...) {
        return -1;
    }
}


void printCalendarWithAssignments(const std::vector<AssignmentData>& assignments,Utility utils) {
    time_t now = time(nullptr);
    if (now == -1) {
        utils.printErrorMessage("Failed to get current time");
        return;
    }
    
    tm* localtm = localtime(&now);
    if (!localtm) {
        utils.printErrorMessage("Failed to get local time");
        return;
    }
    
    int year = 1900 + localtm->tm_year;
    int month = 1 + localtm->tm_mon;

    tm firstDay = {0};
    firstDay.tm_year = localtm->tm_year;
    firstDay.tm_mon = localtm->tm_mon;
    firstDay.tm_mday = 1;
    mktime(&firstDay);
    int startWeekday = firstDay.tm_wday;
    int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int dim = daysInMonth[month - 1];

    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        dim = 29;
    }
    std::set<int> dueDays;
    for (const auto& a : assignments) {
        std::string prefix = std::to_string(year) + "-" + (month < 10 ? "0" : "") + std::to_string(month) + "-";
        if (a.due_date.substr(0, 7) == prefix.substr(0, 7)) {
            int day = getDayFromDate(a.due_date);
            if (day > 0) dueDays.insert(day);
        }
    }
    utils.printSectionHeader("ASSIGNMENT CALENDAR", "[@]");
    std::string monthNames[] = {"", "January", "February", "March", "April", "May", "June",
                               "July", "August", "September", "October", "November", "December"};
    utils.printCentered(BOLD + monthNames[month] + " " + std::to_string(year) + RESET, 30, YELLOW);
    std::cout << std::endl;
    
    std::cout << MAGENTA << " Su  Mo  Tu  We  Th  Fr  Sa" << RESET << std::endl;
    utils.printLine('-', 28, BLUE);

    for (int i = 0; i < startWeekday; i++) std::cout << "    ";

    for (int day = 1; day <= dim; day++) {
        if (dueDays.count(day)) {
            std::cout << RED << BOLD << std::setw(2) << day << "*" << RESET << " ";
        } else {
            std::cout << CYAN << std::setw(2) << day << RESET << "  ";
        }

        if ((startWeekday + day) % 7 == 0 || day == dim) 
            std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << RED << BOLD << "*" << RESET << " = Assignment due dates" << std::endl;
    utils.printLine('=', 60, MAGENTA);
}

int main() {
    sqlite3* db;
    Utility utils;
    if (sqlite3_open("student.db", &db) != SQLITE_OK) {
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

    if (auth.registerUser(username, password)) {
        utils.printSuccessMessage("Registration completed successfully!");
    } else {
        utils.printErrorMessage("Registration failed! Username might already exist.");
    }

    std::cout << std::endl;
    

    utils.printSectionHeader("USER LOGIN", "[>]");
    
    utils.printInputPrompt("Enter Username: ", "[USER]");
    std::cin >> username;
    std::cin.ignore();
    
    password = auth.getHiddenPassword("[PASS] Enter Password: ");

    if (!auth.loginUser(username, password)) {
        utils.printErrorMessage("Login failed! Invalid credentials.");
        sqlite3_close(db);
        return 1;
    }
    
    utils.printSuccessMessage("Welcome back, " + username + "! Login successful.");

    int user_id = auth.getUserId(username);
    if (user_id == -1) {
        utils.printErrorMessage("Failed to retrieve user information");
        sqlite3_close(db);
        return 1;
    }


    int choice;
    do {
        utils.printMenu();
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            utils.printErrorMessage("Invalid input! Please enter a number between 1-4.");
            continue;
        }
        std::cin.ignore();

        switch (choice) {
            case 1: {
                utils.printSectionHeader("ADD NEW ASSIGNMENT", "[+]");
                
                std::string title, description, due_date;
                
                utils.printInputPrompt("Assignment Title: ", "[TITLE]");
                std::getline(std::cin, title);
                
                utils.printInputPrompt("Description: ", "[DESC]");
                std::getline(std::cin, description);
                
                utils.printInputPrompt("Due Date (YYYY-MM-DD): ", "[DATE]");
                std::getline(std::cin, due_date);

                if (assignment.addAssignment(user_id, title, description, due_date)) {
                    utils.printSuccessMessage("Assignment added successfully!");
                } else {
                    utils.printErrorMessage("Failed to add assignment. Please check your input.");
                }
                break;
            }

            case 2: {
                utils.printSectionHeader("YOUR ASSIGNMENTS", "[*]");
                
                auto assignments = assignment.getAssignments(user_id);
                if (assignments.empty()) {
                    utils.printInfoMessage("No assignments found. Add some assignments to get started!");
                } else {
                    std::cout << BLUE << "[COUNT] " << RESET << "Total Assignments: " << YELLOW << assignments.size() << RESET << std::endl;
                    utils.printLine('-', 60, BLUE);
                    
                    for (size_t i = 0; i < assignments.size(); i++) {
                        const auto& a = assignments[i];
                        std::cout << YELLOW << "Assignment #" << (i+1) << RESET << std::endl;
                        std::cout << CYAN << " ID: " << RESET << a.id << std::endl;
                        std::cout << CYAN << " Title: " << RESET << a.title << std::endl;
                        std::cout << CYAN << " Description: " << RESET << a.description << std::endl;
                        std::cout << CYAN << " Due Date: " << RESET << a.due_date << std::endl;
                        
                        if (i < assignments.size() - 1) {
                            utils.printLine('.', 40, BLUE);
                        }
                    }
                }
                utils.printLine('=', 60, MAGENTA);
                break;
            }

            case 3: {
                auto assignments = assignment.getAssignments(user_id);
                printCalendarWithAssignments(assignments,utils);
                break;
            }

            case 4: {
                utils.printSectionHeader("GOODBYE!", "[!]");
                utils.printSuccessMessage("Thank you for using Student Assignment Management System!");
                utils.printInfoMessage("Your data has been saved. See you next time!");
                utils.printLine('*', 70, MAGENTA);
                break;
            }

            default: {
                utils.printErrorMessage("Invalid choice! Please select a number between 1-4.");
                break;
            }
        }

        if (choice != 4) {
            std::cout << std::endl << YELLOW << "[PAUSE] " << RESET << "Press Enter to continue...";
            std::cin.get();
            utils.clearScreen();
        }

    } while (choice != 4);

    sqlite3_close(db);
    return 0;
}