#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include <PalmOS.h>

void DrawAnalogClockFace(Int16 centerX, Int16 centerY);
void UpdateAnalogClockHands(Int16 centerX, Int16 centerY,
                            UInt16 hours, UInt16 minutes, UInt16 seconds);
void UpdateAnalogClock(Int16 centerX, Int16 centerY);
void DrawCurrentAnalogClockHands(Int16 centerX, Int16 centerY);

#endif