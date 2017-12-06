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
    digitalWrite(ubStartPin,0);
    pinMode(ubUnlockPin, OUTPUT);
    digitalWrite(ubUnlockPin,0);
    pinMode(ubLockPin, OUTPUT);
    digitalWrite(ubLockPin,0);
}