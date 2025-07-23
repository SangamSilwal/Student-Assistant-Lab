#include "PomodoroTimer.h"
#include <iostream>
#include <ctime>

int main() {
    int workMinutes, breakMinutes;

    std::cout << "Enter work time in minutes: ";
    std::cin >> workMinutes;

    std::cout << "Enter break time in minutes: ";
    std::cin >> breakMinutes;

    PomodoroTimer timer(workMinutes, breakMinutes);

    timer.setWorkStartCallback([]() {
        std::cout << "\n🔨 Work phase started!\n";
    });

    timer.setBreakStartCallback([]() {
        std::cout << "\n☕ Break phase started!\n";
    });

    timer.setTimerUpdateCallback([](int remainingSeconds) {
        std::cout << "⏳ Remaining: " << remainingSeconds << " seconds\r";
        std::cout.flush();
    });

    timer.start();

    // Basic loop to simulate a ticking timer without using this_thread
    std::time_t lastUpdate = std::time(nullptr);
    while (true) {
        std::time_t now = std::time(nullptr);
        if (now != lastUpdate) {
            lastUpdate = now;
            timer.update();
        }
    }

    return 0;
}
