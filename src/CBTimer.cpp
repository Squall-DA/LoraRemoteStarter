/** 
 *  @file                   Timer.cpp
 *  @brief                  Creates a basic timer using the Arduino loop 
 *                          and millis function.
 *  
 *  @copyright              2017 Squall-DA
 *  @date                   12/04/2017
 * 
 *  @remark Author:         Squall-DA
 *  @remark Project Tree:   BlynkRemoteStarter
 * 
 */
#include <Arduino.h>

#include "CBTimer.h"

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
 *  @fn     void vConfigure(uint32_t, void function pointer)
 *
 *  @brief  Configures the timer object. ulTime configures the 
 *          timeout before the callback function is called.
 *
 *  @author Squall-DA
 *
 *  @note   N/A
 *
 */
void CBTimer::vConfigure(uint32_t ulTime, void (*vCallBack)())
{
    vCallBackFunction = vCallBack;
    ulTimeOut = ulTime;
    ulStartTime = millis();
}

/**
 *  @fn     void vRun()
 *
 *  @brief  Function that updates and runs the timer.
 *
 *  @author Squall-DA
 *
 *  @note   N/A
 *
 */
void CBTimer::vRun()
{
    uint32_t ulDeltaTime = 0;

    ulDeltaTime = millis() - ulStartTime;

    if(ulDeltaTime > ulTimeOut)
    {
        vCallBackFunction();
    }
}