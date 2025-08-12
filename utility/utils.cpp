

#include "utils.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <set>
#include <string>
#include <limits>

void Utility::clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Utility::printLine(char c, int length, const std::string &color)
{
    std::cout << color;
    for (int i = 0; i < length; i++)
    {
        std::cout << c;
    }
    std::cout << RESET << std::endl;
}

void Utility::printCentered(const std::string &text, int width, const std::string &color)
{
    int padding = (width - text.length()) / 2;
    std::cout << color << std::string(padding, ' ') << text << RESET << std::endl;
}


void Utility::printWelcomeBanner()
{
    clearScreen();
    printLine('=', 80, MAGENTA);
    printLine('*', 80, CYAN);
    std::cout << std::endl;

    std::cout << BOLD << YELLOW;
    printCentered("   _____ _______ _    _ _____  ______ _   _ _______ ", 80);
    printCentered("  / ____|__   __| |  | |  __ \\|  ____| \\ | |__   __|", 80);
    printCentered(" | (___    | |  | |  | | |  | | |__  |  \\| |  | |   ", 80);
    printCentered("  \\___ \\   | |  | |  | | |  | |  __| | . ` |  | |   ", 80);
    printCentered("  ____) |  | |  | |__| | |__| | |____| |\\  |  | |   ", 80);
    printCentered(" |_____/   |_|   \\____/|_____/|______|_| \\_|  |_|   ", 80);
    std::cout << RESET << std::endl;

    std::cout << BOLD << CYAN;
    printCentered("ASSISTANT",80);
std::cout << RESET << std::endl << std::endl;

    printLine('-', 80, BLUE);
    std::cout << std::endl;

    std::cout << BOLD << WHITE;
    printCentered(">> YOUR PERSONAL ACADEMIC ORGANIZER <<", 80);
    std::cout << RESET << std::endl;

    std::cout << CYAN;
    printCentered("Organize | Plan | Succeed", 80);
    std::cout << RESET << std::endl
              << std::endl;

    printLine('-', 80, GREEN);
    std::cout << GREEN << "| " << BOLD << WHITE << "Features:" << RESET << GREEN;
    for (int i = 0; i < 65; i++)
        std::cout << " ";
    std::cout  << std::endl;

    std::cout << GREEN << "| " << YELLOW << "+ Assignment Tracking" << RESET << GREEN;
    for (int i = 0; i < 54; i++)
        std::cout << " ";
    std::cout  << std::endl;

    std::cout << GREEN << "| " << YELLOW << "+ Deadline Management" << RESET << GREEN;
    for (int i = 0; i < 54; i++)
        std::cout << " ";
    std::cout  << std::endl;

    std::cout << GREEN << "| " << YELLOW << "+ Progress Monitoring" << RESET << GREEN;
    for (int i = 0; i < 54; i++)
        std::cout << " ";
    std::cout  << std::endl;

    std::cout << GREEN << "| " << YELLOW << "+ Pomodoro For Focus" << RESET << GREEN;
    for (int i = 0; i < 57; i++)
        std::cout << " ";
    std::cout << std::endl;
    std::cout << GREEN << "| " << YELLOW << "+ Todo-List Feature" << RESET << GREEN;
    for (int i = 0; i < 57; i++)
        std::cout << " ";
    std::cout  << std::endl;
    std::cout << GREEN << "| " << YELLOW << "+ Routine Setting" << RESET << GREEN;
    for (int i = 0; i < 57; i++)
        std::cout << " ";
    std::cout  << std::endl;

    printLine('-', 80, GREEN);
    std::cout << std::endl;

    std::cout << BOLD << MAGENTA;
    printCentered("\"Success is the sum of small efforts, repeated day in and day out.\"", 80);
    std::cout << RESET << std::endl;

    std::cout << ITALIC << WHITE;
    printCentered("- Robert Collier", 80);
    std::cout << RESET << std::endl
              << std::endl;


    printLine('*', 80, CYAN);
    printLine('=', 80, MAGENTA);
    std::cout << std::endl;


    std::cout << BOLD << YELLOW;
    printCentered("Press ENTER to continue...", 80);
    std::cout << RESET << std::endl;
}

