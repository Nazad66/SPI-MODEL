/* SPI Registers addresses */     
#define SPI_CR1 (* ((unsigned volatile long*)0x40013000))
#define SPI_CR2 (* ((unsigned volatile long*)0x40013004))
#define SPI_SR  (* ((unsigned volatile long*)0x40013008))
#define SPI_DR  (* ((unsigned volatile long*)0x4001300C))

                                            /* MACROS */

 //Data frame selection 
#define BITMODE8      0
#define BITMODE16     1

//Clock Phase and Polarity modes
#define SPI_MODE0     0
#define SPI_MODE1     1
#define SPI_MODE2     2
#define SPI_MODE3     3

//Baud Rate selection
#define FPCLK2        0
#define FPCLK4        1
#define FPCLK8        2
#define FPCLK16       3
#define FPCLK32       4
#define FPCLK64       5
#define FPCLK128      6
#define FPCLK256      7

//Transfer order 
#define LSBFIRST      1
#define MSBFIRST      0


                                   /* Functions Prototypes */

void begin                      (void);
void setDataMode                (int mode, int clockMode);
void setClockDivider            (int freq_divider);
void setBitOrder                (int byteOrder);
unsigned char transfer          (unsigned char TxData);
void end                        (void);
void beginTransaction           (int byteOrder,int dataMode,int baudRate,int clockMode);
void endTransaction             (void);

