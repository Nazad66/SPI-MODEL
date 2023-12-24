/* MCAL */
#include "SPI.h"
 
 unsigned char RxData ;
 
void begin ()
{
     //GPIO pins configuration
       RCC_AHB1ENR |= (1<<0);                 //IO port A clock enable
     // PA4(SPI1_NSS), PA5(SPI1_SCK), PA6(SPI1_MISO), PA7(SPI1_MOSI)
       GPIOA_MODER |= (2<<8) | (2<<10) | (2<<12) | (2<<14)  ;          //(PA4,PA5,PA6,PA7) alternate mode 
       GPIOA_AFRL  |= (5<<16) | (5<<20) | (5<<24) | (5<<28) ;         // SPI1 alternate functions
      
      //SPI1 clock enable
       RCC_APB2ENR |= (1<<12);
      
      //Software slave management enable
       SPI_CR1 |=  (1<<9) ;           //SSM=1
       SPI_CR1 |=  (1<<8) ;          // SSI=1 (to operate in master mode)
      
     //Full duplex mode
       SPI_CR1 &= ~( (1<<10) | (1<<15) ) ;      //RxONLY=0 , BIDIMODE=0
      
     //Master configuration
       SPI_CR1 |= (1<<2);
      
     //SPI enable
       SPI_CR1 |= (1<<6);

}

void setDataMode ( int mode, int clockMode)
{
     //Data frame format selection
      if(mode == BITMODE8)
        {
           SPI_CR1  &= ~(1<<11);       //8-bit data frame format
        }
      if(mode == BITMODE16)
        {
           SPI_CR1  |=  (1<<11);       //16-bit data frame format
        }

      //Select clock phase and polarity
        switch(clockMode)
        {
             case SPI_MODE0:
               SPI_CR1  &= ~(1<<0);      //First clock transition is the first data capture edge
               SPI_CR1  &= ~(1<<1);      //CK to 0 when idle
               break;

             case SPI_MODE1:
               SPI_CR1  |=  (1<<0);      //Second clock transition is the first data capture edge
               SPI_CR1  &= ~(1<<1);      //CK to 0 when idle
               break;

             case SPI_MODE2:
               SPI_CR1  &= ~(1<<0);      //First clock transition is the first data capture edge
               SPI_CR1  |=  (1<<1);      //CK to 1 when idle
               break;

             case SPI_MODE3:
               SPI_CR1  |= (1<<0);      //Second clock transition is the first data capture edge
               SPI_CR1  |= (1<<1);      //CK to 1 when idle
               break;

        }
}

void setClockDivider(int freq_divider)
{
      //Baud rate Control
      switch(freq_divider)
        {
             case FPCLK2:
               SPI_CR1  &= ~(1<<3);
               SPI_CR1  &= ~(1<<4);
               SPI_CR1  &= ~(1<<5);
               break;

             case FPCLK4:
               SPI_CR1  |=  (1<<3);
               SPI_CR1  &= ~(1<<4);
               SPI_CR1  &= ~(1<<5);
               break;

             case FPCLK8:
               SPI_CR1  &= ~(1<<3);
               SPI_CR1  |=  (1<<4);
               SPI_CR1  &= ~(1<<5);
               break;

             case FPCLK16:
               SPI_CR1  |=  (1<<3);
               SPI_CR1  |=  (1<<4);
               SPI_CR1  &= ~(1<<5);
               break;

             case FPCLK32:
               SPI_CR1  &= ~(1<<3);
               SPI_CR1  &= ~(1<<4);
               SPI_CR1  |=  (1<<5);
               break;

             case FPCLK64:
               SPI_CR1  |=  (1<<3);
               SPI_CR1  &= ~(1<<4);
               SPI_CR1  |=  (1<<5);
               break;

             case FPCLK128:
               SPI_CR1  &= ~(1<<3);
               SPI_CR1  |=  (1<<4);
               SPI_CR1  |=  (1<<5);
               break;

             case FPCLK256:
               SPI_CR1  |= (1<<3);
               SPI_CR1  |= (1<<4);
               SPI_CR1  |= (1<<5);
               break;
        }
}

void setBitOrder (int byteOrder)
{
       switch(byteOrder)
       {
           case LSBFIRST :
             SPI_CR1  |= (1<<7);      //LSB transmitted first
             break;

           case MSBFIRST :
             SPI_CR1  &= ~(1<<7);    //MSB transmitted first
             break;
       }
}

