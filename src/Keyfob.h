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
#include <stdint.h>
#include <Arduino.h>

#ifndef KEYFOB_MODULE
#define KEYFOB_MODULE 1

/*========================================================================* 
 *  SECTION - Global definitions 
 *========================================================================* 
 */

/**
 *  @class  Keyfob
 *
 *  @brief  Object to interface with a vehicles remote keyfob
 *
 *  @author Squall-DA
 *
 *  @note   NA
 *
 */
class Keyfob 
{
    uint8_t ubStartPin, ubUnlockPin, ubLockPin;
    bool fStarterOnly = false;
    CBTimer cbTimer;
public:
    Keyfob(uint8_t);
    Keyfob(uint8_t, uint8_t, uint8_t);
    void vStartVehicle();
    void vUnlockVehicle();
    void vLockVehicle();
    void vRun(); 
}; /* End of Keyfob class */


typedef enum Starter_Seq
{
    BUTTON_PRESS_1
    ,PAUSE
    ,BUTTON_PRESS_2
    ,START_FINISHED 
}STARTER_SEQ;

#define BTN_PRESS_TIME 50 /* ms */
#define PAUSE_TIME     25 /* ms */

/*========================================================================* 
 *  SECTION - extern global variables (minimize global variable use)      * 
 *========================================================================* 
 */

/*========================================================================* 
 *  SECTION - extern global functions                                     * 
 *========================================================================* 
 */

#endif  /* #ifndef KEYFOB_MODULE */