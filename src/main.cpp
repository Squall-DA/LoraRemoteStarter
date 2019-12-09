/** 
 *  @file                   main.cpp
 *  @brief                  Main source file for remote starter
 *  @copyright              2017 Squall-DA
 *  @date                   12/04/2017
 * 
 *  @remark Author:         Squall-DA
 *  @remark Project Tree:   LoraRemoteStarter
 * 
 */

/* Includes */
#include "main.h"

#include <stdint.h>
#include "Keyfob.h"
#include "LoRa.h"
#include "SSD1306.h"


/*========================================================================* 
 *  SECTION - External variables that cannot be defined in header files   * 
 *========================================================================* 
 */

/*========================================================================* 
 *  SECTION - Local function prototypes                                   * 
 *========================================================================* 
 */

void vLoRa_rxMode(void);
void vLoRaOnReceiveMsg(int swPacketSize);

/*========================================================================* 
 *  SECTION - Local variables                                             * 
 *========================================================================* 
 */

/* Define the vehicle keyfob object 
*  I am using the lock, unlock, and start keyfob
*/
Keyfob ramKeyfob(START_PIN,UNLOCK_PIN,LOCK_PIN);

/* Setup the OLED display at address 0x3c using standard SDA and SCL */
SSD1306 oledDisplay(0x3c,SDA,SCL);

/* LoRa Frequency */
const uint32_t kulFrequency = 915E6;

/* LoRa Pins */ 
const uint8_t kubLoraCsPin = 18;
const uint8_t kubLoraIrqPin = 26;
const uint8_t kubLoraRstPin = 0;  //Throwaway pin Rst not actually connected.


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
    pinMode(16,OUTPUT);
    digitalWrite(16, LOW);    // set GPIO16 low to reset OLED
    delay(50); 
    digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high、

    /* Init screen */
    oledDisplay.init();
    oledDisplay.flipScreenVertically();  
    oledDisplay.setFont(ArialMT_Plain_10);
    oledDisplay.setTextAlignment(TEXT_ALIGN_LEFT);

    // Debug console
    Serial.begin(115200);

    while (!Serial);

    /* Configure ESP32 SPI */
    SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);

    /* Set lora pins */
    LoRa.setPins(kubLoraCsPin, kubLoraRstPin, kubLoraIrqPin);

    /* Initialize lora frequency */
    if(!LoRa.begin(kulFrequency))
    {
        oledDisplay.drawString(0,0,"LoRa Init Error");
        oledDisplay.display();
        while(1);
    }
    else
    {
      oledDisplay.drawString(0,0,"LoRa Initialized"); 
      oledDisplay.display(); 
    }
    
    LoRa.onReceive(vLoRaOnReceiveMsg);
    vLoRa_rxMode();
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
    ramKeyfob.vRun();
}

/**
 * @fn     void vLoRa_rxMode(void)
 * 
 *  @brief  Inverts IQ for node GW communications and sets 
 *          receive mode
 *  
 *  @return N/A
 *
 *  @author Squall-DA
 *
 *  @note   N/A
 *
 */
void vLoRa_rxMode(void){
    LoRa.enableInvertIQ();                // active invert I and Q signals
    LoRa.receive();                       // set receive mode
}

void vLoRaOnReceiveMsg(int swPacketSize)
{
    oledDisplay.clear();
    oledDisplay.drawString(0,0, "LoRa msg received.");
    oledDisplay.drawString(0,0, "Size: " + swPacketSize);
    oledDisplay.display();
}