void Utility::printMenu()
{
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

void Utility::printSectionHeader(const std::string &title, const std::string &icon)
{
    std::cout << std::endl;
    printLine('=', 60, MAGENTA);
    printCentered(BOLD + icon + " " + title + " " + icon + RESET, 60, YELLOW);
    printLine('=', 60, MAGENTA);
    std::cout << std::endl;
}

void Utility::printInputPrompt(const std::string &prompt, const std::string &icon)
{
    std::cout << GREEN << BOLD << icon << " " << CYAN << prompt << RESET;
}

void Utility::printSuccessMessage(const std::string &message)
{
    std::cout << GREEN << BOLD << "[SUCCESS] " << RESET << GREEN << message << RESET << std::endl;
}

void Utility::printErrorMessage(const std::string &message)
{
    std::cout << RED << BOLD << "[X ERROR] " << RESET << RED << message << RESET << std::endl;
}

void Utility::printInfoMessage(const std::string &message)
{
    std::cout << BLUE << BOLD << "[i INFO] " << RESET << BLUE << message << RESET << std::endl;
}

void Utility::printWarningMessage(const std::string &message)
{
    std::cout << YELLOW << BOLD << "[! WARNING] " << RESET << YELLOW << message << RESET << std::endl;
}

void Utility::displayMainMenu(Utility &utils)
{
    utils.printSectionHeader("MAIN MENU", "[*]");

    std::cout << BRIGHT_GREEN << BG_BLACK << "+=========================================+" << RESET << std::endl;
    std::cout << BRIGHT_GREEN << BG_BLACK << "| " << RESET << BG_BLUE << WHITE << BOLD << "   Student Management System           " << RESET << BRIGHT_GREEN << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BRIGHT_GREEN << BG_BLACK << "+=========================================+" << RESET << std::endl;
    std::cout << BG_BLACK << "| " << CYAN << BOLD << "1." << RESET << BG_BLACK << WHITE << " Add New Assignment                " << RESET << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BG_BLACK << "| " << CYAN << BOLD << "2." << RESET << BG_BLACK << WHITE << " View All Assignments              " << RESET << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BG_BLACK << "| " << CYAN << BOLD << "3." << RESET << BG_BLACK << WHITE << " View Calendar                     " << RESET << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BG_BLACK << "| " << CYAN << BOLD << "4." << RESET << BG_BLACK << WHITE << " Manage Todo List                  " << RESET << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BG_BLACK << "| " << CYAN << BOLD << "5." << RESET << BG_BLACK << WHITE << " View Routine                      " << RESET << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BG_BLACK << "| " << CYAN << BOLD << "6." << RESET << BG_BLACK << WHITE << " Try POMODORO timer                " << RESET << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BG_BLACK << "| " << CYAN << BOLD << "7." << RESET << BG_BLACK << WHITE << " Exit Application                  " << RESET << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BRIGHT_GREEN << BG_BLACK << "+=========================================+" << RESET << std::endl;
    std::cout << std::endl;

    utils.printInputPrompt("Choose an option (1-5): ", "[>]");
}

void Utility::handleAssignmentMenu(Assignment &assignment, int user_id, Utility &utils)
{
    while (true) 
    {
        utils.clearScreen();
        utils.printSectionHeader("YOUR ASSIGNMENTS", "[*]");

        auto assignments = assignment.getAssignments(user_id);
        if (assignments.empty())
        {
            std::cout << YELLOW << BG_BLACK << "+=========================================+" << RESET << std::endl;
            std::cout << YELLOW << BG_BLACK << "| " << RESET << BG_RED << WHITE << BOLD << "       No assignments found!           " << RESET << YELLOW << BG_BLACK << "|" << RESET << std::endl;
            std::cout << YELLOW << BG_BLACK << "| " << RESET << BG_YELLOW << BLUE << " Add some assignments to get started! " << RESET << YELLOW << BG_BLACK << "|" << RESET << std::endl;
            std::cout << YELLOW << BG_BLACK << "+=========================================+" << RESET << std::endl;
        }
        else
        {
            std::cout << BG_BLUE << WHITE << BOLD << "[INFO] Total Assignments: " << BG_YELLOW << BLUE << " " << assignments.size() << " " << RESET << std::endl;
            utils.printLine('=', 60, BLUE);
            std::cout << std::endl;

            for (size_t i = 0; i < assignments.size(); i++)
            {
                const auto &a = assignments[i];

                std::cout << BG_YELLOW << BLUE << BOLD << "[" << (i + 1) << "] Assignment Details:" << RESET << std::endl;
                std::cout << BG_BLACK << "  ID: " << CYAN << BOLD << a.id << RESET << std::endl;
                std::cout << BG_BLACK << "  Title: " << WHITE << BOLD << a.title << RESET << std::endl;
                std::cout << BG_BLACK << "  Description: " << WHITE << a.description << RESET << std::endl;
                std::cout << BG_BLACK << "  Due Date: " << BG_GREEN << WHITE << BOLD << " " << a.due_date << " " << RESET << std::endl;

                if (i < assignments.size() - 1)
                {
                    utils.printLine('-', 40, DIM);
                    std::cout << std::endl;
                }
            }
        }

        std::cout << std::endl;
        std::cout <<YELLOW<<"Choose an action:\n"<<RESET;
        std::cout <<GREEN<<"1. Add Assignment\n"<<RESET;
        std::cout <<GREEN<<"2. Delete Assignment\n"<<RESET;
        std::cout <<GREEN<<"3. Back to Main Menu\n"<<RESET;
        std::cout <<GREEN<<"Enter choice: "<<RESET;

        int action;
        std::cin >> action;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (action == 1)
        {
            std::string title, description, due_date;

            std::cout <<YELLOW<<"Enter Title: "<<RESET;
            std::getline(std::cin, title);

            std::cout <<YELLOW<<"Enter Description: "<<RESET;
            std::getline(std::cin, description);

            std::cout <<YELLOW<<"Enter Due Date (YYYY-MM-DD): "<<RESET;
            std::getline(std::cin, due_date);

            bool added = assignment.addAssignment(user_id, title, description, due_date);
            if (added)
                utils.printSuccessMessage("Assignment added successfully.");
            else
                utils.printErrorMessage("Failed to add assignment.");
        }
        else if (action == 2)
        {
            int delete_id;
            std::cout << "Enter the Assignment ID to delete: ";
            std::cin >> delete_id;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            bool deleted = assignment.deleteAssignment(delete_id);
            if (deleted)
                utils.printSuccessMessage("Assignment deleted successfully.");
            else
                utils.printErrorMessage("Failed to delete assignment. Check the ID.");
        }
        else if (action == 3)
        {
            break;
        }
        else
        {
            utils.printErrorMessage("Invalid choice, please try again.");
        }

        std::cout << "Press Enter to continue...";
        std::cin.get();
    }
}



void Utility::handleTodoMenu(TodoList &todo, Utility &utils)
{
    int choice;

    while (true)
    {
        utils.clearScreen();
        displayTodoSubMenu(utils);

        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            utils.printErrorMessage(" Invalid input! Please enter a valid number.");
            waitForUserInput();
            continue;
        }
        std::cin.ignore();

        switch (choice)
        {
        case 1:
        {
            std::cout << std::endl;
            std::string task;
            printInputPrompt("Enter task description: ", "[DESC]");
            std::getline(std::cin, task);

            if (!task.empty())
            {
                todo.addTask(task);
                utils.printSuccessMessage("[~] Task added successfully!");
            }
            else
            {
                utils.printErrorMessage("[X] Task description cannot be empty!");
            }
            waitForUserInput();
            break;
        }

        case 2:
        {
            std::cout << std::endl;
            int id;
            utils.printInputPrompt("Enter task ID to remove: ", "[ID]");
            if (std::cin >> id)
            {
                todo.removeTask(id);
                utils.printSuccessMessage("[~] Task removal attempted!");
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                utils.printErrorMessage("[X] Invalid ID format!");
            }
            std::cin.ignore();
            waitForUserInput();
            break;
        }

        case 3:
        {
            utils.clearScreen();
            utils.printSectionHeader("YOUR TASKS", "[TASK]");
            todo.viewTasks();
            waitForUserInput();
            break;
        }

        case 4:
        {
            std::cout << std::endl;
            int id;
            utils.printInputPrompt("Enter task ID to mark as done: ", "[DONE]");
            if (std::cin >> id)
            {
                todo.markTaskDone(id);
                utils.printSuccessMessage("[~] Task status updated!");
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                utils.printErrorMessage("[X] Invalid ID format!");
            }
            std::cin.ignore();
            waitForUserInput();
            break;
        }
        case 5:
        {
            todo.displayStatistics();
            break;
        }

        case 6:
        {
            // Return to main menu
            utils.printSuccessMessage("[>] Returning to main menu...");
            SLEEP(800);
            return;
        }

        default:
        {
            utils.printErrorMessage("[X]  Invalid choice! Please select a number between 1-5.");
            waitForUserInput();
            break;
        }
        }
    }
}

