/******************************************************************************************
*	MRAM with Arduino header; the MRAM chip is MR25H256A
*	Original Code: K Tyler (SpiRAM)
*	Code Modified: Prawar Poudel (pp0030@uah.edu)

*	Date: 07/24/2018
******************************************************************************************/

#ifndef mram_h
#define mram_h

// support for old IDE's
#if ARDUINO < 100
  #include <WProgram.h>
#else
  #include <Arduino.h>
#endif

#include <SPI.h>

#define HEADER_DEBUG 1

// Command Codes; Please refer to the datasheet at
// https://download.mikroe.com/documents/datasheets/EST02896_MR25H256A_Datasheet_Rev1.0%20100116-1036068.pdf
#define RDSR  0x05
#define WRSR  0x01
#define WRITE 0x02
#define READ  0x03
#define WRITE_EN 0x06
#define WRITE_DN 0x04

class mram {
  public:
    // Initialize and specify the SS pin
    mram (uint8_t ss_Pin, uint8_t newHoldPin);
    
    // following function if needed to change the device
    // .. may be needed if multiple devices interfaced
    uint8_t changeDevice  (uint8_t ss_Pin,uint8_t newHoldPin);
    
    // following function reads a single character (uint8_t)
    uint8_t readByte   (uint16_t address);
    
    // following function write a single character (uint8_t)
    void writeByte  (uint16_t address, uint8_t dataToWrite);
    
    // read "length" number of character into "buffer" from memory starting at "address"
    void readBuffer (uint16_t address, char *buffer, uint16_t length);
    
    // write "length" number of character from "buffer" to memory starting at "address"
    void writeBuffer(uint16_t address, char *buffer, uint16_t length);
    
    //fill "length" bytes in memory starting at "address" all with "value"
    void fillBytes  (uint16_t address, uint8_t value, uint16_t length);

    uint8_t readByteEffecient(uint16_t address);

    void writeByteEffecient(uint16_t address,uint8_t value);
    
  private:
  	//CS Pin of the SPI device connected right now
    uint8_t csPin,holdPin;
    //folllowing sets the command to "mode" and sends "address" as the concerned address
    void setAddressMode(uint16_t address, uint8_t mode);

    //enable write operation to MRAM memory or Status Register
    void writeEnable();

    //disable write operation to MRAM memory or Status Register: protection mechanism
    void writeDisable();
};

#endif
// END OF FILE