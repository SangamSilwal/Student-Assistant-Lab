#ifndef POMODOROTIMER_H
#define POMODOROTIMER_H

#include <ctime>
#include <functional>

class PomodoroTimer {
public:
    // Constructor with optional default durations (minutes)
    PomodoroTimer(int workMinutes = 0, int breakMinutes = 0);

    // Core timer functions
    void update();
    void start();
    void stop();
    void reset();

    // Set durations dynamically (in minutes)
    void setDurations(int workMinutes, int breakMinutes);

    // Callback setters
    void setWorkStartCallback(std::function<void()> callback);
    void setBreakStartCallback(std::function<void()> callback);
    void setTimerUpdateCallback(std::function<void(int)> callback);

    // Status queries
    bool isRunning() const;
    bool isWorkPhase() const;
    int getRemainingSeconds() const;

private:
    void checkTimer();

    int workDuration;   // in seconds
    int breakDuration;  // in seconds
    int remainingTime;  // in seconds

    bool running;
    bool workPhase;
    time_t lastUpdateTime;

    // Callback functions
    std::function<void()> onWorkStart;
    std::function<void()> onBreakStart;
    std::function<void(int)> onTimerUpdate;
};

#endif // POMODOROTIMER_H