void Utility::displayTodoSubMenu(Utility &utils)
{
    utils.printSectionHeader("TODO LIST MANAGER", "[*]");

    std::cout << BRIGHT_CYAN << BG_BLACK << "+=========================================+" << RESET << std::endl;
    std::cout << BRIGHT_CYAN << BG_BLACK << "| " << RESET << BG_MAGENTA << WHITE << BOLD << "        Task Management Menu           " << RESET << BRIGHT_CYAN << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BRIGHT_CYAN << BG_BLACK << "+=========================================+" << RESET << std::endl;
    std::cout << BG_BLACK << "| " << YELLOW << BOLD << "1." << RESET << BG_BLACK << WHITE << " Add New Task                     " << RESET << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BG_BLACK << "| " << YELLOW << BOLD << "2." << RESET << BG_BLACK << WHITE << " Remove Task                      " << RESET << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BG_BLACK << "| " << YELLOW << BOLD << "3." << RESET << BG_BLACK << WHITE << " View All Tasks                   " << RESET << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BG_BLACK << "| " << YELLOW << BOLD << "4." << RESET << BG_BLACK << WHITE << " Mark Task as Done               " << RESET << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BG_BLACK << "| " << YELLOW << BOLD << "5." << RESET << BG_BLACK << WHITE << " Display Statistics               " << RESET << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BG_BLACK << "| " << RED << BOLD << "6" << RESET << BG_BLACK << BRIGHT_YELLOW << " Return to Main Menu             " << RESET << BG_BLACK << "|" << RESET << std::endl;
    std::cout << BRIGHT_CYAN << BG_BLACK << "+=========================================+" << RESET << std::endl;
    std::cout << std::endl;

    utils.printInputPrompt("Choose an option (1-5): ", "[>]");
}

