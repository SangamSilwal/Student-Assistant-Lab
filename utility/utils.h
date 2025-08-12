#ifndef UTILS_H
#define UTILS_H

#include "assigments/Assignments.h"
#include "todo-list/TodoList.h"
#include "studentValidation/UserAuth.h"
#include "colorHeader.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <set>
#include <string>
#include <limits>



#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP(ms) usleep((ms) * 1000)
#endif

class Utility
{
public:
    static void clearScreen();
    void printLine(char c = '=', int length = 60, const std::string &color = CYAN);
    void printCentered(const std::string &text, int width = 60, const std::string &color = WHITE);
    void printWelcomeBanner();
    void printMenu();
    void printSectionHeader(const std::string &title, const std::string &icon = "[*]");
    void printInputPrompt(const std::string &prompt, const std::string &icon = "[>]");
    void printSuccessMessage(const std::string &message);
    void printErrorMessage(const std::string &message);
    void printInfoMessage(const std::string &message);
    void printWarningMessage(const std::string &message);
    void displayMainMenu(Utility &utils);
    void handleAssignmentMenu(Assignment &assignment, int user_id, Utility &utils);
    void handleTodoMenu(TodoList &todo, Utility &utils);
    void displayTodoSubMenu(Utility &utils);
    bool getUserRegistration(UserAuth &auth, Utility &utils);
    bool getUserLogin(UserAuth &auth, Utility &utils, std::string &username);
    void waitForUserInput(const std::string &message = "Press Enter to continue...");
};

#endif