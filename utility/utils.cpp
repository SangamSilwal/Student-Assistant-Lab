

#include "utils.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <set>
#include <string>
#include <limits>

void Utility::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Utility::printLine(char c, int length, const std::string& color) {
    std::cout << color;
    for (int i = 0; i < length; i++) {
        std::cout << c;
    }
    std::cout << RESET << std::endl;
}

void Utility::printCentered(const std::string& text, int width, const std::string& color) {
    int padding = (width - text.length()) / 2;
    std::cout << color << std::string(padding, ' ') << text << RESET << std::endl;
}

void Utility::printWelcomeBanner() {
    clearScreen();
    printLine('*', 70, MAGENTA);
    printCentered(BOLD "STUDENT ASSIGNMENT MANAGEMENT SYSTEM" RESET, 70, YELLOW);
    printCentered("Your Personal Academic Organizer", 70, CYAN);
    printLine('*', 70, MAGENTA);
    std::cout << std::endl;
}

void Utility::printMenu() {
    std::cout << std::endl;
    printLine('-', 50, BLUE);
    printCentered(BOLD "MAIN MENU" RESET, 50, YELLOW);
    printLine('-', 50, BLUE);
    
    std::cout << GREEN << " 1. [+] " << CYAN << "Add New Assignment" << RESET << std::endl;
    std::cout << GREEN << " 2. [*] " << CYAN << "View All Assignments" << RESET << std::endl;
    std::cout << GREEN << " 3. [@] " << CYAN << "View Assignment Calendar" << RESET << std::endl;
    std::cout << GREEN << " 4. [T] " << CYAN << "Todo List" << RESET << std::endl;
    std::cout << GREEN << " 5. [X] " << CYAN << "Exit System" << RESET << std::endl;
    
    printLine('-', 50, BLUE);
    std::cout << YELLOW << " >> " << BOLD << "Enter your choice (1-4): " << RESET;
}

void Utility::printSectionHeader(const std::string& title, const std::string& icon ) {
    std::cout << std::endl;
    printLine('=', 60, MAGENTA);
    printCentered(BOLD + icon + " " + title + " " + icon + RESET, 60, YELLOW);
    printLine('=', 60, MAGENTA);
    std::cout << std::endl;
}

void Utility::printInputPrompt(const std::string& prompt, const std::string& icon ) {
    std::cout << GREEN << BOLD << icon << " " << CYAN << prompt << RESET;
}


void Utility::printSuccessMessage(const std::string& message) {
    std::cout << GREEN << BOLD << "[✓ SUCCESS] " << RESET << GREEN << message << RESET << std::endl;
}

void Utility:: printErrorMessage(const std::string& message) {
    std::cout << RED << BOLD << "[✗ ERROR] " << RESET << RED << message << RESET << std::endl;
}

void Utility::printInfoMessage(const std::string& message) {
    std::cout << BLUE << BOLD << "[i INFO] " << RESET << BLUE << message << RESET << std::endl;
}

void Utility::printWarningMessage(const std::string& message) {
    std::cout << YELLOW << BOLD << "[! WARNING] " << RESET << YELLOW << message << RESET << std::endl;
}

void Utility::displayMainMenu(Utility &utils) {
    utils.printSectionHeader("MAIN MENU", "[*]");
    
    std::cout << BRIGHT_GREEN << BG_BLACK << "+=========================================+" << RESET << std::endl;
    std::cout << BRIGHT_GREEN << BG_BLACK << "| " << RESET << BG_BLUE << WHITE << BOLD << "   Student Management System           " << RESET << BRIGHT_GREEN << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BRIGHT_GREEN << BG_BLACK << "+=========================================+" << RESET << std::endl;
    std::cout << BG_BLACK << "| " << CYAN << BOLD << "1." << RESET << BG_BLACK << WHITE << " Add New Assignment                " << RESET << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BG_BLACK << "| " << CYAN << BOLD << "2." << RESET << BG_BLACK << WHITE << " View All Assignments              " << RESET << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BG_BLACK << "| " << CYAN << BOLD << "3." << RESET << BG_BLACK << WHITE << " View Calendar                     " << RESET << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BG_BLACK << "| " << CYAN << BOLD << "4." << RESET << BG_BLACK << WHITE << " Manage Todo List                  " << RESET << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BG_BLACK << "| " << CYAN << BOLD << "5." << RESET << BG_BLACK << WHITE << " Exit Application                  " << RESET << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BRIGHT_GREEN << BG_BLACK << "+=========================================+" << RESET << std::endl;
    std::cout << std::endl;
    
    utils.printInputPrompt("Choose an option (1-5): ", "[>]");
}