bool Utility::getUserRegistration(UserAuth &auth, Utility &utils)
{
    utils.printSectionHeader("USER REGISTRATION", "[+]");

    std::string username, password;

    utils.printInputPrompt("Enter Username: ", "[USER]");
    std::cin >> username;
    std::cin.ignore();

    password = auth.getHiddenPassword("[PASS] Enter Password: ");

    std::cout << std::endl;
    if (auth.registerUser(username, password))
    {
        utils.printSuccessMessage("[SUCCESS] Registration completed successfully!");
        return true;
    }
    else
    {
        utils.printErrorMessage("[ERROR] Registration failed! Username might already exist.");
        return false;
    }
}

bool Utility::getUserLogin(UserAuth &auth, Utility &utils, std::string &username)
{
    utils.printSectionHeader("USER LOGIN", "[>]");

    utils.printInputPrompt("Enter Username: ", "[USER]");
    std::cin >> username;
    std::cin.ignore();

    std::string password = auth.getHiddenPassword("[PASS] Enter Password: ");

    std::cout << std::endl;
    if (auth.loginUser(username, password))
    {
        utils.printSuccessMessage("[SUCCESS] Welcome back, " + username + "! Login successful.");
        SLEEP(1000);
        return true;
    }
    else
    {
        utils.printErrorMessage("[ERROR] Login failed! Invalid credentials.");
        return false;
    }
}

void Utility::waitForUserInput(const std::string &message)
{
    std::cout << std::endl
              << YELLOW << "[PAUSE] " << RESET << message;
    std::cin.get();
}