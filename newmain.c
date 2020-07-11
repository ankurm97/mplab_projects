/* 
 * File:   newmain.c
 * Author: Ankur Mishra
 *
 * Created on July 6, 2018, 4:07 PM
 */
#define _XTAL_FREQ 8000000
#define TMR2PRESCALE 4
#include <xc.h>
#pragma config FOSC = HS   
#pragma config WDTE = OFF  
#pragma config PWRTE = OFF 
#pragma config BOREN = ON  
#pragma config LVP = OFF  
#pragma config CPD = OFF   
#pragma config WRT = OFF   
#pragma config CP = OFF  
long freq;
int PWM_Max_Duty()
{
  return(_XTAL_FREQ/(freq*TMR2PRESCALE));
}
PWM1_Init(long fre)
{
  PR2 = (_XTAL_FREQ/(fre*4*TMR2PRESCALE)) - 1;
  freq = fre;
}
PWM2_Init(long fre)
{
  PR2 = (_XTAL_FREQ/(fre*4*TMR2PRESCALE)) - 1;
  freq = fre;
}
PWM1_Duty(unsigned int duty)
{
  if(duty<1024)
  {
    duty = ((float)duty/1023)*PWM_Max_Duty();
    CCP1X = duty & 2;
    CCP1Y = duty & 1;
    CCPR1L = duty>>2;
  }
}
PWM2_Duty(unsigned int duty)
{
  if(duty<1024)
  {
    duty = ((float)duty/1023)*PWM_Max_Duty();
    CCP2X = duty & 2;
    CCP2Y = duty & 1;
    CCPR2L = duty>>2;
  }
}
PWM1_Start()
{
  CCP1M3 = 1;
  CCP1M2 = 1;
  #if TMR2PRESCALAR == 1
    T2CKPS0 = 0;
    T2CKPS1 = 0;
  #elif TMR2PRESCALAR == 4
    T2CKPS0 = 1;
    T2CKPS1 = 0;
  #elif TMR2PRESCALAR == 16
    T2CKPS0 = 1;
    T2CKPS1 = 1;
  #endif
  TMR2ON = 1;
  TRISC2 = 0;
}
PWM1_Stop()
{
  CCP1M3 = 0;
  CCP1M2 = 0;
}
PWM2_Start()
{
  CCP2M3 = 1;
  CCP2M2 = 1;
  #if TMR2PRESCALE == 1
    T2CKPS0 = 0;
    T2CKPS1 = 0;
  #elif TMR2PRESCALE == 4
    T2CKPS0 = 1;
    T2CKPS1 = 0;
  #elif TMR2PRESCALE == 16
    T2CKPS0 = 1;
    T2CKPS1 = 1;
  #endif
    TMR2ON = 1;
    TRISC1 = 0;
}
PWM2_Stop()
{
  CCP2M3 = 0;
  CCP2M2 = 0;
}
void main()
{
  unsigned int i=0,j=0;
  PWM1_Init(5000);
  PWM2_Init(5000);
  TRISD = 0xFF;
  TRISB = 0;
  PWM1_Duty(0);
  PWM2_Duty(0);
  PWM1_Start();
  PWM2_Start();
  do
  {
    if(RD0 == 0 && i<1000)
      i=i+10;
    if(RD1 == 0 && i>0)
      i=i-10;
    if(RD2 == 0 && j<1000)
      j=j+10;
    if(RD3 == 0 && j>0)
      j=j-10;
    PWM1_Duty(i);
    PWM2_Duty(j);

    __delay_ms(50);
  }while(1);
}
