# Memory  SPI Chips
  
## Description  
This repository is created to contain code that interfaces the SPI chips to Arduino Uno.  
Basically, the chips are interfaced through SPI communication protocol, so any memory chip that uses the same configuration and command codes can be interfaced.
  
  
## File Structure  
*spiMemoryChips*  
	&nbsp; libs  
	&nbsp;&nbsp;&nbsp; fram  
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; fram.cpp  
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; fram.h  
	&nbsp;&nbsp;&nbsp; mram  
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; mram.cpp  
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; mram.h  
	&nbsp; source  
	&nbsp;&nbsp;&nbsp; framInterface  
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; framInterface.ino  
	&nbsp;&nbsp;&nbsp; mramInterface  
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; mramInterface.ino  

  
## Device Supported  
It should support all the devices that can be interfaced using SPI. Current tested  fine for:  
MR25H256A (https://www.mikroe.com/mram-click)  
MB85RS256A (https://www.mikroe.com/fram-click)