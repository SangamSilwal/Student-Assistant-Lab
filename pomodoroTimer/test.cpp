#include "PomodoroTimer.h"
#include <iostream>
#include <iomanip>
#include <unistd.h> // for sleep()

void displayTime(int seconds) {
    int minutes = seconds / 60;
    int secs = seconds % 60;
    std::cout << "\rTime remaining: " 
              << std::setw(2) << std::setfill('0') << minutes << ":" 
              << std::setw(2) << std::setfill('0') << secs << " "
              << std::flush;
}

int main() {
    PomodoroTimer timer(1, 1); // 1 minute work, 1 minute break for testing
    
    timer.setWorkStartCallback([]() {
        std::cout << "\nWork phase started! Focus!\n";
    });
    
    timer.setBreakStartCallback([]() {
        std::cout << "\nBreak phase started! Relax!\n";
    });
    
    timer.setTimerUpdateCallback(displayTime);
    
    std::cout << "Starting Pomodoro Timer (1 min work, 1 min break)\n";
    timer.start();
    
    // Main loop
    for (int i = 0; i < 300; i++) { // Run for ~5 minutes
        timer.update();
        sleep(1); // Wait for 1 second
    }
    
    timer.stop();
    std::cout << "\nTimer stopped.\n";
    
    return 0;
}