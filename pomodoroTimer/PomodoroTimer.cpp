#include "PomodoroTimer.h"
#include <ctime>
#include <iostream>

/**
 * @brief Constructs a PomodoroTimer object with specified durations for work and break.
 * 
 * @param workMinutes Duration of the work phase in minutes.
 * @param breakMinutes Duration of the break phase in minutes.
 */
PomodoroTimer::PomodoroTimer(int workMinutes, int breakMinutes) 
    : workDuration(workMinutes * 60),
      breakDuration(breakMinutes * 60),
      remainingTime(workDuration),
      running(false),
      workPhase(true),
      lastUpdateTime(0) {}
      

/**
 * @brief Updates the timer each second if running. 
 *        Decrements remaining time and triggers callbacks.
 */
void PomodoroTimer::update() {
    if (!running) return;
    
    time_t currentTime = time(nullptr);
    if (currentTime - lastUpdateTime >= 1) {
        remainingTime--;
        lastUpdateTime = currentTime;
        
        // Trigger timer update callback
        if (onTimerUpdate) {
            onTimerUpdate(remainingTime);
        }

        // Transition to next phase when time runs out
        if (remainingTime <= 0) {
            checkTimer();
        }
    }
}


/**
 * @brief Starts the timer if it is not already running.
 */
void PomodoroTimer::start() {
    if (!running) {
        running = true;
        lastUpdateTime = time(nullptr);
    }
}


/**
 * @brief Stops the timer, pausing countdown.
 */
void PomodoroTimer::stop() {
    running = false;
}


/**
 * @brief Resets the timer to the full duration of the current phase.
 */
void PomodoroTimer::reset() {
    remainingTime = workPhase ? workDuration : breakDuration;
    lastUpdateTime = time(nullptr);
}


/**
 * @brief Sets a callback function to be called when the work phase starts.
 * 
 * @param callback The function to call.
 */
void PomodoroTimer::setWorkStartCallback(std::function<void()> callback) {
    onWorkStart = callback;
}


/**
 * @brief Sets a callback function to be called when the break phase starts.
 * 
 * @param callback The function to call.
 */
void PomodoroTimer::setBreakStartCallback(std::function<void()> callback) {
    onBreakStart = callback;
}


/**
 * @brief Sets a callback function to be called every second the timer updates.
 * 
 * @param callback The function to call, receives remaining seconds as argument.
 */
void PomodoroTimer::setTimerUpdateCallback(std::function<void(int)> callback) {
    onTimerUpdate = callback;
}


/**
 * @brief Checks whether the timer is currently running.
 * 
 * @return true if the timer is running, false otherwise.
 */
bool PomodoroTimer::isRunning() const {
    return running;
}


/**
 * @brief Checks if the current phase is a work phase.
 * 
 * @return true if in work phase, false if in break phase.
 */
bool PomodoroTimer::isWorkPhase() const {
    return workPhase;
}


/**
 * @brief Gets the number of seconds remaining in the current phase.
 * 
 * @return Remaining seconds as an integer.
 */
int PomodoroTimer::getRemainingSeconds() const {
    return remainingTime;
}


/**
 * @brief Handles phase switching between work and break.
 *        Resets remaining time and triggers phase start callbacks.
 */
void PomodoroTimer::checkTimer() {
    workPhase = !workPhase;
    remainingTime = workPhase ? workDuration : breakDuration;
    
    if (workPhase && onWorkStart) {
        onWorkStart();
    } else if (!workPhase && onBreakStart) {
        onBreakStart();
    }
}
