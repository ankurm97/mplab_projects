/* 
 * File:   motorcontrol.c
 * Author: Ankur Mishra
 *
 * Created on July 6, 2018, 1:32 PM
 */
#include<xc.h>
#pragma config WRT = OFF
#pragma config FOSC = HS 
#pragma config PWRTE = OFF
#pragma config WDTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CP = OFF 
#pragma config CPD = OFF 
#define DELAY 5
#define FULL_STEP    // change this for the mode of excitation.

#ifdef HALF_STEP
#define SEQ 8
#else
#define SEQ 4
#endif
#ifdef WAVE_DRIVE
unsigned char stepping_seq[4]={0b00001000, 0b00000100, 0b00000010, 0b00000001};
#endif
#ifdef FULL_STEP
unsigned char stepping_seq[4]={0b00001100, 0b00000110, 0b00000011, 0b00001001};
#endif
#ifdef HALF_STEP
unsigned char stepping_seq[8]={0b00001000, 0b00001100, 0b00000100, 0b00000110,
                               0b00000010, 0b00000011, 0b00000001, 0b00001001};
#endif

void main()
{
    unsigned char count = 0;
    TRISD = 0x00;
    while(1)
    {
        if (count == SEQ)
           count = 0;
        PORTD = stepping_seq[count];
        __delay_ms(DELAY);
        count++;
    }
}