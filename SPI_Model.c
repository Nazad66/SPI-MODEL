/* MCAL */
#include "SPI.h"
 
 unsigned char Tx ;
 
void main() {
               
               begin();
               beginTransaction(LSBFIRST , FPCLK16 , BITMODE8 , SPI_MODE0);
     
      while(1)
     {  
            
             Tx = 1 ;
            transfer (Tx);
            Delay_ms(3000);       
           
             Tx = 0 ;
            transfer (Tx);
            Delay_ms(3000);   
               
     }

}
