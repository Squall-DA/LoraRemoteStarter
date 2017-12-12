/** 
 *  @file                   main.h 
 *  @brief                  main header file
 *  @copyright              2017 Squall-DA
 *  @date                   12/04/2017
 *  
 *  @remark Author:         Squall-DA
 *  @remark Project Tree:   BlynkRemoteStarter
 *  
 */
#ifndef MAIN_MODULE
#define MAIN_MODULE 1


/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#define TINY_GSM_MODEM_SIM900

#define START_PIN    3
#define UNLOCK_PIN   4
#define LOCK_PIN     5

// Default heartbeat interval for GSM is 60
// If you want override this value, uncomment and set this option:
//#define BLYNK_HEARTBEAT 30



#endif  /* #ifndef MAIN_MODULE */