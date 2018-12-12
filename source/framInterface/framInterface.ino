/****************************************************************************
Arduino Interface Program: This program interfaces FRAM chip available at 
https://download.mikroe.com/documents/datasheets/MB85RS256A.pdf with Arduino.
It is designed to be used with FRAM click from mikroElectronika.

Developed by: Prawar Poudel (pp0030@uah.edu)
Date: 7/24/3018
****************************************************************************/
#include <fram.h>

#define DEBUG_PRINT_STATEMENTS 0

//create an object here so that it has global scope throughout this file
//  -> CS signal is Android pin 9
fram myfram(9,3);

void setup() 
{
  Serial.begin(115200);     //initiate serial communication @ 115200 bps
  #if DEBUG_PRINT_STATEMENTS
    Serial.println("Serial Communication Initiated");
  #endif

//  The following statement just writes one byte and reads the same byte and prints in serial monitor
  Serial.println("Writing one byte to memory...");
  myfram.writeByte(0x000,0x48);
  uint8_t myReadVal = myfram.readByte(0x000);
  Serial.print("The value read is :");
  Serial.println(myReadVal,HEX);
  Serial.println(" ... writing one byte to memory completed");

// The following statement writes a buffer stored, and reads into another buffer from fram memory
  Serial.println();
  Serial.println("Writing buffer to memory...");  
  char myBuffer[] = "Mission Impossible: Ghost Protocol";
  myfram.writeBuffer(0x000,myBuffer,35);
  char myReadBuffer[50]; 
  myfram.readBuffer(0x000,myReadBuffer,35);
  Serial.print("The buffer read is :");
  Serial.println(myReadBuffer);
  Serial.println(" ... writing buffer to memory completed");

// The following fills the 10 memory bytes starting at address 0x7ffa and prints them (the maximum address being 0x7fff, it should roll over)
  Serial.println();
  Serial.println("Filing byte to memory...");  
  char myByte = 0x37;
  myfram.fillBytes(0x7ffa,myByte,10);
  char myReadByte[10]; 
  myfram.readBuffer(0x7ffa,myReadByte,10);
  Serial.print("The buffer read is :");
  for(char iter= 0;iter<10;iter++) Serial.print(myReadByte[iter],HEX);
  Serial.println();
  Serial.println(" ... filling byte to memory completed");  

}

void loop() 
{
  // put your main code here, to run repeatedly:

}
