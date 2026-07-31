#include <PalmOS.h>
#include "AnalogClock.h"

#define HOUR_HAND_LENGTH     16
#define MINUTE_HAND_LENGTH   21
#define SECOND_HAND_LENGTH   21

// Clock constants
static const Int16 clockX[12] =
{
      0,  50,  87, 100,  87,  50,
      0, -50, -87,-100, -87, -50
};

static const Int16 clockY[12] =
{
   -100, -87, -50,   0,  50,  87,
    100,  87,  50,   0, -50, -87
};

/*
 * Clock directions for each minute/second position.
 * Values are sin/cos coordinates scaled by 100.
 *
 * Position:
 *   0  = 12 o'clock
 *   15 = 3 o'clock
 *   30 = 6 o'clock
 *   45 = 9 o'clock
 */
static const Int16 clock60X[60] =
{
      0,  10,  21,  31,  41,  50,  59,  67,  74,  81,
     87,  91,  95,  98,  99, 100,  99,  98,  95,  91,
     87,  81,  74,  67,  59,  50,  41,  31,  21,  10,
      0, -10, -21, -31, -41, -50, -59, -67, -74, -81,
    -87, -91, -95, -98, -99,-100, -99, -98, -95, -91,
    -87, -81, -74, -67, -59, -50, -41, -31, -21, -10
};

static const Int16 clock60Y[60] =
{
   -100, -99, -98, -95, -91, -87, -81, -74, -67, -59,
    -50, -41, -31, -21, -10,   0,  10,  21,  31,  41,
     50,  59,  67,  74,  81,  87,  91,  95,  98,  99,
    100,  99,  98,  95,  91,  87,  81,  74,  67,  59,
     50,  41,  31,  21,  10,   0, -10, -21, -31, -41,
    -50, -59, -67, -74, -81, -87, -91, -95, -98, -99
};

#define HOUR_HAND_LENGTH     16
#define MINUTE_HAND_LENGTH   21
#define SECOND_HAND_LENGTH   21

static UInt16 oldHourPosition;
static UInt16 oldMinutePosition;
static UInt16 oldSecondPosition;

static Boolean handsDrawn = false;

Boolean useAnalogClockNumbers = true;


static void DrawClockCenter(Int16 centerX, Int16 centerY)
{
    RectangleType centerRect;

    RctSetRectangle(
        &centerRect,
        centerX - 1,
        centerY - 1,
        3,
        3
    );
	
    WinDrawRectangle(&centerRect, 1);
}


void DrawAnalogClockFace(Int16 centerX, Int16 centerY)
{
    static const Char *clockNumbers[12] =
    {
        "12", "1", "2", "3", "4", "5",
        "6", "7", "8", "9", "10", "11"
    };

    Int16 innerRadius;
    Int16 outerRadius;
    Int16 numberRadius;
    Int16 x1;
    Int16 y1;
    Int16 x2;
    Int16 y2;
    Int16 textWidth;
    Int16 textHeight;
    Int16 textX;
    Int16 textY;
    UInt16 textLength;
    UInt16 i;

    if (useAnalogClockNumbers)
    {
        numberRadius = 26;

        FntSetFont(stdFont);
        textHeight = FntLineHeight();

        for (i = 0; i < 12; i++)
        {
            x1 = centerX + (clockX[i] * numberRadius) / 100;
            y1 = centerY + (clockY[i] * numberRadius) / 100;

            textLength = StrLen(clockNumbers[i]);
            textWidth = FntCharsWidth(clockNumbers[i], textLength);

            textX = x1 - (textWidth / 2);
            textY = y1 - (textHeight / 2);

            WinDrawChars(
                clockNumbers[i],
                textLength,
                textX,
                textY
            );
        }
    }
    else
    {
        outerRadius = 28;

        for (i = 0; i < 12; i++)
        {
            if (i == 0 || i == 3 || i == 6 || i == 9)
                innerRadius = 23;
            else
                innerRadius = 25;

            x1 = centerX + (clockX[i] * innerRadius) / 100;
            y1 = centerY + (clockY[i] * innerRadius) / 100;

            x2 = centerX + (clockX[i] * outerRadius) / 100;
            y2 = centerY + (clockY[i] * outerRadius) / 100;

            WinDrawLine(x1, y1, x2, y2);
        }
    }

    /* WinDrawPixel() is unavailable in Palm OS 1.0. */
    //WinDrawLine(centerX, centerY, centerX, centerY);
    
    DrawClockCenter(centerX, centerY);
}


static void DrawHand(
    UInt16 position,
    Int16 length,
    Int16 centerX,
    Int16 centerY)
{
    Int16 x;
    Int16 y;

    position %= 60;

    x = centerX + ((clock60X[position] * length) / 100);
    y = centerY + ((clock60Y[position] * length) / 100);

    WinDrawLine(centerX, centerY, x, y);
}


static void EraseHand(
    UInt16 position,
    Int16 length,
    Int16 centerX,
    Int16 centerY)
{
    Int16 x;
    Int16 y;

    position %= 60;

    x = centerX + ((clock60X[position] * length) / 100);
    y = centerY + ((clock60Y[position] * length) / 100);

    WinEraseLine(centerX, centerY, x, y);
}


void UpdateAnalogClockHands(
    Int16 centerX,
    Int16 centerY,
    UInt16 hours,
    UInt16 minutes,
    UInt16 seconds)
{
    UInt16 newHourPosition;
    UInt16 newMinutePosition;
    UInt16 newSecondPosition;

    //1) Erase previous hands
    if (handsDrawn)
    {
        EraseHand(
            oldHourPosition,
            HOUR_HAND_LENGTH,
            centerX,
            centerY
        );

        EraseHand(
            oldMinutePosition,
            MINUTE_HAND_LENGTH,
            centerX,
            centerY
        );

        EraseHand(
            oldSecondPosition,
            SECOND_HAND_LENGTH,
            centerX,
            centerY
        );
    }

    
    //2) Calculate new positions
    newHourPosition =
        ((hours % 12) * 5) + (minutes / 12);

    newMinutePosition = minutes;
    newSecondPosition = seconds;
    
    //3) Draw new hands
    DrawHand(
        newHourPosition,
        HOUR_HAND_LENGTH,
        centerX,
        centerY
    );

    DrawHand(
        newMinutePosition,
        MINUTE_HAND_LENGTH,
        centerX,
        centerY
    );

    DrawHand(
        newSecondPosition,
        SECOND_HAND_LENGTH,
        centerX,
        centerY
    );
    
	//4) Draw clock center
	DrawClockCenter(centerX, centerY);

    
    //5) Save positions for next update
    oldHourPosition = newHourPosition;
    oldMinutePosition = newMinutePosition;
    oldSecondPosition = newSecondPosition;

    handsDrawn = true;
}


void DrawCurrentAnalogClockHands(Int16 centerX, Int16 centerY)
{
    UInt32 seconds;
    DateTimeType dateTime;

    seconds = TimGetSeconds();
    TimSecondsToDateTime(seconds, &dateTime);

    UpdateAnalogClockHands(
        centerX,
        centerY,
        dateTime.hour,
        dateTime.minute,
        dateTime.second
    );
}


void UpdateAnalogClock(Int16 centerX, Int16 centerY)
{
    UInt32 seconds;
    DateTimeType dateTime;

    seconds = TimGetSeconds();
    TimSecondsToDateTime(seconds, &dateTime);

    UpdateAnalogClockHands(
        centerX,
        centerY,
        dateTime.hour,
        dateTime.minute,
        dateTime.second
    );
}
