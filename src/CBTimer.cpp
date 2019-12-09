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
 *  @param[in] ulTime timeout until the callback is called
 *  @param[in] vCallBack pointer to the function to be called
 *
 *  @author Squall-DA
 *
 *  @note   Use this instance to interface with static member
 *          functions or C functions.
 *
 */
void CBTimer::vConfigure(uint32_t ulTime, void (*vCallBack)())
{
    vCallBackFunctionC = vCallBack;
    ulTimeOut = ulTime;
    ulStartTime = millis();
}

/**
 *  @fn     void vConfigure(uint32_t, void *, void function pointer (void *))
 *
 *  @brief  Configures the timer object. ulTime configures the 
 *          timeout before the callback function is called.
 * 
 *  @param[in] ulTime timeout until the callback is called
 *  @param[in] vpObject void pointer to the object of the callback function
 *  @param[in] vCallBack pointer to the function to be called
 *
 *  @author Squall-DA
 *
 *  @note   The callback function of this overload has a void pointer
 *          that is used to point to an object instance. Use this instance
 *          to interface with non static member function wrappers.
 *
 */
void CBTimer::vConfigure(uint32_t ulTime, void * vpObject, void (*vCallBack)(void *))
{
    vCallBackFunction = vCallBack;
    vpObjectPtr = vpObject;
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

    if(nullptr != vCallBackFunction)
    {
        if( (ulDeltaTime > ulTimeOut) 
            && (0 != ulTimeOut))
        {
            if(vpObjectPtr == nullptr)
            {
                    vCallBackFunctionC();
            }
            else
            {
                vCallBackFunction(vpObjectPtr);
            }
            vpObjectPtr = nullptr;
        }
    }
}