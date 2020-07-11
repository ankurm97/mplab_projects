 // CONFIG
#pragma config FOSC = HS       // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
// End of configuration

#include <xc.h>
#define _XTAL_FREQ 8000000
#define Baud_rate 9600

//***Initializing UART module for PIC16F877A***//
void Initialize_UART(void)
{
    //****Setting I/O pins for UART****//
    TRISC6 = 0; // TX Pin set as output
    TRISC7 = 1; // RX Pin set as input
    //________I/O pins set __________//
    
    /**Initialize SPBRG register for required 
    baud rate and set BRGH for fast baud_rate**/
    //SPBRG = ((_XTAL_FREQ/16)/Baud_rate) - 1;
    SPBRG = 51;
    BRGH  = 1;  // for high baud_rate
    //_________End of baud_rate setting_________//
    
    //****Enable Asynchronous serial port*******//
    SYNC  = 0;    // Asynchronous
    SPEN  = 1;    // Enable serial port pins
    //_____Asynchronous serial port enabled_______//

    //**Lets prepare for transmission & reception**//
    TXEN  = 1;    // enable transmission
    CREN  = 1;    // enable reception
    //__UART module up and ready for transmission and reception__//
    
    //**Select 8-bit mode**//  
    TX9   = 0;    // 8-bit reception selected
    RX9   = 0;    // 8-bit reception mode selected
    //__8-bit mode selected__//     
}
//________UART module Initialized__________//

 

//**Function to send one byte of date to UART**//
void UART_send_char(char bt)  
{
    while(!TXIF);  // hold the program till TX buffer is free
    TXREG = bt; //Load the transmitter buffer with the received value
}
//_____________End of function________________//

 

//**Function to get one byte of date from UART**//
char UART_get_char()   
{
    if(OERR) // check for Error 
    {
        CREN = 0; //If error -> Reset 
        CREN = 1; //If error -> Reset 
    }
    
    while(!RCIF);  // hold the program till RX buffer is free
    
    return RCREG; //receive the value and send it to main function
}
//_____________End of function________________//

 

//**Function to convert string to byte**//
void UART_send_string(char* st_pt)
{
    while(*st_pt) //if there is a char
        UART_send_char(*st_pt++); //process it as a byte data
}
//___________End of function______________//

    

// **********START of Main Function**************//
void main(void)
{
    int get_value;
    
    TRISB = 0x00; //Initialize PortB as output
    Initialize_UART();    //Initialize UART module                    
    
    UART_send_string("UART Module Initialized and active");    // Introductory Text
    
    while(1) //Infinite loop
    {
      get_value = UART_get_char(); 
        
        if (get_value == '1') //If the user sends "1"
        {
            RB3=1; //Turn on LED
            UART_send_string("RED LED -> ON"); //Send notification to the computer 
            UART_send_char(10);//ASCII value 10 is used for carriage return (to print in new line)
        }
        
        if (get_value == '0') //If the user sends "0"
        {
           RB3=0; //Turn off LED
           UART_send_string("RED -> OFF"); //Send notification to the computer      
           UART_send_char(10);//ASCII value 10 is used for carriage return (to print in new line)
        }
       
    }
}