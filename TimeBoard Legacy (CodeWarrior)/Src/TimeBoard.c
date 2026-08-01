/*
 * TimeBoard.c
 *
 * main file for TimeBoard
 *
 * This wizard-generated code is based on code adapted from the
 * stationery files distributed as part of the Palm OS SDK 4.0.
 *
 * Copyright (c) 1999-2000 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 */
 
#include <PalmOS.h>
#include <PalmOSGlue.h>

#include "TimeBoard.h"
#include "TimeBoard_Rsc.h"
#include "TimeBoardDraw.h"
#include "AnalogClock.h"


/*********************************************************************
 * Entry Points
 *********************************************************************/

/*********************************************************************
 * Global variables
 *********************************************************************/

// Global to detect if form has been obscured by MainMenuBar, etc.
static Boolean mainFormObscured = false;

/*********************************************************************
 * Internal Constants
 *********************************************************************/

/* Define the minimum OS version we support */
#define ourMinVersion    sysMakeROMVersion(1,0,0,sysROMStageDevelopment,0)
#define kPalmOS20Version sysMakeROMVersion(2,0,0,sysROMStageDevelopment,0)

/*********************************************************************
 * Internal Functions
 *********************************************************************/

/*
 * FUNCTION: GetObjectPtr
 *
 * DESCRIPTION:
 *
 * This routine returns a pointer to an object in the current form.
 *
 * PARAMETERS:
 *
 * formId
 *     id of the form to display
 *
 * RETURNED:
 *     address of object as a void pointer
 */

static void * GetObjectPtr(UInt16 objectID)
{
	FormType * frmP;

	frmP = FrmGetActiveForm();
	return FrmGetObjectPtr(frmP, FrmGetObjectIndex(frmP, objectID));
}

/*
 * FUNCTION: MainFormInit
 *
 * DESCRIPTION: This routine initializes the MainForm form.
 *
 * PARAMETERS:
 *
 * frm
 *     pointer to the MainForm form.
 */

static void MainFormInit(FormType *frmP)
{

}

/*
 * FUNCTION: MainFormDoCommand
 *
 * DESCRIPTION: This routine performs the menu command specified.
 *
 * PARAMETERS:
 *
 * command
 *     menu item id
 */

static Boolean MainFormDoCommand(UInt16 command)
{
    Boolean handled = false;

    switch (command)
    {
        case AboutMenuItem:
            FrmAlert(AboutAlert);
            handled = true;
            break;
        case PrefsMenuItem:
			FrmGotoForm(PreferencesForm);
        	handled = true;
        	break;
    }

    return handled;
}

/*
 * FUNCTION: MainFormHandleEvent
 *
 * DESCRIPTION:
 *
 * This routine is the event handler for the "MainForm" of this 
 * application.
 *
 * PARAMETERS:
 *
 * eventP
 *     a pointer to an EventType structure
 *
 * RETURNED:
 *     true if the event was handled and should not be passed to
 *     FrmHandleEvent
 */

static Boolean MainFormHandleEvent(EventType * eventP)
{
	Boolean handled = false;
	FormType * frmP;

	switch (eventP->eType) 
	{
		case menuEvent:
			return MainFormDoCommand(eventP->data.menu.itemID);

		case frmOpenEvent:
			frmP = FrmGetActiveForm();
		    FrmDrawForm(frmP);
			
			// Draw background panels
			DrawViewPanels();
			
			// Draw analog clock numbers/lines
			DrawAnalogClockFace(
			    GetViewCenterX(0) - 1,
			    GetViewCenterY(0) - 1
			);
			
			// Draw first set of hands
			DrawCurrentAnalogClockHands(
			    GetViewCenterX(0) - 1,
			    GetViewCenterY(0) - 1
			);
			
		    handled = true;
			break;
			
		case nilEvent:
		    if (!mainFormObscured)
		    {
		    	// Update clock hands every second
		        UpdateAnalogClock(
		            GetViewCenterX(0) - 1,
		            GetViewCenterY(0) - 1
		        );
		    }

		    handled = true;
		    break;
            
        case frmUpdateEvent:
			/* 
			 * To do any custom drawing here, first call
			 * FrmDrawForm(), then do your drawing, and
			 * then set handled to true. 
			 */
			break;
			
		case ctlSelectEvent:

			break;
			
		    handled = true;
		    break;
	}
    
	return handled;
}


// Preferences form handler
static Boolean PreferencesFormHandleEvent(EventType *eventP)
{
    Boolean handled = false;
    FormType *frmP;

    switch (eventP->eType)
    {
        case frmOpenEvent:
            frmP = FrmGetActiveForm();
            FrmDrawForm(frmP);
            handled = true;
            break;
            			
	case ctlSelectEvent:

	    switch (eventP->data.ctlSelect.controlID)
	    {
	        case AnalogClockPrefBtn:
	        {
	            FormType *frmP;

	            frmP = FrmInitForm(AngClockPrefMForm);
	            FrmDoDialog(frmP);
	            FrmDeleteForm(frmP);

	            handled = true;
	            break;
	        }

	        case PreferencesBackBtn:
	            FrmGotoForm(MainForm);
	            handled = true;
	            break;
	    }

	    break;
    }

    return handled;
}


