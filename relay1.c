/* 
 * File:   relay1.c
 * Author: Ankur Mishra
 *
 * Created on July 6, 2018, 4:27 PM
 */

#include <xc.h>
#define _XTAL_FREQ = 8000000
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
