/* 
 * File:   newmain1.c
 * Author: Ankur Mishra
 *
 * Created on July 4, 2018, 3:54 PM
 */
#define _XTAL_FREQ 8000000
#include <xc.h>
int main()
{
    TRISB=0X00;
    PORTB=0X00;       
    while(1)
    {
    RB3=1; 
    __delay_ms(500); 
    RB3=0;
    __delay_ms(500);
     
    }
return(0);
}