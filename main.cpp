#include "studentValidation/UserAuth.h"
#include "assigments/Assignments.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <set>
#include <string>
#include <limits>

// ANSI Color Codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

// Function to clear screen (cross-platform)
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Function to print a decorative line
void printLine(char c = '=', int length = 60, const std::string& color = CYAN) {
    std::cout << color;
    for (int i = 0; i < length; i++) {
        std::cout << c;
    }
    std::cout << RESET << std::endl;
}

// Function to print centered text
void printCentered(const std::string& text, int width = 60, const std::string& color = WHITE) {
    int padding = (width - text.length()) / 2;
    std::cout << color << std::string(padding, ' ') << text << RESET << std::endl;
}

// Function to print welcome banner
void printWelcomeBanner() {
    clearScreen();
    printLine('*', 70, MAGENTA);
    printCentered(BOLD "STUDENT ASSIGNMENT MANAGEMENT SYSTEM" RESET, 70, YELLOW);
    printCentered("Your Personal Academic Organizer", 70, CYAN);
    printLine('*', 70, MAGENTA);
    std::cout << std::endl;
}

// Function to print menu with attractive formatting
void printMenu() {
    std::cout << std::endl;
    printLine('-', 50, BLUE);
    printCentered(BOLD "MAIN MENU" RESET, 50, YELLOW);
    printLine('-', 50, BLUE);
    
    std::cout << GREEN << " 1. [+] " << CYAN << "Add New Assignment" << RESET << std::endl;
    std::cout << GREEN << " 2. [*] " << CYAN << "View All Assignments" << RESET << std::endl;
    std::cout << GREEN << " 3. [@] " << CYAN << "View Assignment Calendar" << RESET << std::endl;
    std::cout << GREEN << " 4. [X] " << CYAN << "Exit System" << RESET << std::endl;
    
    printLine('-', 50, BLUE);
    std::cout << YELLOW << " >> " << BOLD << "Enter your choice (1-4): " << RESET;
}

// Function to print section headers
void printSectionHeader(const std::string& title, const std::string& icon = "[*]") {
    std::cout << std::endl;
    printLine('=', 60, MAGENTA);
    printCentered(BOLD + icon + " " + title + " " + icon + RESET, 60, YELLOW);
    printLine('=', 60, MAGENTA);
    std::cout << std::endl;
}

// Enhanced input prompts
void printInputPrompt(const std::string& prompt, const std::string& icon = "[>]") {
    std::cout << GREEN << BOLD << icon << " " << CYAN << prompt << RESET;
}

// Success/Error message functions
void printSuccessMessage(const std::string& message) {
    std::cout << GREEN << BOLD << "[✓ SUCCESS] " << RESET << GREEN << message << RESET << std::endl;
}

void printErrorMessage(const std::string& message) {
    std::cout << RED << BOLD << "[✗ ERROR] " << RESET << RED << message << RESET << std::endl;
}

void printInfoMessage(const std::string& message) {
    std::cout << BLUE << BOLD << "[i INFO] " << RESET << BLUE << message << RESET << std::endl;
}

void printWarningMessage(const std::string& message) {
    std::cout << YELLOW << BOLD << "[! WARNING] " << RESET << YELLOW << message << RESET << std::endl;
}

// Helper: Extract day from "YYYY-MM-DD"
int getDayFromDate(const std::string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') return -1;
    try {
        return std::stoi(date.substr(8, 2));
    } catch (...) {
        return -1;
    }
}

