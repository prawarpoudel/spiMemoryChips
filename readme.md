# Memory  SPI Chips
  
## Description  
This repository contains code that interfaces SPI memory chips, namely [FRAM](https://www.mikroe.com/fram-click) and [MRAM](https://www.mikroe.com/mram-click). Both of these chips can be interfaced using the same interfacing program as they have similar SPI controller in them. They differ however in terms of their phyiscs as they are ferro-electric and magento-resistive memory respectively. These two chips are, respectively, composed of [FRAM chip](https://download.mikroe.com/documents/datasheets/MB85RS256A.pdf) manufactured by Fujitsu and [MRAM chip](https://download.mikroe.com/documents/datasheets/EST02896_MR25H256A_Datasheet_Rev1.0%20100116-1036068.pdf) manufactured by Everspin.  
  
The file hare include the header and sample source file. One key difference between that might exists between other SPI devices and these chips in particular is that the HOlD signal has to be HIGH all the time for any memory operation to work. It is written in the data sheet of the chips that the HOLD signal LOW means the memory operation will be stopped.
  
## File Structure  
*spiMemoryChips*  
	&nbsp;&nbsp; libs  
	&nbsp;&nbsp;&nbsp;&nbsp; fram  
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; fram.cpp  
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; fram.h  
	&nbsp;&nbsp;&nbsp;&nbsp; mram  
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; mram.cpp  
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; mram.h  
	&nbsp;&nbsp; source  
	&nbsp;&nbsp;&nbsp;&nbsp; framInterface  
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; framInterface.ino  
	&nbsp;&nbsp;&nbsp;&nbsp; mramInterface  
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; mramInterface.ino  

  
## Device Supported  
It should support all the devices that can be interfaced using SPI. Current tested  fine for:  
MR25H256A (https://www.mikroe.com/mram-click)  
MB85RS256A (https://www.mikroe.com/fram-click)