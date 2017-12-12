/** 
 *  @file                   main.cpp
 *  @brief                  Main source file for remote starter
 *  @copyright              2017 Squall-DA
 *  @date                   12/04/2017
 * 
 *  @remark Author:         Squall-DA
 *  @remark Project Tree:   BlynkRemoteStarter
 * 
 */

/* Includes */
#include "main.h"

#include <stdint.h>
#include <TinyGsmClient.h>
#include <BlynkSimpleSIM800.h>
#include <SoftwareSerial.h>
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
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "a28e9d33d7814e58ac7ff904fa19b53e";

// Your GPRS credentials
// Leave empty, if missing user or pass
char apn[]  = "YourAPN";
char user[] = "";
char pass[] = "";

/* Use software serial on UNO */
SoftwareSerial SerialAT(7, 8); // RX, TX

/* Set Tiny GSM modem to use software serial */
TinyGsm modem(SerialAT);

/* Define the vehicle keyfob object 
*  I am using the lock, unlock, and start keyfob
*/
Keyfob ramKeyfob(START_PIN,UNLOCK_PIN,LOCK_PIN);


/**
 *  @fn     void setup()
 *
 *  @brief  Runs once at device startup. Is usually used to configure IO
 *  
 *  @return N/A
 *
 *  @author Squall-DA
 *
 *  @note   N/A
 *
 */

void setup() 
{ 
    // Debug console
    Serial.begin(9600);

    delay(10);

    // Set GSM module baud rate
    SerialAT.begin(115200);
    delay(3000);

    // Restart takes quite some time
    // To skip it, call init() instead of restart()
    Serial.println("Initializing modem...");
    modem.restart();

    // Unlock your SIM card with a PIN
    //modem.simUnlock("1234");

    Blynk.begin(auth, modem, apn, user, pass);
}

/**
 *  @fn     void loop()
 *
 *  @brief  NULL loop of the device. Code placed in this functions
 *          runs as fast as the microcontroller will allow it.
 *  
 *  @return N/A
 *
 *  @author Squall-DA
 *
 *  @note   N/A
 *
 */
void loop() 
{
    Blynk.run();
    ramKeyfob.vRun();
}

/**
 *  @fn     void BLYNK_WRITE(V0)
 *
 *  @brief  #define from Blynk library. Called whenever Virtual pin 0
 *          is written to by the Blynk widget. 
 *  
 *  @return N/A
 *
 *  @author Squall-DA
 *
 *  @note   Virtual pin 0 controls the remote start on the keyfob
 *
 */
BLYNK_WRITE(V0)
{
    if( param.asInt() )
    {
        ramKeyfob.vStartVehicle();
        Blynk.virtualWrite(V0,0);
    }
}

/**
 *  @fn     void BLYNK_WRITE(V1)
 *
 *  @brief  #define from Blynk library. Called whenever virtual pin 1
 *          is written to by the Blynk widget. 
 *  
 *  @return N/A
 *
 *  @author Squall-DA
 *
 *  @note   Virtual pin 1 controls the lock on the keyfob
 *
 */
BLYNK_WRITE(V1)
{
    if( param.asInt() )
    {
        ramKeyfob.vLockVehicle();
        Blynk.virtualWrite(V1,0);
    }
}

/**
 *  @fn     void BLYNK_WRITE(V2)
 *
 *  @brief  #define from Blynk library. Called whenever virtual pin 2
 *          is written to by the Blynk widget. 
 *  
 *  @return N/A
 *
 *  @author Squall-DA
 *
 *  @note   Virtual pin 2 controls the unlock on the keyfob
 *
 */
BLYNK_WRITE(V2)
{
    if( param.asInt() )
    {
        ramKeyfob.vUnlockVehicle();
        Blynk.virtualWrite(V2,0);
    }
}