// Enhanced calendar display with colors
void printCalendarWithAssignments(const std::vector<AssignmentData>& assignments) {
    time_t now = time(nullptr);
    if (now == -1) {
        printErrorMessage("Failed to get current time");
        return;
    }
    
    tm* localtm = localtime(&now);
    if (!localtm) {
        printErrorMessage("Failed to get local time");
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

    printSectionHeader("ASSIGNMENT CALENDAR", "[@]");
    
    std::string monthNames[] = {"", "January", "February", "March", "April", "May", "June",
                               "July", "August", "September", "October", "November", "December"};
    printCentered(BOLD + monthNames[month] + " " + std::to_string(year) + RESET, 30, YELLOW);
    std::cout << std::endl;
    
    std::cout << MAGENTA << " Su  Mo  Tu  We  Th  Fr  Sa" << RESET << std::endl;
    printLine('-', 28, BLUE);

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
    printLine('=', 60, MAGENTA);
}

int main() {
    sqlite3* db;
    if (sqlite3_open("student.db", &db) != SQLITE_OK) {
        printErrorMessage("Failed to open database");
        return 1;
    }

    UserAuth auth(db);
    Assignment assignment(db);

    printWelcomeBanner();
    
    // Registration Section
    printSectionHeader("USER REGISTRATION", "[+]");
    
    std::string username, password;
    printInputPrompt("Enter Username: ", "[USER]");
    std::cin >> username;
    std::cin.ignore();
    
    password = auth.getHiddenPassword("[PASS] Enter Password: ");

    if (auth.registerUser(username, password)) {
        printSuccessMessage("Registration completed successfully!");
    } else {
        printErrorMessage("Registration failed! Username might already exist.");
    }

    std::cout << std::endl;
    
    // Login Section
    printSectionHeader("USER LOGIN", "[>]");
    
    printInputPrompt("Enter Username: ", "[USER]");
    std::cin >> username;
    std::cin.ignore();
    
    password = auth.getHiddenPassword("[PASS] Enter Password: ");

    if (!auth.loginUser(username, password)) {
        printErrorMessage("Login failed! Invalid credentials.");
        sqlite3_close(db);
        return 1;
    }
    
    printSuccessMessage("Welcome back, " + username + "! Login successful.");

    int user_id = auth.getUserId(username);
    if (user_id == -1) {
        printErrorMessage("Failed to retrieve user information");
        sqlite3_close(db);
        return 1;
    }

    // Main application loop
    int choice;
    do {
        printMenu();
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            printErrorMessage("Invalid input! Please enter a number between 1-4.");
            continue;
        }
        std::cin.ignore();

        switch (choice) {
            case 1: {
                printSectionHeader("ADD NEW ASSIGNMENT", "[+]");
                
                std::string title, description, due_date;
                
                printInputPrompt("Assignment Title: ", "[TITLE]");
                std::getline(std::cin, title);
                
                printInputPrompt("Description: ", "[DESC]");
                std::getline(std::cin, description);
                
                printInputPrompt("Due Date (YYYY-MM-DD): ", "[DATE]");
                std::getline(std::cin, due_date);

                if (assignment.addAssignment(user_id, title, description, due_date)) {
                    printSuccessMessage("Assignment added successfully!");
                } else {
                    printErrorMessage("Failed to add assignment. Please check your input.");
                }
                break;
            }

            case 2: {
                printSectionHeader("YOUR ASSIGNMENTS", "[*]");
                
                auto assignments = assignment.getAssignments(user_id);
                if (assignments.empty()) {
                    printInfoMessage("No assignments found. Add some assignments to get started!");
                } else {
                    std::cout << BLUE << "[COUNT] " << RESET << "Total Assignments: " << YELLOW << assignments.size() << RESET << std::endl;
                    printLine('-', 60, BLUE);
                    
                    for (size_t i = 0; i < assignments.size(); i++) {
                        const auto& a = assignments[i];
                        std::cout << YELLOW << "Assignment #" << (i+1) << RESET << std::endl;
                        std::cout << CYAN << " ID: " << RESET << a.id << std::endl;
                        std::cout << CYAN << " Title: " << RESET << a.title << std::endl;
                        std::cout << CYAN << " Description: " << RESET << a.description << std::endl;
                        std::cout << CYAN << " Due Date: " << RESET << a.due_date << std::endl;
                        
                        if (i < assignments.size() - 1) {
                            printLine('.', 40, BLUE);
                        }
                    }
                }
                printLine('=', 60, MAGENTA);
                break;
            }

            case 3: {
                auto assignments = assignment.getAssignments(user_id);
                printCalendarWithAssignments(assignments);
                break;
            }

            case 4: {
                printSectionHeader("GOODBYE!", "[!]");
                printSuccessMessage("Thank you for using Student Assignment Management System!");
                printInfoMessage("Your data has been saved. See you next time!");
                printLine('*', 70, MAGENTA);
                break;
            }

            default: {
                printErrorMessage("Invalid choice! Please select a number between 1-4.");
                break;
            }
        }

        if (choice != 4) {
            std::cout << std::endl << YELLOW << "[PAUSE] " << RESET << "Press Enter to continue...";
            std::cin.get();
            clearScreen();
        }

    } while (choice != 4);

    sqlite3_close(db);
    return 0;
}