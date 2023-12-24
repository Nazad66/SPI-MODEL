/* SPI Registers addresses */     
#define SPI_CR1 (* ((unsigned volatile long*)0x40013000))
#define SPI_CR2 (* ((unsigned volatile long*)0x40013004))
#define SPI_SR  (* ((unsigned volatile long*)0x40013008))
#define SPI_DR  (* ((unsigned volatile long*)0x4001300C))

                                            /* MACROS */

 //Data frame selection 
#define bitMode8      0
#define bitMode16     1

//Clock Phase and Polarity modes
#define SPI_MODE0     0
#define SPI_MODE1     1
#define SPI_MODE2     2
#define SPI_MODE3     3

//Baud Rate selection
#define fPCLK2        0
#define fPCLK4        1
#define fPCLK8        2
#define fPCLK16       3
#define fPCLK32       4
#define fPCLK64       5
#define fPCLK128      6
#define fPCLK256      7

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

