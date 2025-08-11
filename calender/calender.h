#include "assigments/Assignments.h"
#include "utility/utils.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <set>
#include <string>
#include <limits>

int getDayFromDate(const std::string& date);
void printCalendarWithAssignments(const std::vector<AssignmentData>& assignments,Utility& utils);