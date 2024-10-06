/**************************************************************************************
 Name        : stopwatch.c
 Author      : Rawan Mohamed Fathy
 Description : Stop watch with Dual Mode (Count up and Count down) Using ATmega32
 	 	 	   and six Seven-Segment Display.
**************************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
/**********************************global variables**********************************/
unsigned char seconds=0,minutes=0,hours=0,toggle_to_count_down_mode=0;

unsigned char hours_INC_flag   = 0 ,hours_DEC_flag   = 0;
unsigned char minutes_INC_flag = 0 ,minutes_DEC_flag = 0;
unsigned char seconds_INC_flag = 0 ,seconds_DEC_flag = 0;

unsigned char one_press=0,toggle_mode=0;

/******************************************ISR functions******************************************/
//ISR(TIMER1_COMPA_vect) {
//	timer_flag =1;
//}

ISR(TIMER1_COMPA_vect) {

		if (toggle_to_count_down_mode == 0)  //by default count up mode select
		{
			seconds++; 						//every compare match increment number of seconds
				if (seconds == 60)			// 60 seconds equal to 1 minute
				{
					minutes++;
					seconds = 0;
				}
				if (minutes == 60) 			// 60 minutes equal to 1 hour
				{
					hours++;
					minutes = 0;
				}
				if (hours == 24) 			// if the stop watch reach to 24 hour, it will be reset
				{							//one day = 24 hours
					seconds = 0;
					minutes = 0;
					hours = 0;
				}
		}
		else
		{
			// Count Down Mode
			if (seconds == 0 && hours == 0 && minutes == 0) {
				PORTD |= (1 << PD0);
			}

			if (seconds > 0) {
				seconds--;
			} else if (minutes > 0) {
				seconds = 59;
				minutes--;
			} else if (hours > 0) {
				seconds = 59;
				minutes = 59;
				hours--;
			}
		}

}


ISR(INT0_vect) {
	//when INT0 triggered, stop watch time should be reset by reset all variables
	TCNT1 = 0;
	seconds = 0;
	minutes = 0;
	hours = 0;
}

ISR(INT1_vect) {
	//when INT1 triggered, stop watch time should be paused by disable timer1 by disable clock
	TCCR1B &= ~(1 << CS10) &  ~(1 << CS11) &  ~(1 << CS12);
}

ISR(INT2_vect) {
	//when INT2 triggered, stop watch time should be resumed by enable clock to enable timer1
	TCCR1B |= (1 << CS10) | (1 << CS12);
}

/************************************************************************************
 * Function Name   : Seven_Segment_Multiplexed_Display_Time
 * Function Inputs : void
 * Description     : Function to display time on multiplexed six 7-Segment
 ************************************************************************************/
void  Seven_Segment_Multiplexed_Display_Time(void) {

	/*   HOURS	    MIN        SEC    */
		/* PA5	PA4   PA3  PA2	 PA1  PA0 */
	/* 0 0  0	 0	   0	0 	  0	   1  */
		PORTA = (PORTA & 0xC0) | 0x01;						/* enable first digit in seconds */
		PORTC = (PORTC & 0xF0) | ((seconds % 10) & 0x0F);	/* put the value of first digit in seconds*/
		_delay_ms(2);   									/*delay to show the number on 7-segment*/

		/*   HOURS	    MIN     	SEC   */
		/* PA5	PA4   PA3  PA2	 PA1  PA0 */
	/* 0 0  0	 0	   0	0 	  1	   0  */
		PORTA = (PORTA & 0xC0) | 0x02;						/* enable second digit in seconds */
		PORTC = (PORTC & 0xF0) | ((seconds / 10) & 0x0F);	/* put the value of second digit in seconds*/
		_delay_ms(2);										/*delay to show the number on 7-segment*/

		/*   HOURS	    MIN     	SEC   */
		/* PA5	PA4   PA3  PA2	 PA1  PA0 */
	/* 0 0  0	 0	   0	1 	  0	   0  */
		PORTA = (PORTA & 0xC0) | 0x04;					    /* enable first digit in minutes */
		PORTC = (PORTC & 0xF0) | ((minutes % 10) & 0x0F);   /* put the value of first digit in minutes*/
		_delay_ms(2);										/*delay to show the number on 7-segment*/

		/*   HOURS	    MIN     	SEC   */
		/* PA5	PA4   PA3  PA2	 PA1  PA0 */
	/* 0 0  0	 0	   1	0	  0	   0  */
		PORTA = (PORTA & 0xC0) | 0x08;						/* enable second digit in minutes */
		PORTC = (PORTC & 0xF0) | ((minutes / 10) & 0x0F);	/* put the value of second digit in minutes */
		_delay_ms(2);										/*delay to show the number on 7-segment*/

		/*   HOURS	    MIN     	SEC   */
		/* PA5	PA4   PA3  PA2	 PA1  PA0 */
	/* 0 0  0	 1	   0	0	  0	   0  */
		PORTA = (PORTA & 0xC0) | 0x10;						/* enable first digit in hours */
		PORTC = (PORTC & 0xF0) | ((hours % 10) & 0x0F);		/* put the value of first digit in hours */
		_delay_ms(2);										/*delay to show the number on 7-segment*/

		/*   HOURS	    MIN     	SEC   */
		/* PA5	PA4   PA3  PA2	 PA1  PA0 */
	/* 0 0  1	 0	   0	0	  0	   0  */
		PORTA = (PORTA & 0xC0) | 0x20;						/* enable second digit in hours */
		PORTC = (PORTC & 0xF0) | ((hours / 10) & 0x0F);     /* put the value of second digit in hours*/
		_delay_ms(2);										/*delay to show the number on 7-segment*/
}
/************************************************************************************
 * Function Name   : TIMER1_CTC_Init
 * Function Inputs : void
 * Description     : Function to initialize timer1.
 ************************************************************************************/