// Analog Clock Preferences Modal Form
static Boolean AngClockPrefMFormHandleEvent(EventType *eventP)
{
    Boolean handled = false;
    FormType *frmP;

    switch (eventP->eType)
    {
        case frmOpenEvent:
        {
            ControlType *popupP;
            ListType *listP;

            frmP = FrmGetActiveForm();
            FrmDrawForm(frmP);

            popupP = GetObjectPtr(ClockMarkersPopup);
            listP  = GetObjectPtr(ClockMarkersList);

            CtlSetLabel(
                popupP,
                LstGetSelectionText(
                    listP,
                    LstGetSelection(listP)
                )
            );

            handled = true;
            break;
        }

        case popSelectEvent:
        {
            handled = true;
            break;
        }

        case ctlSelectEvent:

            switch (eventP->data.ctlSelect.controlID)
            {
                case AngClockPrefBackBtn:
                    FrmReturnToForm(0);
                    handled = true;
                    break;
            }

            break;
    }

    return handled;
}


/*
 * FUNCTION: AppHandleEvent
 *
 * DESCRIPTION: 
 *
 * This routine loads form resources and set the event handler for
 * the form loaded.
 *
 * PARAMETERS:
 *
 * event
 *     a pointer to an EventType structure
 *
 * RETURNED:
 *     true if the event was handled and should not be passed
 *     to a higher level handler.
 */

static Boolean AppHandleEvent(EventType * eventP)
{
	UInt16 formId;
	FormType * frmP;

	if (eventP->eType == frmLoadEvent)
	{
		/* Load the form resource. */
		formId = eventP->data.frmLoad.formID;
		frmP = FrmInitForm(formId);
		FrmSetActiveForm(frmP);

		/* 
		 * Set the event handler for the form.  The handler of the
		 * currently active form is called by FrmHandleEvent each
		 * time is receives an event. 
		 */
		switch (formId)
		{
		    case MainForm:
		        FrmSetEventHandler(frmP, MainFormHandleEvent);
		        break;

		    case PreferencesForm:
		        FrmSetEventHandler(frmP, PreferencesFormHandleEvent);
		        break;
		        
		    case AngClockPrefMForm:
			    FrmSetEventHandler(frmP, AngClockPrefMFormHandleEvent);
			    break;
		}
		return true;
	}

	return false;
}

/*
 * FUNCTION: AppEventLoop
 *
 * DESCRIPTION: This routine is the event loop for the application.
 */

static void AppEventLoop(void)
{
    UInt16 error;
    EventType event;
    FormType *mainFormP;

    do
    {
        EvtGetEvent(&event, sysTicksPerSecond);

        // Detect when MainForm becomes obscured or visible again.
        if (event.eType == winExitEvent)
        {
            mainFormP = FrmGetFormPtr(MainForm);

            if (mainFormP != NULL &&
                event.data.winExit.exitWindow == (WinHandle)mainFormP)
            {
                mainFormObscured = true;
            }
        }
        else if (event.eType == winEnterEvent)
        {
            mainFormP = FrmGetFormPtr(MainForm);

            if (mainFormP != NULL &&
                event.data.winEnter.enterWindow == (WinHandle)mainFormP)
            {
                mainFormObscured = false;
            }
        }

        if (!SysHandleEvent(&event))
        {
            if (!MenuHandleEvent(0, &event, &error))
            {
                if (!AppHandleEvent(&event))
                {
                    FrmDispatchEvent(&event);
                }
            }
        }

    } while (event.eType != appStopEvent);
}

/*
 * FUNCTION: AppStart
 *
 * DESCRIPTION:  Get the current application's preferences.
 *
 * RETURNED:
 *     errNone - if nothing went wrong
 */

static Err AppStart(void)
{

	return errNone;
}

/*
 * FUNCTION: AppStop
 *
 * DESCRIPTION: Save the current state of the application.
 */

static void AppStop(void)
{
        
	// Close all the open forms.
	FrmCloseAllForms();

}

/*
 * FUNCTION: RomVersionCompatible
 *
 * DESCRIPTION: 
 *
 * This routine checks that a ROM version is meet your minimum 
 * requirement.
 *
 * PARAMETERS:
 *
 * requiredVersion
 *     minimum rom version required
 *     (see sysFtrNumROMVersion in SystemMgr.h for format)
 *
 * launchFlags
 *     flags that indicate if the application UI is initialized
 *     These flags are one of the parameters to your app's PilotMain
 *
 * RETURNED:
 *     error code or zero if ROM version is compatible
 */

static Err RomVersionCompatible(UInt32 requiredVersion, UInt16 launchFlags)
{
	UInt32 romVersion;

	/* See if we're on in minimum required version of the ROM or later. */
	FtrGet(sysFtrCreator, sysFtrNumROMVersion, &romVersion);
	if (romVersion < requiredVersion)
	{
		if ((launchFlags & 
			(sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp)) ==
			(sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp))
		{
			//FrmAlert (RomIncompatibleAlert);

			/* Palm OS versions before 2.0 will continuously relaunch this
			 * app unless we switch to another safe one. */
			if (romVersion < kPalmOS20Version)
			{
				AppLaunchWithCommand(
					sysFileCDefaultApp, 
					sysAppLaunchCmdNormalLaunch, NULL);
			}
		}

		return sysErrRomIncompatible;
	}

	return errNone;
}

/*
 * FUNCTION: PilotMain
 *
 * DESCRIPTION: This is the main entry point for the application.
 * 
 * PARAMETERS:
 *
 * cmd
 *     word value specifying the launch code. 
 *
 * cmdPB
 *     pointer to a structure that is associated with the launch code
 *
 * launchFlags
 *     word value providing extra information about the launch.
 *
 * RETURNED:
 *     Result of launch, errNone if all went OK
 */
 
UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
    Err error;

    switch (cmd)
    {
        case sysAppLaunchCmdNormalLaunch:
            error = AppStart();
            if (error)
                return error;

            FrmGotoForm(MainForm);
            AppEventLoop();

            AppStop();
            break;
    }

    return errNone;
}