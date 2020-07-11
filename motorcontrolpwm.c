/* 
 * File:   motorcontrolpwm.c
 * Author: Ankur Mishra
 *
 * Created on July 7, 2018, 5:03 PM
 */
#include <xc.h>
#define _XTAL_FREQ   20000000 
#pragma config FOSC = HS       // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
void rundutycycle(unsigned int x );
#define s1           RA0
#define s2           RA1
#define s3           RA2
#define s4           RA3
#define s5           RA4
#define s6           RA5



//_CONFIG( FOSC_HS & WDTE_OFF & PWRTE_ON & CP_OFF & BOREN_ON & LVP_OFF & CPD_OFF & WRT_ON & DEBUG_OFF);
		
		
void main()
{
    ADCON0=0x00;    //ADC turned off
	ADCON1=0x06;    //All pins as digital
    TRISA=0b111111;             //PortA as Input
    TRISC2  = 0;            // Make CCP1 pin as output
	CCP1CON = 0x0C;         // Configure CCP1 module in PWM mode
	PR2   = 0xFF;           // Configure the Timer2 period
    rundutycycle(512);
}
void rundutycycle(unsigned int dutycyc){
T2CON = 0x01;           // Set Prescaler to be 4, hence PWM frequency is set to 4.88KHz.
T2CON |= 0x04;          // Enable the Timer2, hence enable the PWM.
while(1){
	
	CCPR1L   = dutycyc>>2;        	// Put MSB 8 bits in CCPR1L
	CCP1CON &= 0xCF;                	// Make bit4 and 5 zero
	CCP1CON |= (0x30&(dutycyc<<4));   // Assign Last 2 LSBs to CCP1CON
if(s1==1){dutycyc=172; }
if(s2==1){dutycyc=342; }
if(s3==1){dutycyc=512; }
if(s4==1){dutycyc=686; }
if(s5==1){dutycyc=858; }
if(s6==1){dutycyc=1020; }
dutycyc=dutycyc;

}
}
