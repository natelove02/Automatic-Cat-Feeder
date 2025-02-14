#include "../Lab4_Blynk_4C123/esp8266.h"


//This code is a combination of the ESP8266 and Blynk Code
//It will create the communcation between our Blynk app and TM4C
//Allows user to trigger feeding via button on app or activate 12 hour timer




char serial_buf[64];
char Pin_Number[2]   = "99";       // Initialize to invalid pin number
char Pin_Integer[8]  = "0000";     //
char Pin_Float[8]    = "0.0000";   //
extern uint32_t pin_num; 
extern uint32_t pin_int;
extern uint32_t LastF;    // Vp74
extern uint32_t LED;      // VP1
extern int blynkPin;
extern int blynkVal;

// ----------------------------------- TM4C_to_Blynk ------------------------------
// Send data to the Blynk App
// It uses Virtual Pin numbers between 70 and 99
// so that the ESP8266 knows to forward the data to the Blynk App
void TM4C_to_Blynk(uint32_t pin,uint32_t value){
  if((pin < 70)||(pin > 99)){
    return; // ignore illegal requests
  }
// your account will be temporarily halted 
  // if you send too much data
  ESP8266_OutUDec(pin);       // Send the Virtual Pin #
  ESP8266_OutChar(',');
  ESP8266_OutUDec(value);      // Send the current value
  ESP8266_OutChar(',');
  ESP8266_OutString("0.0\n");  // Null value not used in this example
}
 
 
// -------------------------   Blynk_to_TM4C  -----------------------------------
// This routine receives the Blynk Virtual Pin data via the ESP8266 and parses the
// data and feeds the commands to the TM4C.
void Blynk_to_TM4C(void){int j; char data;
// Check to see if a there is data in the RXD buffer
	//ST7735_FillScreen(0xFFFF);
  if(ESP8266_GetMessage(serial_buf)){  // returns false if no message

           
// Rip the 3 fields out of the CSV data. The sequence of data from the 8266 is:
// Pin #, Integer Value, Float Value.
    strcpy(Pin_Number, strtok(serial_buf, ","));
    strcpy(Pin_Integer, strtok(NULL, ","));       // Integer value that is determined by the Blynk App
    strcpy(Pin_Float, strtok(NULL, ","));         // Not used
    pin_num = atoi(Pin_Number);     // Need to convert ASCII to integer
    pin_int = atoi(Pin_Integer);  

		//ST7735_FillScreen(0xFFFF);
		if((pin_num == 1)||(pin_num == 2)){
		blynkPin = pin_num;
		blynkVal = pin_int;
		}
		
		
	}
}


void SendInformation(void){
  uint32_t thisF;
	 //Jitter_Measure(); // add this line
  thisF = PortF_Input();
// your account will be temporarily halted if you send too much data
  if(thisF != LastF){
    TM4C_to_Blynk(74, thisF);  // VP74
#ifdef DEBUG3
    Output_Color(ST7735_WHITE);
    ST7735_OutString("Send 74 data=");
    ST7735_OutUDec(thisF);
    ST7735_OutChar('\n');
#endif
  }
  LastF = thisF;
}
