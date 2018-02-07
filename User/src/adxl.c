#include "adxl.h"

	
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	uint8_t SPIData[2];


void adxl_read(uint16_t temp[])
{
	CS_ON();
	
SPI_I2S_SendData(SPI1, 0xB2);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
		SPIData[0] = SPI_I2S_ReceiveData(SPI1);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
			SPI_I2S_SendData(SPI1, 0x00);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
		SPIData[0] = SPI_I2S_ReceiveData(SPI1);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
		
		
		
			SPI_I2S_SendData(SPI1, 0xB3);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
		SPIData[1] = SPI_I2S_ReceiveData(SPI1);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
			SPI_I2S_SendData(SPI1, 0x00);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
		SPIData[1] = SPI_I2S_ReceiveData(SPI1);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}

		//temp[0] = SPIData[1]*256 + SPIData[0];
	 temp[0] = ((((uint16_t)SPIData[0])<<8)|((uint16_t)SPIData[1]))*0.002;
	
		
	 	
		 
		
		
		SPI_I2S_SendData(SPI1, 0xB4);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
		SPIData[0] = SPI_I2S_ReceiveData(SPI1);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
			SPI_I2S_SendData(SPI1, 0x00);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
		SPIData[0] = SPI_I2S_ReceiveData(SPI1);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
		
		
		
			SPI_I2S_SendData(SPI1, 0xB5);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
		SPIData[1] = SPI_I2S_ReceiveData(SPI1);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
			SPI_I2S_SendData(SPI1, 0x00);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
		SPIData[1] = SPI_I2S_ReceiveData(SPI1);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
		
		
		temp[1] = ((((uint16_t)SPIData[0])<<8)|((uint16_t)SPIData[1]))*0.002;
	//	temp[1] = SPIData[1]*256 + SPIData[0];
		
		SPI_I2S_SendData(SPI1, 0xB6);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
		SPIData[0] = SPI_I2S_ReceiveData(SPI1);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
			SPI_I2S_SendData(SPI1, 0x00);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
		SPIData[0] = SPI_I2S_ReceiveData(SPI1);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
		
		
		
			SPI_I2S_SendData(SPI1, 0xB7);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
		SPIData[1] = SPI_I2S_ReceiveData(SPI1);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
			SPI_I2S_SendData(SPI1, 0x01);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
		SPIData[1] = SPI_I2S_ReceiveData(SPI1);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
		
		
		
		temp[2] = ((((uint16_t)SPIData[0])<<8)|((uint16_t)SPIData[1]))*0.002;
		
		
		if ( temp[1]  > 65) 
		 	temp[1] =  131- temp[1];
			
		
		
		
		
		
		//temp[2] = SPIData[1]*256 + SPIData[0];
	
//	temp1[0] = 57.295*atan((uint16_t)temp[0]/ sqrt(pow((uint16_t)temp[1],2)+pow((uint16_t)temp[2],2)));
	//	temp1[1] =   57.295*atan((uint16_t)temp[1]/ sqrt(pow((uint16_t)temp[0],2)+pow((uint16_t)temp[2],2)));
		//temp1[2] = 57.295*atan((uint16_t)temp[2]/ sqrt(pow((uint16_t)temp[0],2)+pow((uint16_t)temp[1],2)));
		
		
	CS_OFF();


}



void adxl_init(void)
{

CS_ON();

	SPI_I2S_SendData(SPI1,  0x2C);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
		SPI_I2S_SendData(SPI1, 0x0B);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
	
		
		
		SPI_I2S_SendData(SPI1,  0x2A);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
		SPI_I2S_SendData(SPI1, 0x07);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
	
	SPI_I2S_SendData(SPI1, 0x2D);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
		SPI_I2S_SendData(SPI1, 0x08);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
		
		
		
		
		SPI_I2S_SendData(SPI1, 0x31);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
		SPI_I2S_SendData(SPI1,  0x02);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
		
	CS_OFF();

}











void SPI_ini(void)
	{
	
		
RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE);
RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;	

GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //????????? JTAG, SW ????????? ??????????
GPIO_PinRemapConfig(GPIO_Remap_SPI1,ENABLE);
		
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
		SPI_InitStructure.SPI_CRCPolynomial = 7;
		SPI_Init(SPI1, &SPI_InitStructure);

		CS_OFF();
 
		SPI_CalculateCRC(SPI1, ENABLE);
	

		SPI_Cmd(SPI1, ENABLE);


}



void GPIO_Configuration(void)
{
  
	
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
	
  
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
 
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	

	

}




