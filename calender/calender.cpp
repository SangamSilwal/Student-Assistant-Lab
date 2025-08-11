#include "assigments/Assignments.h"
#include "utility/utils.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <set>
#include <string>
#include <limits>

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