#include <PalmOS.h>
#include "TimeBoardDraw.h"

#define VIEW_MARGIN       8
#define VIEW_GAP          4
#define VIEW_SIZE        70
#define VIEW_STEP        (VIEW_SIZE + VIEW_GAP)
#define VIEW_HALF_SIZE   (VIEW_SIZE / 2)

UInt16 cornerRadiusOut;
UInt16 cornerRadiusIn;

static Boolean hasCornerRadius = true;


void DrawViewPanels(void)
{
    RectangleType outerRect;
    RectangleType innerRect;
    Int16 x;
    Int16 y;
    UInt16 row;
    UInt16 col;
    
    // Corner radius control
    if (hasCornerRadius) {
    	cornerRadiusOut = 8;
    	cornerRadiusIn = 7;
    }
    else
    {
    	cornerRadiusOut = 0;
    	cornerRadiusIn = 0;
    }
	
    for (row = 0; row < 2; row++)
    {
        for (col = 0; col < 2; col++)
        {
            x = VIEW_MARGIN + (col * VIEW_STEP);
            y = VIEW_MARGIN + (row * VIEW_STEP);

            RctSetRectangle(&outerRect, x, y, VIEW_SIZE, VIEW_SIZE);
            WinDrawRectangle(&outerRect, cornerRadiusOut);

            /*
             * 67x67 intentionally gives the frame
             * the slight shadow effect.
             */
            RctSetRectangle(&innerRect, x + 1, y + 1, 67, 67);
            WinEraseRectangle(&innerRect, cornerRadiusIn);
        }
    }
}


Int16 GetViewX(UInt16 view)
{
    return VIEW_MARGIN + ((view % 2) * VIEW_STEP);
}


Int16 GetViewY(UInt16 view)
{
    return VIEW_MARGIN + ((view / 2) * VIEW_STEP);
}


Int16 GetViewCenterX(UInt16 view)
{
    return GetViewX(view) + VIEW_HALF_SIZE;
}


Int16 GetViewCenterY(UInt16 view)
{
    return GetViewY(view) + VIEW_HALF_SIZE;
}
