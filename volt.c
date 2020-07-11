/* 
 * File:   volt.c
 * Author: Ankur Mishra
 *
 * Created on July 7, 2018, 12:30 PM
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
const unsigned char DispArray[]={
          0x3F,  //0
          0x6,  //1
          0x5B,  //2
          0x4F,    //3
          0x66, //4
          0x6D, //5
          0x7D, //6
          0x7, //7
          0x7F, //8
          0x6F};    //9
void set7SegToInt(int x){
    PORTB=DispArray[x];
    PORTD=0x01;
}
void ADC_Init()
{
  ADCON0 = 0x81;               //Turn ON ADC and Clock Selection
  ADCON1 = 0x80;               //All pins as Analog Input and setting Reference Voltages
}
unsigned int ADC_Read(unsigned char channel)
{
  if(channel > 7)              //Channel range is 0 ~ 7
    return 0;
  ADCON0 &= 0xC5;              //Clearing channel selection bits
  ADCON0 |= channel<<3;        //Setting channel selection bits
  __delay_ms(2);               //Acquisition time to charge hold capacitor
  GO_nDONE = 1;                //Initializes A/D conversion
  while(GO_nDONE);             //Waiting for conversion to complete
  return ((ADRESH<<8)+ADRESL); //Return result
}
void main()
{
  unsigned int a;
  TRISA = 0xFF;                 //Analog pins as Input
  ADC_Init();                   //Initialize ADC
  ANSELH=0X00;
  TRISB=0X00;   //PORTB is output   //connected to anode
  TRISD=0x00;   // PORTD is output  //connected to cathode
  do
  {
    a = ADC_Read(0);            //Read Analog Channel 0
    set7SegToInt(a/100);
    __delay_ms(100);            //Delay
  }while(1);                    //Infinite Loop
}