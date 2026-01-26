#pragma once

#include <stdbool.h>

typedef void (*TimerCallback)(void);

typedef struct Timer {
    float elapsed;
    float interval;

    bool repeat;
    bool active;

    TimerCallback callback;
} Timer;

Timer CreateTimer(float interval, bool repeat, TimerCallback callback);
void UpdateTimer(Timer* timer, float deltaTime);
void ResetTimer(Timer* timer);
void PlayTimer(Timer* timer);
void StopTimer(Timer* timer);