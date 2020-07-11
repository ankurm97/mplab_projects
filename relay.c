/* 
 * File:   relay.c
 * Author: Ankur Mishra
 *
 * Created on July 5, 2018, 12:44 PM
 */

#include <xc.h>
#define _XTAL_FREQ = 4000000
#pragma config FOSC = HS 
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON 
#pragma config LVP = OFF 
#pragma config CPD = OFF 
#pragma config WRT = OFF 
#pragma config CP = OFF 
int main() 
{
    TRISA5=0;
    TRISB4=0;
    RB4=1;
    TRISA4=1;
    RA5=0;
    if(RA4==0)
    {
        RA5=0;
    }
    else
    {
        RA5=1;
    }    
    return 0;
}

