

//This module controls our motor
//oves the motor back and forth a set number of time to output desired food amount

extern int timerCounter;
extern int timerStarted;
extern int counter;

void swapMotorDir(){
//test comment for one drive


		//print food depensed 
		ST7735_SetCursor(0,5);
		ST7735_OutString("Despensed(g):~");
		ST7735_OutUDec4((.1777*(float)counter));
		
	TM4C_to_Blynk(74,1);
	//rotate forwards
	if(counter%3 == 0){
		GPIO_PORTB_DATA_R = 0x40; //Turn on PB6
		LED_GreenToggle();
		toggleGif();
		
		counter++; 
		
		
	}
	//rotate backwards
	else if (counter < 90){
		GPIO_PORTB_DATA_R = 0x80; //Turn on PB7
		toggleGif();
		
		counter++;
		}
	else{
		GPIO_PORTB_DATA_R = 0x00;
		TM4C_to_Blynk(74,0);
		Timer1A_Stop(); 
		

}



}

