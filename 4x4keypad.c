/* 
 * File:   4x4keypad.c
 * Author: Ankur Mishra
 *
 * Created on July 7, 2018, 2:20 PM
 */
#define _XTAL_FREQ 8000000
#include <xc.h>
#pragma config FOSC = HS   
#pragma config WDTE = OFF  
#pragma config PWRTE = OFF 
#pragma config BOREN = ON  
#pragma config LVP = OFF  
#pragma config CPD = OFF   
#pragma config WRT = OFF   
#pragma config CP = OFF  
#define FOSC 10000
#define BAUD_RATE 9.6
//9600 Baudrate
#define BAUD_VAL (char)(FOSC/ (16 * BAUD_RATE )) - 1;
//Calculation For 9600 Baudrate @10Mhz void SerialInit(void);
//Serial port Initialization Function void ScanCol(void);
//Column Scan Function void ScanRow(void);
//Row Scan Function void DelayMs(unsigned int);
unsigned char KeyArray[4][4]= { '1','2','3','4', '5','6','7','8', '9','A','B','C', 'D','E','F','0'};
//Keypad value Initialization Function unsigned char Count[4][4]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int Col=0,Row=0,count=0,i,j;
void main()
{
__delay_ms(50);
SerialInit();
nRBPU=0;
//Enable PORTB Pullup values while(1)
{
TRISB=0x0f;
// Enable the 4 LSB as I/P & 4 MSB as O/P PORTB=0;
while(PORTB==0x0f);
// Get the ROW value ScanRow();
TRISB=0xf0;
// Enable the 4 LSB as O/P & 4 MSB as I/P PORTB=0;
while(PORTB==0xf0);
// Get the Column value ScanCol();
__delay_ms(150); 
count[Row][Col]++;
// Count the Pressed key printf("[%c] Pressed:[%d] Times\n\r", KeyArray[Row][Col],Count[Row][Col]);
__delay_ms(200);
}
}
void ScanRow()
{
switch(PORTB)
{
case 0x07: Row=3;
break;
case 0x0b: Row=2;
break;
case 0x0d: Row=1;
break;
case 0x0e: Row=0;
break;
}
}
void ScanCol()
{
switch(PORTB)
{
case 0x70: Col=3;
break;
case 0xb0: Col=2;
break;
case 0xd0: Col=1;
break;
case 0xe0: Col=0;
break;
}
}
void SerialInit()
{
TRISC=0xc0;
TXSTA=0x24;
SPBRG=BAUD_VAL;
RCSTA=0x90;
printf("Press Anyone Key:\n\r");
}
void putch(unsigned char character)
{
while(!TXIF);
// Wait for the TXREG register to be empty TXREG=character;
// Display the Character
}