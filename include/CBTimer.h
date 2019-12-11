/** 
 *  @file                   CBTimer.h
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
#include <stdint.h>
#include <Arduino.h>

#ifndef CBTIMER_MODULE
#define CBTIMER_MODULE 1

/*========================================================================* 
 *  SECTION - Global definitions 
 *========================================================================* 
 */

/**
 *  @class  CBTimer
 *
 *  @brief  Class to create a timer object.
 *
 *  @author Squall-DA
 *
 *  @note   NA
 *
 */
class CBTimer
{
    void (* vCallBackFunctionC)() = nullptr;
    void (* vCallBackFunction)(void *) = nullptr;
    uint32_t ulTimeOut, ulStartTime;
    void * vpObjectPtr = nullptr;
public:
    void vConfigure(uint32_t, void (*vCallback)());
    void vConfigure(uint32_t, void *,void (*vCallback)(void *) );
    void vRun();
}; /* End of CBTimer class */


/*========================================================================* 
 *  SECTION - extern global variables (minimize global variable use)      * 
 *========================================================================* 
 */

/*========================================================================* 
 *  SECTION - extern global functions                                     * 
 *========================================================================* 
 */

#endif  /* #ifndef CBTIMER_MODULE */