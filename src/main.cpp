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

BlynkTimer timer;


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
    Keyfob Keyfob(3,4,5);
    
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
}

/**
 *  @fn     void BLYNK_WRITE(VI)
 *
 *  @brief  #define from Blynk library. Called whenever virtual pin 1
 *          is written to by the Blynk widget. 
 *  
 *  @return N/A
 *
 *  @author Squall-DA
 *
 *  @note   Virtual pin 1 controls the remote start on the keyfob
 *
 */
BLYNK_WRITE(V1)
{
    if( param.asInt() )
    {
        
    }
}