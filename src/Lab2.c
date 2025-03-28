#include <stdint.h> // standard integer types gives type definition for fixed width intgers example: uint32_t (this declares an unsigned 32 bit integer variable )
#include <stdio.h>  // standard input/output provides functions for performing input out operations (need so we can use sprintf)
#include "sleep.h" // provides functions for pausing the execution of the program for a specified duration

#define SEG_CTL *(uint32_t *)0x43c10000 //Seven Segment configuration register only use the two LSB, the LSB is Enable or disable set to 1 for enable set 0 for disable. secound LSB is for mode set to zero for defualt mode
#define SEG_DATA *(uint32_t *)0x43c10004 //Seven Segment Data register lower 4 bits are BCD/hex data the next 3 bits are direct segment drive data(mode1), and bit 7 is the decimal point
#define Button_DATA *(uint32_t*)0x41200000 // buttons are lower 4 bits we are gonna use button0, button1, and button2



int main(void) 
{

    //Enable the display (bit 0 = 1 to enable, bit 1 = 0 for default mode)
    SEG_CTL = 0x01;


    // Tempoary Variable for Seven Segment Display Controls 1s place 
    uint8_t tempVar0 = 0x00;
    
    //Tempoary Variable for Seven Segment Display Controls 10s place 
    uint8_t tempVar1 = 0x00;
    
    //Tempoary Variable for Seven Segment Display Controls 100s place
    uint8_t tempVar2 = 0x00;
   
    //Tempoary Variable for Seven Segment Display Controls 1000s place 
    uint8_t tempVar3 = 0x00;
    
    // variable used to pause the count
    uint8_t pause = 0;
    

    
    
    
    //SEG_DATA = (tempVar3 << 24) | (tempVar2 << 16) | (tempVar1 << 8) | tempVar0; (don't know what this has to be in while loop) I started editing here
    
    // This while loop makes it so nothing happens if button is not pressed
    while((Button_DATA & 0x02) == 0)
        {
            ;  
        }
    
    // Main loop controls the functions of the counter starting, pausing the counter, and starting it again if paused
    while(1)
        {
            
            if(pause == 1 && (Button_DATA & 0x04) == 0x04)
                {
                    tempVar0 = 0;
                    tempVar1 = 0;
                    tempVar2 = 0;
                    tempVar3 = 0;

                    SEG_DATA = (tempVar3 << 24) | (tempVar2 << 16) | (tempVar1 << 8) |(tempVar0) | 0x80808080;                    
                }
            
            
            //makes the variable "pause" = 1 if button 0 is pressed 
            if((Button_DATA & 0x01) == 0x01 )
                {
                   pause = 1;
                }

            //pause is intialized to 0 at start of code this if statment is just there to contiues the count by pressing button 1 if we paused it by pressing button 0
            if((Button_DATA & 0x02) == 0x02)
                {
                    pause = 0;
                }
            
            //pauses the count using loop control statement contiue, conntinue skips remaing code and starts next iteration of the loop
            if(pause == 1)
                {
                    continue;
                }
                
                
                
                
            
            SEG_DATA = (tempVar3 << 24) | (tempVar2 << 16) | (tempVar1 << 8) |(tempVar0) | 0x80808080; // SEG_DATA =  '0'   0000 0000   0000 0000    0000 0000 | '0'   0000 0000   0000 0000 | '0'   0000 0000 | 0000 000'0' 


            // increments the 1s place
            tempVar0++;
            sleep(1);
            
            
            // once 1s place greater then 9 it sets it back to 0 increments 10s place once and goes back to incrementing once place 
            if(tempVar0 > 0x09)
                {
                    tempVar0 = 0x00;
                    tempVar1++;
                }
            
            // once 10s place greater then 9 it sets it back to 0 increments 100s place once and goes back to incrementing once place
            if(tempVar1 > 0x09)
                {
                    tempVar1 = 0x00;
                    tempVar2++;
                }
            
            // once 100s place greater then 9 it sets it back to 0 increments 1000s place once and goes back to incrementing once place
            if(tempVar2 > 0x09)
                {
                    tempVar2 = 0x00;
                    tempVar3++;
                }
            // restarts count
            if(tempVar3 > 0x09)
                {
                    tempVar3 = 0x00;
                }

        }


    return 0;

} 