/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.0 Professional
Automatic Program Generator
© Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Sound Detection
Version : 1.0
Date    : 23-03-2015
Author  : NeVaDa
Company : 
Comments: 


Chip type               : ATmega32A
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*****************************************************/

#include <mega32a.h>
#include <stdlib.h>
#include <delay.h>
#include <math.h>
#define tperiod 0.000001
#define sound 343

// Alphanumeric LCD Module functions
#include <alcd.h>
   volatile long int scene=-1,right=1,right90=0,left=1,loop=0;
   float cnt,an,ans1,answer;
   volatile int dispflag=-1,sit=-1; 
   char ch[16];  
   float cal_theta(float cnt)
   {
     return asin((cnt*tperiod)*sound/0.23f)*180.0/PI;
   }
  float cal_main(float thetha) {
    if(right == 1 && right90 == 0) {
        answer = thetha;
    }
    else if(right == 1 && right90 == 1) {
        answer = thetha + 90.0;
    }
    else if(left  == 1 && right90 == 1) {
        answer = thetha + 180.0;
    } else {
        answer = 270.0 + thetha;
    } 
	right=0;left=0;right90=0; 
    loop=0;
    scene=-1;  
    sit=-1;
    dispflag=-1;
    return answer;
} 
void cal_answer(float cnt)
{       lcd_clear();
    lcd_gotoxy(0,0);
    lcd_putsf("Calculating");
    
     an=cal_theta(cnt); 
     ans1=cal_main(an);
    ftoa(ans1,6,ch);
      lcd_clear();
    lcd_gotoxy(0,0);

    lcd_putsf("Angle is");
    lcd_gotoxy(0,1);
    lcd_puts(ch);
    delay_ms(1000);
}

// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{
// Place your code here
   lcd_clear();
    lcd_gotoxy(0,0);
lcd_puts("Listening");
if(scene==-1){
loop=0;
TCNT0=0;  
scene=0;
right=1;
dispflag=-1;  
 }
else if(scene==1){
   cnt=(TCNT0+loop*256);
    if(dispflag==-1){
   cal_answer(cnt);       
dispflag=2; }
        
    if(sit==-1) 
                sit=1;
             }
}

// External Interrupt 1 service routine
interrupt [EXT_INT1] void ext_int1_isr(void)
{
   lcd_clear();
    lcd_gotoxy(0,0);
lcd_puts("Listening");
if(scene==-1){
loop=0;
TCNT0=0;  
scene=1;
left=1;
dispflag=-1;
    }
else if(scene==0 ){
   cnt=(TCNT0+loop*256);
       if(dispflag==-1)
    cal_answer(cnt);
           dispflag=3;
    if(sit==-1) 
    sit=1;

}

// Place your code here

}

// External Interrupt 2 service routine
interrupt [EXT_INT2] void ext_int2_isr(void)
{
   lcd_clear();
    lcd_gotoxy(0,0);
lcd_puts("Listening");
if(scene==-1)
right90=1;
else if(scene==1 || scene==0)
{
  if(sit==-1)
           {
           sit=1;
           right90=1;
           }
}


// Place your code here

}

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
// Place your code here
loop++;
if(loop==240)
loop=0;

}

// Declare your global variables here

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTA=0x00;
DDRA=0x00;

// Port B initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTB=0x00;
DDRB=0x00;

// Port C initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTC=0x00;
DDRC=0x00;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTD=0x00;
DDRD=0x00;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 8000.000 kHz
// Mode: Normal top=0xFF
// OC0 output: Disconnected
TCCR0=0x02;
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
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
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Rising Edge
// INT1: On
// INT1 Mode: Rising Edge
// INT2: On
// INT2 Mode: Rising Edge
GICR|=0xE0;
MCUCR=0x0F;
MCUCSR=0x40;
GIFR=0xE0;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x01;

// USART initialization
// USART disabled
UCSRB=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC disabled
ADCSRA=0x00;

// SPI initialization
// SPI disabled
SPCR=0x00;

// TWI initialization
// TWI disabled
TWCR=0x00;

// Alphanumeric LCD initialization
// Connections specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTA Bit 0
// RD - PORTA Bit 1
// EN - PORTA Bit 2
// D4 - PORTA Bit 4
// D5 - PORTA Bit 5
// D6 - PORTA Bit 6
// D7 - PORTA Bit 7
// Characters/line: 16
lcd_init(16);

// Global enable interrupts
#asm("sei")
   lcd_clear();
               lcd_gotoxy(0,0); 
               lcd_putsf("Welcome All"); 
               delay_ms(1000);
     
 
while (1)
      {
      // Place your code here    
               
               lcd_clear();
               lcd_gotoxy(0,0); 
               lcd_putsf("Ready");
     
      
        if(dispflag == 1)
        {lcd_gotoxy(0,1);    
                lcd_clear();
        
            ftoa(cnt,1,ch)  ;
            dispflag=-1;
            lcd_puts(ch);
            delay_ms(1000);
        }
      }
}
