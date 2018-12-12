/******************************************************************************************
*	fram with Arduino header; the FRAM chip is MB85RS256A
*	Original Code: K Tyler (SpiRAM)
*	Code Modified: Prawar Poudel (pp0030@uah.edu)

*	Date: 07/24/2018
******************************************************************************************/

#include <fram.h>

// following is the constructor of hte class;
// .. the slave is initialized with the pin number argument
fram::fram(uint8_t ss_Pin,uint8_t newHoldPin)
{
	/*
		follwing steps are performed
		-> set the value in class
		-> write high to the pin
		-> initialize it as output
		-> begin SPI engine
	*/
	#if HEADER_DEBUG
		Serial.begin(115200);
		Serial.println("Object Creation..");
	#endif
	csPin = ss_Pin;   
	holdPin = newHoldPin;                 
	digitalWrite(csPin,HIGH);          
	pinMode(csPin,OUTPUT);             
	SPI.begin();                       
	#if HEADER_DEBUG
		Serial.println(".. obj creation completed");
	#endif

}

// following function if needed to change the device
// .. may be needed if multiple devices interfaced
uint8_t fram::changeDevice  (uint8_t ss_Pin,uint8_t newHoldPin)
{
	/*
		to change the pin, following steps are performed
		-> change the pin in object to the new pin number
		-> set the CS (slave select to high to deselect it now)
		-> set the direction as output
	*/
	uint8_t temp = csPin;               
	csPin = ss_Pin;   
	holdPin = newHoldPin;                  
	digitalWrite(csPin,HIGH);           
	pinMode(csPin,OUTPUT);              

	#if HEADER_DEBUG
		Serial.print("Device changed to ");
		Serial.println(ss_Pin);
	#endif

	return temp;                        
}

// .. read just one byte
uint8_t fram::readByte(uint16_t address) 
{
	/*
		following steps are performed here:
		-> call the function to readBuffer, with length argument 1
		-> return the read value
	*/
	uint8_t dataByte;
	readBuffer(address, (char*) &dataByte, 1);

	#if HEADER_DEBUG
		Serial.print("Data byte read from memory address ");
		Serial.print(address);
		Serial.print(" : ");
		Serial.println(dataByte);
	#endif

	return dataByte;
}

// .. write just one byte
void fram::writeByte(uint16_t address, uint8_t dataByte) 
{
	/*
		following steps are performed here:
		-> call the function to writeBuffer, with length argument 1
	*/
	writeBuffer(address, (char*) &dataByte, 1);

	#if HEADER_DEBUG
		Serial.print("Data byte written to memory address ");
		Serial.print(address);
		Serial.print(" : ");
		Serial.println(dataByte);
	#endif
}

void fram::readBuffer(uint16_t address, char *buffer, uint16_t length) 
{
	/*
		The steps to perform read are (please refer to datasheet)
		-> Take CS to low 
		-> Send 1 Byte Command Value
		-> Send 2 Bytes Start Address Value
		-> Send 0x00 to read the value
		-> Take Cs to high to end read operation
	*/
	digitalWrite(csPin, LOW);

	#if HEADER_DEBUG
		Serial.print("Buffer reading initiated from address : ");
		Serial.println(address);
	#endif

	setAddressMode(address, READ);
	for (uint16_t i = 0; i < length; i++) buffer[i] = SPI.transfer(0x00);
	digitalWrite(csPin, HIGH);

	#if HEADER_DEBUG
		Serial.print("Buffer reading completed of length: ");
		Serial.println(length);
	#endif
}

void fram::writeBuffer(uint16_t address, char *buffer, uint16_t length)
{
	/*
		The steps to perform write are (please refer to datasheet)
		-> Take CS to low 
		-> Send 1 Byte Command Value
		-> Send 2 Bytes Start Address Value
		-> Send data value to write
		-> Take Cs to high to end write operation
	*/
	writeEnable();

	#if HEADER_DEBUG
		Serial.print("Buffer writing initiated from address : ");
		Serial.println(address);
	#endif

	digitalWrite(csPin, LOW);
	setAddressMode(address, WRITE);
	for (uint16_t i = 0; i < length; i++) SPI.transfer(buffer[i]);
	digitalWrite(csPin, HIGH);

	#if HEADER_DEBUG
		Serial.print("Buffer writing completed of length: ");
		Serial.println(length);
	#endif

	writeDisable();
}

void fram::fillBytes(uint16_t address, uint8_t value, uint16_t length) {
	/*
		operation similar to write operation but same value sent to all the addresses
	*/
	writeEnable();

	#if HEADER_DEBUG
		Serial.print("Buffer filling initiated from address : ");
		Serial.println(address);
	#endif

	digitalWrite(csPin, LOW);
	setAddressMode(address, WRITE);
	for (uint16_t i = 0; i < length; i++) SPI.transfer(value);
	digitalWrite(csPin, HIGH);

	#if HEADER_DEBUG
		Serial.print("Buffer filling completed of length: ");
		Serial.println(length);
	#endif

	writeDisable();
}

void fram::setAddressMode(uint16_t address, uint8_t command) 
{
	/*
		following steps are performed to set the mode and send the adress to chip
		-> send 1 Byte to command
		-> send 2 Bytes address (MSB first)
		modification can be done to send 16bit address at once
	*/

	#if HEADER_DEBUG
		Serial.print("initiating command : ");
		Serial.println(command);
	#endif

	SPI.transfer(command);
	// SPI.transfer((uint8_t)(address >> 8));
	// SPI.transfer((uint8_t)(address));
	SPI.transfer(&address,2);
}

void fram::writeEnable()
{
	digitalWrite(csPin, LOW);
	SPI.transfer(WRITE_EN);	
	digitalWrite(csPin, HIGH);
}

void fram::writeDisable()
{
	digitalWrite(csPin, LOW);
	SPI.transfer(WRITE_DN);	
	digitalWrite(csPin, HIGH);
}

// END OF FILE