void Utility::handleAssignmentMenu(Assignment &assignment, int user_id, Utility &utils) {
    utils.clearScreen();
    utils.printSectionHeader("YOUR ASSIGNMENTS", "[*]");

    auto assignments = assignment.getAssignments(user_id);
    if (assignments.empty()) {
        std::cout << YELLOW << BG_BLACK << "+=========================================+" << RESET << std::endl;
        std::cout << YELLOW << BG_BLACK << "| " << RESET << BG_RED << WHITE << BOLD << "       No assignments found!           " << RESET << YELLOW << BG_BLACK << "|" << RESET << std::endl;
        std::cout << YELLOW << BG_BLACK << "| " << RESET << BG_YELLOW << BLUE << " Add some assignments to get started! " << RESET << YELLOW << BG_BLACK << "|" << RESET << std::endl;
        std::cout << YELLOW << BG_BLACK << "+=========================================+" << RESET << std::endl;
    } else {
        std::cout << BG_BLUE << WHITE << BOLD << "[INFO] Total Assignments: " << BG_YELLOW << BLUE << " " << assignments.size() << " " << RESET << std::endl;
        utils.printLine('=', 60, BLUE);
        std::cout << std::endl;

        for (size_t i = 0; i < assignments.size(); i++) {
            const auto &a = assignments[i];
            
            std::cout << BG_YELLOW << BLUE << BOLD << "[" << (i + 1) << "] Assignment Details:" << RESET << std::endl;
            std::cout << BG_BLACK << "  ID: " << CYAN << BOLD << a.id << RESET << std::endl;
            std::cout << BG_BLACK << "  Title: " << WHITE << BOLD << a.title << RESET << std::endl;
            std::cout << BG_BLACK << "  Description: " << WHITE << a.description << RESET << std::endl;
            std::cout << BG_BLACK << "  Due Date: " << BG_GREEN << WHITE << BOLD << " " << a.due_date << " " << RESET << std::endl;

            if (i < assignments.size() - 1) {
                utils.printLine('-', 40, DIM);
                std::cout << std::endl;
            }
        }
    }
    
    std::cout << std::endl;
    utils.printLine('=', 60, MAGENTA);
    waitForUserInput();
}

void Utility::handleTodoMenu(TodoList &todo, Utility &utils) {
    int choice;
    
    while (true) {
        utils.clearScreen();
        displayTodoSubMenu(utils);

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            utils.printErrorMessage(" Invalid input! Please enter a valid number.");
            waitForUserInput();
            continue;
        }
        std::cin.ignore();

        switch (choice) {
            case 1: {
                // Add task
                std::cout << std::endl;
                std::string task;
                utils.printInputPrompt("Enter task description: ", "[DESC]");
                std::getline(std::cin, task);
                
                if (!task.empty()) {
                    todo.addTask(task);
                    utils.printSuccessMessage("[~] Task added successfully!");
                } else {
                    utils.printErrorMessage("[X] Task description cannot be empty!");
                }
                waitForUserInput();
                break;
            }

            case 2: {
                // Remove task
                std::cout << std::endl;
                int id;
                utils.printInputPrompt("Enter task ID to remove: ", "[ID]");
                if (std::cin >> id) {
                    todo.removeTask(id);
                    utils.printSuccessMessage("[~] Task removal attempted!");
                } else {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    utils.printErrorMessage("[X] Invalid ID format!");
                }
                std::cin.ignore();
                waitForUserInput();
                break;
            }

            case 3: {
                // View tasks
                utils.clearScreen();
                utils.printSectionHeader("YOUR TASKS", "[TASK]");
                todo.viewTasks();
                waitForUserInput();
                break;
            }

            case 4: {
                // Mark task as done
                std::cout << std::endl;
                int id;
                utils.printInputPrompt("Enter task ID to mark as done: ", "[DONE]");
                if (std::cin >> id) {
                    todo.markTaskDone(id);
                    utils.printSuccessMessage("[~] Task status updated!");
                } else {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    utils.printErrorMessage("[X] Invalid ID format!");
                }
                std::cin.ignore();
                waitForUserInput();
                break;
            }

            case 5: {
                // Return to main menu
                utils.printSuccessMessage("[>] Returning to main menu...");
                SLEEP(800);
                return;
            }

            default: {
                utils.printErrorMessage("[X]  Invalid choice! Please select a number between 1-5.");
                waitForUserInput();
                break;
            }
        }
    }
}

