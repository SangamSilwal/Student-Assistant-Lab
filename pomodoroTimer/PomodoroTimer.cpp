#include "PomodoroTimer.h"
#include "utility/colorHeader.h"
#include <iostream>

PomodoroTimer::PomodoroTimer(int workMinutes, int breakMinutes) 
    : workDuration(workMinutes * 60),
      breakDuration(breakMinutes * 60),
      remainingTime(workDuration),
      running(false),
      workPhase(true),
      lastUpdateTime(0) {}

void PomodoroTimer::setDurations(int workMinutes, int breakMinutes) {
    workDuration = workMinutes * 60;
    breakDuration = breakMinutes * 60;
    remainingTime = workDuration;
    workPhase = true;
    running = false;
}

void PomodoroTimer::update() {
    if (!running) return;
    
    time_t currentTime = time(nullptr);
    if (currentTime - lastUpdateTime >= 1) {
        remainingTime--;
        lastUpdateTime = currentTime;

        if (onTimerUpdate) {
            onTimerUpdate(remainingTime);
        }

        if (remainingTime <= 0) {
            checkTimer();
        }
    }
}

void PomodoroTimer::start() {
    if (!running) {
        running = true;
        lastUpdateTime = time(nullptr);
    }
}

void PomodoroTimer::stop() {
    running = false;
}

void PomodoroTimer::reset() {
    remainingTime = workPhase ? workDuration : breakDuration;
    lastUpdateTime = time(nullptr);
}

void PomodoroTimer::setWorkStartCallback(std::function<void()> callback) {
    onWorkStart = callback;
}

void PomodoroTimer::setBreakStartCallback(std::function<void()> callback) {
    onBreakStart = callback;
}

void PomodoroTimer::setTimerUpdateCallback(std::function<void(int)> callback) {
    onTimerUpdate = callback;
}

bool PomodoroTimer::isRunning() const {
    return running;
}

bool PomodoroTimer::isWorkPhase() const {
    return workPhase;
}

int PomodoroTimer::getRemainingSeconds() const {
    return remainingTime;
}

void PomodoroTimer::checkTimer() {
    workPhase = !workPhase;

    if (workPhase) {
        // After break finishes, ask user if they want to continue
        char choice;
        std::cout << "\n"<<BOLD<<"Break time finished!"<<RESET<<YELLOW<<" Do you want to continue with another work session? (y/n): "<<RESET;
        std::cin >> choice;
        
        if (choice == 'y' || choice == 'Y') {
            remainingTime = workDuration;
            if (onWorkStart) {
                onWorkStart();
            }
        } else {
            std::cout << "Pomodoro session ended. Good job!\n";
            running = false;
            return;
        }
    } else {
        // Entering break phase
        remainingTime = breakDuration;
        if (onBreakStart) {
            onBreakStart();
        }
    }
}