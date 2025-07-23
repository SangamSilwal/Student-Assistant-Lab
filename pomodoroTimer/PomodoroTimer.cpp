#include "PomodoroTimer.h"
#include <ctime>
#include <iostream>

PomodoroTimer::PomodoroTimer(int workMinutes, int breakMinutes) 
    : workDuration(workMinutes * 60),
      breakDuration(breakMinutes * 60),
      remainingTime(workDuration),
      running(false),
      workPhase(true),
      lastUpdateTime(0) {}

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
    remainingTime = workPhase ? workDuration : breakDuration;
    
    if (workPhase && onWorkStart) {
        onWorkStart();
    } else if (!workPhase && onBreakStart) {
        onBreakStart();
    }
}