void Utility::displayTodoSubMenu(Utility &utils) {
    utils.printSectionHeader("TODO LIST MANAGER", "[*]");
    
    std::cout << BRIGHT_CYAN << BG_BLACK << "+=========================================+" << RESET << std::endl;
    std::cout << BRIGHT_CYAN << BG_BLACK << "| " << RESET << BG_MAGENTA << WHITE << BOLD << "        Task Management Menu           " << RESET << BRIGHT_CYAN << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BRIGHT_CYAN << BG_BLACK << "+=========================================+" << RESET << std::endl;
    std::cout << BG_BLACK << "| " << YELLOW << BOLD << "1." << RESET << BG_BLACK << WHITE << " Add New Task                     " << RESET << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BG_BLACK << "| " << YELLOW << BOLD << "2." << RESET << BG_BLACK << WHITE << " Remove Task                      " << RESET << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BG_BLACK << "| " << YELLOW << BOLD << "3." << RESET << BG_BLACK << WHITE << " View All Tasks                   " << RESET << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BG_BLACK << "| " << YELLOW << BOLD << "4." << RESET << BG_BLACK << WHITE << " Mark Task as Done               " << RESET << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BG_BLACK << "| " << RED << BOLD << "5." << RESET << BG_BLACK << BRIGHT_YELLOW << " Return to Main Menu             " << RESET << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BRIGHT_CYAN << BG_BLACK << "+=========================================+" << RESET << std::endl;
    std::cout << std::endl;
    
    utils.printInputPrompt("Choose an option (1-5): ", "[>]");
}

bool Utility::getUserRegistration(UserAuth &auth, Utility &utils) {
    utils.printSectionHeader("USER REGISTRATION", "[+]");

    std::string username, password;
    
    utils.printInputPrompt("Enter Username: ", "[USER]");
    std::cin >> username;
    std::cin.ignore();

    password = auth.getHiddenPassword("[PASS] Enter Password: ");

    std::cout << std::endl;
    if (auth.registerUser(username, password)) {
        utils.printSuccessMessage("[SUCCESS] Registration completed successfully!");
        return true;
    } else {
        utils.printErrorMessage("[ERROR] Registration failed! Username might already exist.");
        return false;
    }
}

bool Utility::getUserLogin(UserAuth &auth, Utility &utils, std::string &username) {
    utils.printSectionHeader("USER LOGIN", "[>]");

    utils.printInputPrompt("Enter Username: ", "[USER]");
    std::cin >> username;
    std::cin.ignore();

    std::string password = auth.getHiddenPassword("[PASS] Enter Password: ");

    std::cout << std::endl;
    if (auth.loginUser(username, password)) {
        utils.printSuccessMessage("[SUCCESS] Welcome back, " + username + "! Login successful.");
        SLEEP(1000);
        return true;
    } else {
        utils.printErrorMessage("[ERROR] Login failed! Invalid credentials.");
        return false;
    }
}

void Utility::waitForUserInput(const std::string &message) {
    std::cout << std::endl << YELLOW << "[PAUSE] " << RESET << message;
    std::cin.get();
}