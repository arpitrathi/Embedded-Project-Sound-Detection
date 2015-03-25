/*****************************************************
This program was produced by the
CodeWizardAVR V2.04.6 Evaluation
Automatic Program Generator
� Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Sound Following Robot
Version : 1.0
Date    : 09-Mar-2015
Author  : Aman, Arpit, Ashish
Company : MNNIT
Comments: 


Chip type               : ATmega8
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/

#include <mega8.h>

#include <delay.h>

#define ADC_VREF_TYPE 0x40
#define threshold 100
// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=0x40;
// Wait for the AD conversion to complete
while ((ADCSRA & 0x10)==0);
ADCSRA|=0x10;
return ADCW;
}

// Declare your global variables here
int ad1 = 0,ad2 = 0,ad3 = 0,scene = -1,right = 0,left = 0,right90 = 0;
double thetha = 0,answer = 0;

/*
*   setflag function will set the ad_i when ith sensor adc value will be greater than the threshold  
*/
int setflag () {
    int value0 = read_adc(PC.0);
    int value1 = read_adc(PC.1);
    int value2 = read_adc(PC.2); 
    
    if(value0 >= threshold) {
        ad0 = 1;
    }
    if(ad1 >= threshold) {
        ad1 = 1;
    }
    if(value2 >= threshold) {
        ad2 = 1;
    }      
    
    return (ad0 + ad1 + ad2);
}

void calc_answer() {
    if(right == 1 && right90 == 0) {
        answer = thetha;
    }
    else if(right == 1 && right90 == 1) {
        answer = thetha + 90;
    }
    else if(left  == 1 && right90 == 1) {
        answer = thetha + 180;
    } else {
        answer = 270 + thetha;
    } 
}
void first() {
    if(ad0 == 1 && ad1 == 0 && ad2 == 0) {     //scene0
        right = 1;
        scene = 0;
        //starttimer;
    }
    if(ad1 == 1 && ad0 == 0 && ad2 == 0) {      //scene1
        left = 1;
        scene = 1;
        //starttimer;
    }
    if(ad2 == 1 && ad1 == 0 && ad0 == 0) {     //scene2
        right90 = 1;
        scene = 2;
    }
    if(ad0 == 1 && ad2 == 1 && ad1 == 0) {
        answer = 120;
    }
    if(ad0 == 1 && ad1 == 1 && ad2 == 0) {
        answer = 0;
    }
    if(ad1 == 1 && ad2 == 1 && ad2 == 0) {
        answer = 240;
    }
    return ;   
}

int second() {
    int second_flag = 0;
     if(scene == 0) {
        if(ad1 == 1) {
            //stop timer
            //calculate delta_T
            rotate90 = 0;//0 here
            //calculate thetha using delta_T
            calc_answer();
        }
        else if(ad2 == 1) {
            rotate90 = 1;
            second_flag = 1;
        }
        if(ad1 == 1 && ad2 == 1) {
            answer = 60;
        }
     }
     else if(scene == 1) {
        if(ad0 == 1) {
            //stop timer
            //calculate delta_T
            rotate90 = 0;
            //calculate thetha using delta_T
            calc_answer();
        }
        else if(ad2 == 1) {
            rotate90 = 1;
            second_flag = 1;
        }
        if(ad0 == 1 && ad2 == 1) {
            answer = 300;
        }       
     }
     else if(scene == 2) {
        if(ad0 == 1) {
            right = 1;
            //start timer
            second_flag = 1;
        }
        else if(ad1 == 1) {
            //start timer;
            left = 1;// here left
            second_flag = 1;
        }
        if(ad0 == 1 && ad1 == 1) {
            answer = 180;
        }
     }     
     return second_flag;
}

int third() {
    int finish = 0;
    if(scene == 0) {
        if(ad1 == 0) {
            finish = 1;
        }
    }
    else if(scene == 1) {
        if(ad0 == 1) {
            finish = 1;
        }
    }
    else if(scene == 2) {
        if(ad1 == 1) {
            finish = 1;
        }
        else if(ad0 == 1) {
            finish = 1;
        }
    }
    
    if(finish == 1) {
        //stop timer
        //calculate delta_T
        //calculate thetha using delta_T
        calc_answer();
    }
    return finish;
}
void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port B initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTB=0x00;
DDRB=0x00;

// Port C initialization
// Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTC=0x00;
DDRC=0x00;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTD=0x00;
DDRD=0x00;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
TCCR0=0x00;
TCNT0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=FFFFh
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=FFh
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
MCUCR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC Clock frequency: 62.500 kHz
// ADC Voltage Reference: AVCC pin
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0x87;
        
        
        while(setflag() < 0) { // this loop will break only when any of the sensor receives sound
            ;
        }
        first();
        if(answer == -1) {
            while(setflag() < 2) { //this loop will break only when two of the sensor receives sound
                ;
            }
            if(second() == 1 && answer == -1) {
                while(setflag() != 3) { //this loop will end when all the sensors will receieve sound
                    ;
                }
                third();
            }
            
        }
      //display answer on LCD
      
}
