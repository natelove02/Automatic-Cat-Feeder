//Module handles the initialition of GPIO
//Turns on Port B for motor
//Turns on Port C for buttons and also Blynk


void GPIO_Init(void){
  SYSCTL_RCGCGPIO_R |= 0x0007;     // activate clock for Ports A B and C
  while((SYSCTL_PRGPIO_R&0x07) != 0x07){};// wait for clocks to stabilize
		
		  GPIO_PORTB_AFSEL_R &= ~0xC0;     // MRDY {J2.14 TM4C123 PB6, MSP432 P1.7}
  GPIO_PORTB_AMSEL_R &= ~0xC0;     // disable analog functionality on PB6
  GPIO_PORTB_DEN_R |= 0xC0;        // enable digital I/O on PB6
  GPIO_PORTB_DIR_R |= 0xC0;        // output on PB6
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xF0FFFFFF);
		
		
  GPIO_PORTC_LOCK_R = 0x4C4F434B;   // unlock port
	GPIO_PORTC_AMSEL_R &= ~0xF0;      // 3) disable analog functionality on PD4-7
  GPIO_PORTC_PCTL_R &= ~0xFFFF0000; // 4) GPIO
  GPIO_PORTC_DIR_R &= ~0xF0;         // 5) make PC4-7 in
	GPIO_PORTC_PUR_R |= 0x10;          // pull up resistors 
  GPIO_PORTC_AFSEL_R &= ~0xF0;      // 6) regular port function
  GPIO_PORTC_DEN_R |= 0xF0;         // 7) enable digital I/O on PD4-7
	  
}