/*
 * F_CPU     = 16Mhz   , pre-scaler (N) = 1024
 * F_timer   = (F_CPU/N)   = (16Mhz/1024) = 16Khz
 * T_timer   = (1/F_timer) = (1/16Khz)    = 62.5microsec
 * T_compare = 16000 * 62.5micro = 1sec
 * number_of_compare_matches_per_second = (1/1)= 1
 */
void TIMER1_CTC_Init(void) {
	TCCR1A = (1 << FOC1A)| (1<<FOC1B);				  //set 2 bits if specifies a non-PWM mode
	TCCR1B = (1 << WGM12) | (1 << CS10) | (1 << CS12);//CTC Mode , top =OCR1A ,pre-scaler 1024
	TCNT1 = 0;    									  // start timer from 0
	OCR1A = 16000;									  //set compare match value for 1 second
	TIMSK |= (1 << OCIE1A);							  // enable output compare A match interrupt
	SREG |=(1<<7);
}
/************************************************************************************
 * Function Name   : INT0_Init
 * Function Inputs : void
 * Description     : Function to initialize INT0.
 ************************************************************************************/
void INT0_Init(void) {
	//Works with falling edge
	DDRD  &= ~(1 << PD2);		//define PD2 as input
	MCUCR |= (1 << ISC01);  	//falling edge configuration
	GICR  |= (1 << INT0);   	//external INT0 enable
	PORTD |= (1 << PD2);		//internal pull-up resistor for PD2
}
/************************************************************************************
 * Function Name   : INT1_Init
 * Function Inputs : void
 * Description     : Function to initialize INT1.
 ************************************************************************************/
void INT1_Init(void) {
	//Works with raising edge
	DDRD  &= ~(1 << PD3);					//define PD3 as input
	MCUCR |= (1 << ISC10) | (1 << ISC11);	//rising edge configuration
	GICR  |= (1 << INT1);					//external INT1 enable
}
/************************************************************************************
 * Function Name   : INT2_Init
 * Function Inputs : void
 * Description     : Function to initialize INT2.
 ************************************************************************************/
void INT2_Init(void) {
	//Works with falling edge
	DDRB &= ~(1 << PB2);		//define PB2 as input
	MCUCSR &= ~(1 << ISC2);		//falling edge configuration
	GICR |= (1 << INT2);		//external INT2 enable
	PORTB |= (1 << PB2);		//internal pull-up resistor for PB2
}

