#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "string.h"
#include "Gif.c"
#include "../inc/tm4c123gh6pm.h"
#include "../inc/PLL.h"
#include "../inc/LED.h"
#include "../Lab3/buttons.h"
#include "../inc/Timer1A.h"
//#include "../inc/Timer2A.h"
//#include "../inc/Timer3A.h"
#include "../inc/UART.h"
#include "../inc//PortF.h"
#include "Timer2.h"
#include "Timer3.h"
#include "../inc/Timer5A.h"
#include "WIFICOMMS.c"
#include "GPIO.c"
#include "MotorControl.c"
/* List of Things:
Buttons
Screen
WiFi
Motor
*/





int timerCounter;
int timerStarted;

 uint32_t pin_num; 
 uint32_t pin_int;
 uint32_t LastF;    // Vp74
 uint32_t LED;      // VP1
 int blynkPin;
int blynkVal;

int counter;




// Counts for one second for our LCD counter
//Works when activated with Blynk
void oneSec(){

	
		ST7735_SetCursor(0,12);
		ST7735_OutString("Time Remaining(min):");
		ST7735_SetCursor(0,13);
		ST7735_OutUDec4((timerCounter)/60);

	timerCounter--;

}





//Main Below calls different modules within program to run our feeder
//General outline of flow is as follows
//Initilizations
//ESP setup, Timer Set Ups
//Check if inputs from user have been pushed and if so execute code

	
int main(){
	PLL_Init(Bus80MHz);   
	GPIO_Init();
	PortF_Init();
	LastF = PortF_Input();
	LED_Init();
	buttonsInit();
	ST7735_InitR(INITR_REDTAB);

	counter = 0;
	GPIO_PORTB_DATA_R &= ~0xC0;
	
	toggleGif();

	
	
	UART_Init(5);         // Enable Debug Serial Port
//  UART_OutString("\n\rEE445L Lab 4D\n\rBlynk example");
//#endif
  ESP8266_Init();       // Enable ESP8266 Serial Port
  ESP8266_Reset();      // Reset the WiFi module
  ESP8266_SetupWiFi();  // Setup communications to Blynk Server  
  
  Timer2_Init(&Blynk_to_TM4C,1600000); 
  // check for receive data from Blynk App every 10ms

  Timer3_Init(&SendInformation,40000000); 
	
	ST7735_FillScreen(0x0000);
	
	timerStarted = 0;
	timerCounter = 216000;
	
	while(1){
//		ST7735_OutString("Pin: ");
//		ST7735_OutUDec(blynkPin);
//		ST7735_OutString("Val: ");
//		ST7735_OutUDec(blynkVal);
		//Checks timer command from Blynk
	if (blynkPin == 2&& blynkVal == 1){
		if(timerStarted == 0){
			Timer5A_Init(&oneSec, 80000000,4);
			timerStarted = 1;
		}
	
	}	
	//Checks Button Press from Blynk
	else if(blynkPin == 2&& blynkVal == 0){
		if(timerStarted == 1)
			Timer5A_Stop();
		timerStarted = 0;
	}
		
		//Checks button press on Blynk and on the device
	if ((blynkPin == 1&& blynkVal == 1)||(checkPressed(0))||(timerCounter == 0)){
		while(blynkPin == 1&& blynkVal == 1);
		//GPIO_PORTB_DATA_R &= ~0xC0;
		counter = 0; // set despensed amount 0 
		GPIO_PORTB_DATA_R &= ~0x40;
		GPIO_PORTB_DATA_R |= 0x80;	
		
		//LED_GreenToggle();
		timerCounter = 216000; // 12 hours in seconds 
		}
		
	
		
	}	 


}