unsigned char transfer (unsigned char TxData)
{

             unsigned char RxData = 0;
         
     //Wait for TXE=1 to indicate that transmit buffer is empty
        while( !((SPI_SR) & (1<<1)) );

      //Write data and dummy byte to data register 
          SPI_DR = TxData;
          
     /* Wait for  BSY=0  SPI is not busy  *transmission of the last data is complete*
                  RXNE=1 receive buffer is not empty  */
        while( !((SPI_SR) & (1<<0))  ||  SPI_SR & (1<<7) );

          RxData = SPI_DR ;
          return RxData ;
}

void end ()
{
       // Wait until  BSY=0
      while( SPI_SR &(1<<7) );

       //SPI disable
      SPI_CR1  &= ~(1<<6);
}


 //This function is a shortcut for calling 3 functions
void beginTransaction (int byteOrder, int dataMode, int baudRate, int clockMode)
{
      switch(byteOrder)
       {
           case LSBFIRST :
             SPI_CR1  |= (1<<7);      //LSB transmitted first
             break;

           case MSBFIRST :
             SPI_CR1  &= ~(1<<7);    //MSB transmitted first
             break;
       }

        //Baud rate Control
      switch(baudRate)
        {
             case FPCLK2:
               SPI_CR1  &= ~(1<<3);
               SPI_CR1  &= ~(1<<4);
               SPI_CR1  &= ~(1<<5);
               break;

             case FPCLK4:
               SPI_CR1  |=  (1<<3);
               SPI_CR1  &= ~(1<<4);
               SPI_CR1  &= ~(1<<5);
               break;

             case FPCLK8:
               SPI_CR1  &= ~(1<<3);
               SPI_CR1  |=  (1<<4);
               SPI_CR1  &= ~(1<<5);
               break;

             case FPCLK16:
               SPI_CR1  |=  (1<<3);
               SPI_CR1  |=  (1<<4);
               SPI_CR1  &= ~(1<<5);
               break;

             case FPCLK32:
               SPI_CR1  &= ~(1<<3);
               SPI_CR1  &= ~(1<<4);
               SPI_CR1  |=  (1<<5);
               break;

             case FPCLK64:
               SPI_CR1  |=  (1<<3);
               SPI_CR1  &= ~(1<<4);
               SPI_CR1  |=  (1<<5);
               break;

             case FPCLK128:
               SPI_CR1  &= ~(1<<3);
               SPI_CR1  |=  (1<<4);
               SPI_CR1  |=  (1<<5);
               break;

             case FPCLK256:
               SPI_CR1  |= (1<<3);
               SPI_CR1  |= (1<<4);
               SPI_CR1  |= (1<<5);
               break;
        }

           //Data frame format selection
         if(dataMode == BITMODE8)
        {
             SPI_CR1  &= ~(1<<11);       //8-bit data frame format
        }
        if(dataMode == BITMODE16)
        {
             SPI_CR1  |=  (1<<11);       //16-bit data frame format
        }


         //Select clock phase and polarity
        switch(clockMode)
        {
             case SPI_MODE0:
               SPI_CR1  &= ~(1<<0);      //First clock transition is the first data capture edge
               SPI_CR1  &= ~(1<<1);      //CK to 0 when idle
               break;

             case SPI_MODE1:
               SPI_CR1  |= (1<<0);      //Second clock transition is the first data capture edge
               SPI_CR1  &= ~(1<<1);      //CK to 0 when idle
               break;

             case SPI_MODE2:
               SPI_CR1  &= ~(1<<0);      //First clock transition is the first data capture edge
               SPI_CR1  |= (1<<1);      //CK to 1 when idle
               break;

             case SPI_MODE3:
               SPI_CR1  |= (1<<0);      //Second clock transition is the first data capture edge
               SPI_CR1  |= (1<<1);      //CK to 1 when idle
               break;

        }
}

void endTransaction ()
{
        // Wait until (RXNE=1 , TXE=1 ,BSY=0)
       while( !((SPI_SR) & (1<<0)) || !((SPI_SR) & (1<<1)) || SPI_SR &(1<<7) ) ;

       //SPI disable
      SPI_CR1  &= ~(1<<6);
}