/************************************************************************************
 * Function Name   : Select_Mode
 * Function Inputs : void
 * Description     : Function to select mode (count up mode (default) or count down mode).
************************************************************************************/
void Select_Mode(void) {

	if (toggle_mode==1)  // select count down mode
	{
		toggle_to_count_down_mode = 1;
		PORTD |= (1 << PD5); 	// Turn on yellow LED for count down mode
		PORTD &= ~(1 << PD4); 	// Turn off red LED for count up mode

		/* Hours_INC	 Hours_DEC	|  MIN_INC	MIN_DEC  | SEC_INC  SEC_DEC     */
		/*  PB1 		  PB0       |  PB4       PB3     | PB6       PB5  		*/
/**************************************Adjust hours**************************************/
		if (!(PINB & (1 << PB1))) 			//if PB1 is pressed, hours will increment by one every press
		{
			if (hours_INC_flag == 0) 		//to ensure that io one press only
			{
				hours = (hours + 1) % 25;   //increment hours within range 0:24
				hours_INC_flag = 1;
			}
		 } else
			{
				hours_INC_flag = 0;			// reset the flag when the button is released
			}

		 Seven_Segment_Multiplexed_Display_Time(); // Display six multiplexed 7-segment time

		 if (!(PINB & (1 << PB0)))  			//if PB0 is pressed, hours will decrement by one every press
		 {

			 if (hours_DEC_flag == 0) 			//to ensure that is one press only
			 {
				 hours = (hours + 24) % 25; 	//decrement hours within range 0:24
				 hours_DEC_flag = 1;
			 }
		 } else
		 	 {
			 	 hours_DEC_flag = 0; 			// reset the flag when the button is released
		 	 }
		 Seven_Segment_Multiplexed_Display_Time(); // Display six multiplexed 7-segment time

/**************************************Adjust minutes**************************************/
		 if (!(PINB & (1 << PB4)))  			//if PB4 is pressed, minutes will increment by one every press
		 {
			 if (minutes_INC_flag == 0)  		//to ensure that is one press only
			 {
				 minutes = (minutes + 1) % 60; //increment minutes within range 0:59
				 minutes_INC_flag = 1;
			 }
		 } else
		 	 {
			 	 minutes_INC_flag = 0;			// reset the flag when the button is released
		 	 }
	  Seven_Segment_Multiplexed_Display_Time(); // Display six multiplexed 7-segment time
	  if (!(PINB & (1 << PB3))) 				//if PB3 is pressed, seconds will decrement by one every press
	  {

		if (minutes_DEC_flag == 0) 					//to ensure that is one press only
			{
			 	 minutes = (minutes + 59) % 60;		//decrement minutes within range 0:59
			 	 minutes_DEC_flag = 1;
			}
	  } else
		{

		minutes_DEC_flag = 0;						// reset the flag when the button is released
		}
	  Seven_Segment_Multiplexed_Display_Time(); // Display six multiplexed 7-segment time

/**************************************Adjust seconds**************************************/

	  	 if (!(PINB & (1 << PB6)))  			//if PB6 is pressed, seconds will increment by one every press
	  	  {
	  		  if (seconds_INC_flag == 0) 		//to ensure that is one press only
	  		  {
	  			  seconds = (seconds + 1) % 60;	//increment seconds within range 0:59
	  			  seconds_INC_flag = 1;
	  		  }
	  	  } else
	  	  	  {
	  		  	  seconds_INC_flag = 0;			// reset the flag when the button is released
	  	  	  }
	  	 Seven_Segment_Multiplexed_Display_Time(); // Display six multiplexed 7-segment time

	  	 if (!(PINB & (1 << PB5)))  			//if PB5 is pressed, seconds will decrement by one every press
	  	 {
	  		 if (seconds_DEC_flag == 0) 		//to ensure that is one press only
	  		 {
	  			 seconds = (seconds + 59) % 60; //decrement seconds within range 0:59
	  			 seconds_DEC_flag = 1;
	  		 }
	  	 } else
	  	 	 {
	  		 	 seconds_DEC_flag = 0;			// reset the flag when the button is released
	  	 	 }

	  Seven_Segment_Multiplexed_Display_Time(); // Display six multiplexed 7-segment time

		}
		 else
		 {
			PORTD &= ~(1 << PD5); 						// Turn off yellow LED for count down
			PORTD &= ~(1 << PD0); 						// Turn off BUZZER
			toggle_to_count_down_mode = 0; 				// Turn off count down mode
			PORTD |= (1 << PD4); 						// Turn on red LED for count up mode
		 }
}

/******************************************main function******************************************/
int main(void) {

	SREG |= (1 << 7);					//enable global interrupt (I-Bit)

	DDRD  |=(1<<0);						//Set PD0 to Buzzer as output
	PORTD &= ~(1<<0);					//turn off the buzzer at the beginning

	DDRD  |= (1<<4) | (1<<5);			//Set 2 led red yellow as output pins
	PORTD |= (1<<4);					//by default turn on count up (red) led
	PORTD &= ~(1<<5);					//by default turn off count down (yellow) led

	DDRB  = 0x00;						// Set pin 7 in PORTB as input pin (buttons)
	PORTB = 0xFF;						//internal pull-up resistor for all PortB

	DDRA  |= 0x7F;	 			// Set first 6-pins in PORTA as output To enable/disable the six 7-segments
	PORTA &= 0x80;	 			// put 0 value  in PORTA to enable first 6-pins (six 7-segments)

	DDRC  |= 0x0F;	 			// Set first 4-pins in PORTC as output pins PC0 PC1 PC2 PC3 for decoder
	PORTC &= 0xF0;	 			// put 0 as initial value in first 4-pins in PORTC to display 0 on 7-segments

	/*initializations*/
	TIMER1_CTC_Init();
	INT0_Init();
	INT1_Init();
	INT2_Init();

	while (1) {

		Seven_Segment_Multiplexed_Display_Time();  		//display six multiplexed 7-segment time

		/*turn off the buzzer at not zero sec or min or hour or the timer is paused*/
		if(seconds != 0 || hours != 0 || minutes != 0 || ((TCCR1B & 0x07)==0))
		{
			PORTD &= ~(1 << PD0);
		}

		if (!(PINB & (1 << PB7)))  					// PB7 is pressed (toggle button)
		{
			_delay_ms(30);
			if (!(PINB & (1 << PB7)))  				//second check due to switch de-bouncing
			{
				if(one_press == 0)
				{
					if(((TCCR1B & 0x07)==0))  		//accept toggle when timer is off
					{
						toggle_mode =!toggle_mode; //toggle between count up and count down modes
						one_press = 1;
					}
				}
			}
		}
		else
		{
			  one_press = 0;				// button is released reset the button flag to value 0 again.
		}

		Select_Mode(); 						//function to select count up mode or count down mode
		Seven_Segment_Multiplexed_Display_Time();  		//display six multiplexed 7-segment time
	}
}
