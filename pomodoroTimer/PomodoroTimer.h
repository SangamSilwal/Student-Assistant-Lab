#ifndef POMODOROTIMER_H
#define POMODOROTIMER_H

#include <ctime>
#include <functional>

class PomodoroTimer {
public:
    PomodoroTimer(int workMinutes = 25, int breakMinutes = 5);
    
    // Call this frequently from your main loop
    void update();
    
    void start();
    void stop();
    void reset();
    
    void setWorkStartCallback(std::function<void()> callback);
    void setBreakStartCallback(std::function<void()> callback);
    void setTimerUpdateCallback(std::function<void(int)> callback);
    
    bool isRunning() const;
    bool isWorkPhase() const;
    int getRemainingSeconds() const;

private:
    void checkTimer();
    
    int workDuration;
    int breakDuration;
    int remainingTime;
    bool running;
    bool workPhase;
    time_t lastUpdateTime;
    
    std::function<void()> onWorkStart;
    std::function<void()> onBreakStart;
    std::function<void(int)> onTimerUpdate;
};

#endif // POMODOROTIMER_H