/* 
 * File:   newmain.c
 * Author: Ankur Mishra
 *
 * Created on July 6, 2018, 2:13 PM
 */
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off) 
#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 200000000 //Crystal Frequency, used in delay
#define speed 1 // Speed Range 10 to 1  10 = lowest , 1 = highest
#define steps 200 // how much step it will take
#define clockwise 0 // clockwise direction macro
#define anti_clockwise 1 // anti clockwise direction macro
void system_init (void); // This function will initialise the ports.
void full_drive (char direction); // This function will drive the motor in full drive mode
void half_drive (char direction); // This function will drive the motor in full drive mode
void wave_drive (char direction); // This function will drive the motor in full drive mode
void ms_delay(unsigned int val);
void main(void)
{
system_init();
while(1){
/* Drive the motor in full drive mode clockwise */
for(int i=0;i<steps;i++)
{
            full_drive(clockwise);
}
ms_delay(1000);
/* Drive the motor in wave drive mode anti-clockwise */
for(int i=0;i<steps;i++)
{
            wave_drive(anti_clockwise);
}
ms_delay(1000);
for(int i=0;i<steps;i++)
{
            half_drive(anti_clockwise);
}
ms_delay(1000);
}
}
/*System Initialising function to set the pin direction Input or Output*/
void system_init (void){
    TRISB = 0x00;     // PORT B as output port
    PORTB = 0x0F;
}
/*This will drive the motor in full drive mode depending on the direction*/
void full_drive (char direction){
    if (direction == anti_clockwise){
        PORTB = 0b00000011;
        ms_delay(speed);
        PORTB = 0b00000110;
        ms_delay(speed);
        PORTB = 0b00001100;
        ms_delay(speed);
        PORTB = 0b00001001;
        ms_delay(speed);
        PORTB = 0b00000011;
        ms_delay(speed);
    }
    if (direction == clockwise){
        PORTB = 0b00001001;
        ms_delay(speed);
        PORTB = 0b00001100;
        ms_delay(speed);
        PORTB = 0b00000110;
        ms_delay(speed);
        PORTB = 0b00000011;
        ms_delay(speed);
        PORTB = 0b00001001;
        ms_delay(speed);
    }
}
/* This method will drive the motor in half-drive mode using direction input */
void half_drive (char direction){
    if (direction == anti_clockwise){
        PORTB = 0b00000001;
        ms_delay(speed);
        PORTB = 0b00000011;
        ms_delay(speed);
        PORTB = 0b00000010;
        ms_delay(speed);
        PORTB = 0b00000110;
        ms_delay(speed);
        PORTB = 0b00000100;
        ms_delay(speed);
        PORTB = 0b00001100;
        ms_delay(speed);
        PORTB = 0b00001000;
        ms_delay(speed);
        PORTB = 0b00001001;
        ms_delay(speed);
    }
    if (direction == clockwise){
       PORTB = 0b00001001;
       ms_delay(speed);
       PORTB = 0b00001000;
       ms_delay(speed);
       PORTB = 0b00001100;
       ms_delay(speed); 
       PORTB = 0b00000100;
       ms_delay(speed);
       PORTB = 0b00000110;
       ms_delay(speed);
       PORTB = 0b00000010;
       ms_delay(speed);
       PORTB = 0b00000011;
       ms_delay(speed);
       PORTB = 0b00000001;
       ms_delay(speed);
    }
}
/* This function will drive the the motor in wave drive mode with direction input*/
 
void wave_drive (char direction){
    if (direction == anti_clockwise){
        PORTB = 0b00000001;
        ms_delay(speed);
        PORTB = 0b00000010;
        ms_delay(speed);
        PORTB = 0b00000100;
        ms_delay(speed);
        PORTB = 0b00001000;
        ms_delay(speed);
    }
     if (direction == clockwise){
        PORTB = 0b00001000;
        ms_delay(speed);
        PORTB = 0b00000100;
        ms_delay(speed);
        PORTB = 0b00000010;
        ms_delay(speed);
        PORTB = 0b00000001;
        ms_delay(speed);
    }   
}
/*This function will create required delay*/
void ms_delay(unsigned int val)
{
     unsigned int i,j;
        for(i=0;i<val;i++)
            for(j=0;j<1650;j++);
}