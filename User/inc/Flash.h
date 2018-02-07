#ifndef FLASH_H
#define FLASH_H

#include "stm32f10x.h"

#define ADDRESS		0x08020000

uint32_t Read_Flash(uint32_t Data_adr);
void Write_Flash(uint32_t Data_adr, uint32_t Data);


#endif
