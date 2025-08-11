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

class Utility
{
    public:
    static void clearScreen();
    void printLine(char c = '=', int length = 60, const std::string& color = CYAN);
    void printCentered(const std::string& text, int width = 60, const std::string& color = WHITE);
    void printWelcomeBanner();
    void printMenu();
    void printSectionHeader(const std::string& title, const std::string& icon = "[*]");
    void printInputPrompt(const std::string& prompt, const std::string& icon = "[>]");
    void printSuccessMessage(const std::string& message);
    void printErrorMessage(const std::string& message);
    void printInfoMessage(const std::string& message);
    void printWarningMessage(const std::string& message);

};