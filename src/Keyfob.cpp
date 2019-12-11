/** 
 *  @file                   Keyfob.cpp
 *  @brief                  Handles all functions that interface with the
 *                          kefob
 *  @copyright              2017 Squall-DA
 *  @date                   12/04/2017
 * 
 *  @remark Author:         Squall-DA
 *  @remark Project Tree:   BlynkRemoteStarter
 * 
 */

#include "Keyfob.h"

/*========================================================================* 
 *  SECTION - External variables that cannot be defined in header files   * 
 *========================================================================* 
 */

/*========================================================================* 
 *  SECTION - Local function prototypes                                   * 
 *========================================================================* 
 */

/*========================================================================* 
 *  SECTION - Local variables                                             * 
 *========================================================================* 
 */

/**
 *  @fn     Keyfob(uint8_t)
 *
 *  @brief  Creates a Keyfob object for only controlling the starter
 *
 *  @author Squall-DA
 *
 *  @note   N/A
 *
 */
Keyfob::Keyfob(uint8_t ubStarter)
{
    /* This is a starter only object */
    fStarterOnly = true;
    ubStartPin = ubStarter;

    /* Configure the starter pin as an output */
    pinMode(ubStartPin, OUTPUT);
    digitalWrite(ubStartPin,0);
}

/**
 *  @fn     Keyfob(uint8_t, uint8_t, uint8_t)
 *
 *  @brief  Creates a Keyfob object for start, lock and unlock
 *
 *  @author Squall-DA
 *
 *  @note   N/A
 *
 */
Keyfob::Keyfob(uint8_t ubStarter, uint8_t ubUnlock, uint8_t ubLock)
{
    /* This is a starter only object */
    fStarterOnly = false;
    ubStartPin = ubStarter;
    ubUnlockPin = ubUnlock;
    ubLockPin = ubLock;

    /* Configure the pins as output */
    pinMode(ubStartPin, OUTPUT);
    digitalWrite(ubStartPin,HIGH);
    pinMode(ubUnlockPin, OUTPUT);
    digitalWrite(ubUnlockPin,HIGH);
    pinMode(ubLockPin, OUTPUT);
    digitalWrite(ubLockPin,HIGH);
}

/**
 *  @fn     void vStartVehicle()
 *
 *  @brief  Starts the vehicle.
 *
 *  @author Squall-DA
 *
 *  @note   This function uses a state machine combined with 
 *          a timer to create pin output cycle. This should
 *          be modified to match the button presses required
 *          on the keyfob to start the vehicle (double press
 *          start key, press lock then hold start, etc)
 *
 */
void Keyfob::vStartVehicle()
{
    static BUTTON_PRESS_SEQ tStartState = BUTTON_PRESS_1;
    
    /* 2008 Dodge Ram requires double press of the start button */
    switch (tStartState)
    {
        case BUTTON_PRESS_1:
            digitalWrite(ubStartPin, LOW);
            cbTimer.vConfigure(BTN_PRESS_TIME, this, vStartCallback );
            tStartState = PAUSE;
            break;
        case PAUSE:
            digitalWrite(ubStartPin, HIGH);
            cbTimer.vConfigure(PAUSE_TIME, this, vStartCallback );
            tStartState = BUTTON_PRESS_2;
            break;
        case BUTTON_PRESS_2:
            digitalWrite(ubStartPin, LOW);
            cbTimer.vConfigure(BTN_PRESS_TIME, this, vStartCallback );
            tStartState = BUTTON_SEQ_FINISHED;
            break;
        case BUTTON_SEQ_FINISHED:
        default:
            digitalWrite(ubStartPin, HIGH);
            tStartState = BUTTON_PRESS_1;
            break;
    }
}

/**
 *  @fn     void vStartCallback(void * vpObject)
 *
 *  @brief  Static wrapper for Keyfob::vStartVehicle()
 *
 *  @param[in] vpObject void pointer to the keyfob object
 * 
 *  @author Squall-DA
 *
 *  @note   N/A
 *
 */
void Keyfob::vStartCallback(void * vpObject)
{
    Serial.println("Callback");
    ((Keyfob *) vpObject)->vStartVehicle();
} 

/**
 *  @fn     void vLockVehicle()
 *
 *  @brief  Locks the vehicle.
 *
 *  @author Squall-DA
 *
 *  @note   This function uses a state machine combined with 
 *          a timer to create pin output cycle. This should
 *          be modified to match the button presses required
 *          on the keyfob to lock the vehicle (single press, 
 *          double press, etc)
 *
 */
void Keyfob::vLockVehicle()
{
    static BUTTON_PRESS_SEQ tLockState = BUTTON_PRESS_1;
    
    /* Single press of lock button */
    switch (tLockState)
    {
        case BUTTON_PRESS_1:
            digitalWrite(ubLockPin, LOW);
            cbTimer.vConfigure(BTN_PRESS_TIME, this, vLockCallback );
            tLockState = BUTTON_SEQ_FINISHED;
            
            break;
        case BUTTON_SEQ_FINISHED:
        default:
            digitalWrite(ubLockPin, HIGH);
            tLockState = BUTTON_PRESS_1;
            break;
    }
}

/**
 *  @fn     void vLockCallback(void * vpObject)
 *
 *  @brief  Static wrapper for Keyfob::vLockVehicle()
 *
 *  @param[in] vpObject void pointer to the keyfob object
 * 
 *  @author Squall-DA
 *
 *  @note   N/A
 *
 */
void Keyfob::vLockCallback(void * vpObject)
{
    ((Keyfob *) vpObject)->vLockVehicle();
} 

/**
 *  @fn     void vUnlockVehicle()
 *
 *  @brief  Unlocks the vehicle.
 *
 *  @author Squall-DA
 *
 *  @note   This function uses a state machine combined with 
 *          a timer to create pin output cycle. This should
 *          be modified to match the button presses required
 *          on the keyfob to unlock the vehicle (single press, 
 *          double press, etc)
 *
 */
void Keyfob::vUnlockVehicle()
{
    static BUTTON_PRESS_SEQ tUnlockState = BUTTON_PRESS_1;
    
    /* Single press of unlock only unlocks the driver door */
    switch (tUnlockState)
    {
        case BUTTON_PRESS_1:
            digitalWrite(ubUnlockPin, LOW);
            cbTimer.vConfigure(BTN_PRESS_TIME, this, vUnlockCallback );
            tUnlockState = BUTTON_SEQ_FINISHED;
            
            break;
        case BUTTON_SEQ_FINISHED:
        default:
            digitalWrite(ubUnlockPin, HIGH);
            tUnlockState = BUTTON_PRESS_1;
            break;
    }
}

/**
 *  @fn     void vUnlockCallback(void * vpObject)
 *
 *  @brief  Static wrapper for Keyfob::vUnlockVehicle()
 *
 *  @param[in] vpObject void pointer to the keyfob object
 * 
 *  @author Squall-DA
 *
 *  @note   N/A
 *
 */
void Keyfob::vUnlockCallback(void * vpObject)
{
    ((Keyfob *) vpObject)->vUnlockVehicle();
} 

/**
 *  @fn     void vRun()
 *
 *  @brief  Service routine for the Keyfob class
 *
 *  @author Squall-DA
 *
 *  @note   This service routine currently only runs
 *          the CBTimer service routine to update the
 *          timer clock.
 *
 */
void Keyfob::vRun()
{
    /* Run the Callback timer routine */
    cbTimer.vRun();
}