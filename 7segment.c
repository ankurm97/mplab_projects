/* 
 * File:   7segment.c
 * Author: Ankur Mishra
 *
 * Created on July 7, 2018, 1:37 PM
 */
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
#define _XTAL_FREQ 8000000
//***Define the signal pins of all four displays***//
#define s1 RA0
#define s2 RA1
#define s3 RA2
#define s4 RA3
//***End of definition**////
void main()
{
unsigned int a,b,c,d,e,f,g,h; //just variables
int i = 0; //the 4-digit value that is to be displayed
int flag =0; //for creating delay
unsigned int seg[]={0X3F, //Hex value to display the number 0
                    0X06, //Hex value to display the number 1
                    0X5B, //Hex value to display the number 2
                    0X4F, //Hex value to display the number 3
                    0X66, //Hex value to display the number 4
                    0X6D, //Hex value to display the number 5
                    0X7C, //Hex value to display the number 6
                    0X07, //Hex value to display the number 7
                    0X7F, //Hex value to display the number 8
                    0X6F  //Hex value to display the number 9
                   }; //End of Array for displaying numbers from 0 to 9

//*****I/O Configuration****//
TRISA=0X00;
PORTA=0X00;
TRISB=0x00;
PORTB=0X00;

while(1)
{
  //***Splitting "i" into four digits***//  
a=i%10;//4th digit is saved here
b=i/10;
c=b%10;//3rd digit is saved here
d=b/10;
e=d%10; //2nd digit is saved here
f=d/10;
g=f%10; //1st digit is saved here
h=f/10;
//***End of splitting***//
PORTB=seg[a];s1=1; //Turn ON display 1 and print 1st digit
__delay_ms(5);s1=0;     //Turn OFF display 1 after 5ms delay
PORTB=seg[c];s2=1; //Turn ON display 2 and print 2nd digit
__delay_ms(5);s2=0;     //Turn OFF display 2 after 5ms delay
PORTB=seg[e];s3=1; //Turn ON display 3 and print 3rd digit
__delay_ms(5);s3=0;     //Turn OFF display 3 after 5ms delay
PORTB=seg[g];s4=1; //Turn ON display 4 and print 4th digit
__delay_ms(5);s4=0;     //Turn OFF display 4 after 5ms delay
if(flag>=2) //wait till flag reaches
{
    i++;flag=0; //only if flag is 2 "i" will be incremented 
}
flag++; //increment flag for each flash
}
}