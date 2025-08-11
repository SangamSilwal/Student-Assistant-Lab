

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

