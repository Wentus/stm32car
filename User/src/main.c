#include "main.h"


	GPIO_InitTypeDef Pinyshka; 
	TIM_TimeBaseInitTypeDef Timerushka_Base; 
	TIM_OCInitTypeDef Timerushka_OCI;
	TIM_TimeBaseInitTypeDef base_timer;
	USART_InitTypeDef MyUSART; 
	
#define impulscill 20

#define tsopLeft	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)
#define tsopCentr	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)
#define tsopRight	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)

	int middle = 150;
	int rule = 150;
	int hist_rule = 150;
	int speedadd= 0;
  int impuls;
  int vidstan[3] = {0, 0, 0};
  int napram = 0;
  int pach = 0;
  int speed = 150;
  int block = 0;
  int kru = 0;
  int tormiz = 0;
  int k = 0;
	
	uint16_t temp[3];
	uint16_t acceleration;
	uint8_t y;
	
	void Delay (unsigned int t) //
  {
  	unsigned int i;
      for (i = 0;i<t; i++);
  }



void Init_ADC(void)
{

  ADC_InitTypeDef ADC_InitStruct;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable the Dpr Clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  /* Configure Dpr pin as input up */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;

  GPIO_Init(GPIOC, &GPIO_InitStructure); 
  
  /* Reset ADC init structure parameters values */
  /* Initialize the ADC_Mode member */
  ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
  /* initialize the ADC_ScanConvMode member */
  ADC_InitStruct.ADC_ScanConvMode = DISABLE;
  /* Initialize the ADC_ContinuousConvMode member */
  ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
  /* Initialize the ADC_ExternalTrigConv member */
  ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  /* Initialize the ADC_DataAlign member */
  ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
  /* Initialize the ADC_NbrOfChannel member */
  ADC_InitStruct.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStruct);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_14,1,ADC_SampleTime_55Cycles5);
  ADC_Cmd(ADC1, ENABLE);

}


	
  void Init_timer(void){

  //  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
 
 
    Pinyshka.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 ;  
    Pinyshka.GPIO_Mode = GPIO_Mode_AF_PP; 
    Pinyshka.GPIO_Speed = GPIO_Speed_50MHz; 

    //

    GPIO_Init( GPIOB , &Pinyshka);

    Pinyshka.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 ;  // PA1 and PA2 and PA3
    Pinyshka.GPIO_Mode = GPIO_Mode_AF_PP; //
    Pinyshka.GPIO_Speed = GPIO_Speed_10MHz; // speed
    GPIO_Init( GPIOA , &Pinyshka);


    Pinyshka.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
    Pinyshka.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init( GPIOA , &Pinyshka);


//
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

    // 
 //   TIM_TimeBaseInitTypeDef Timerushka_Base; // 
    Timerushka_Base.TIM_CounterMode = TIM_CounterMode_Up; //
    Timerushka_Base.TIM_Prescaler =1 - 1; // 

    Timerushka_Base.TIM_Period = 400; //
    Timerushka_Base.TIM_ClockDivision = TIM_CKD_DIV1; // CKD[1:0]: Clock division 
    TIM_TimeBaseInit(TIM2, &Timerushka_Base); // 



    //TIM_OCInitTypeDef Timerushka_OCI;

    Timerushka_OCI.TIM_OCMode = TIM_OCMode_PWM1; // 
    Timerushka_OCI.TIM_OutputState = TIM_OutputState_Enable; // 
    Timerushka_OCI.TIM_Pulse = 0; //  TIMx->CCR1 
    //
  //  Timerushka_OCI.TIM_Pulse = 9;
    Timerushka_OCI.TIM_OCPolarity = TIM_OCPolarity_High; //
    TIM_OC2Init(TIM2, &Timerushka_OCI);
    TIM_OC3Init(TIM2, &Timerushka_OCI);
    TIM_OC4Init(TIM2, &Timerushka_OCI);


    // 
   //TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //TIM3



       Timerushka_Base.TIM_CounterMode = TIM_CounterMode_Up; //
       Timerushka_Base.TIM_Prescaler = 240 - 1; // 


       Timerushka_Base.TIM_Period = 2000; // 
       Timerushka_Base.TIM_ClockDivision = TIM_CKD_DIV1; // CKD[1:0]: Clock division 

       TIM_TimeBaseInit(TIM3, &Timerushka_Base); // 



          // 1)Timerushka_OCI.TIM_OCMode = TIM_OCMode_Toggle; 

          Timerushka_OCI.TIM_OCMode = TIM_OCMode_PWM1; // 
          Timerushka_OCI.TIM_OutputState = TIM_OutputState_Enable; // 
          Timerushka_OCI.TIM_Pulse = 75; // 

          Timerushka_OCI.TIM_OCPolarity = TIM_OCPolarity_High; // 
          TIM_OC3Init(TIM3, &Timerushka_OCI);
          TIM_OC4Init(TIM3, &Timerushka_OCI);
					
					
         // TIM_TimeBaseInitTypeDef base_timer;
          base_timer.TIM_Prescaler = 24000 - 1;
             base_timer.TIM_Period = 20;
             TIM_TimeBaseInit(TIM6, &base_timer);


             TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
             NVIC_EnableIRQ(TIM6_DAC_IRQn);




          NVIC_EnableIRQ(TIM2_IRQn);
      TIM2->DIER |= TIM_DIER_UIE;





    TIM_Cmd(TIM2, ENABLE);
    Delay(0xFFFFF);
    TIM_Cmd(TIM3, ENABLE);
    Delay(0xFFFFF);
    TIM_Cmd(TIM6, ENABLE);


    Delay(0xFFFFF);
}

  // 95 max right 65 max left

//-----------------------------------------



void TIM6_DAC_IRQHandler(){


			
	




		 adxl_read(temp);

    if (TIM_GetITStatus(TIM6, TIM_IT_Update) == SET)
    {

    	if( GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
    	if(kru == 0)
    			kru = 1;
    		else kru = 0;
    

			if(kru == 1)
    	{
    	if(tormiz  < 15)
    	{
    //	if (tormiz < 7 )
    	//	{






    		if (vidstan[1] < 60)
    		{
    		    	if(vidstan[0]> vidstan[2] )
    		    		middle = 190;
    		    	else
    		    		middle =110;

    		}
    		else middle = 150;
				
				
    					if(vidstan[0]>vidstan[2] )
    		 rule=middle-((vidstan[2]-vidstan[0])) ;
    		 	 	else     rule=middle - ((vidstan[2]-vidstan[0])) ;
 
    		
							hist_rule = hist_rule + (rule - hist_rule)/3;

							rule = hist_rule + (int)(rule - hist_rule)*0.02*20 + (int)((rule + hist_rule)/2)*0.02*5;
							
							/*		
			if( vidstan[1]> 15)
			{
			if ( temp[1] > 5) 
				y = 20;
			else 
				y--;
		}
			else y = 0;
			
		if ( y < 0) y = 0;

*/

    		if ( rule > 190) rule = 190; // right
    		if (rule < 110) rule = 110; // left
			
    	if ( (rule - 150)> 0 )
				{    	
				speed = 160 - ( rule - 150 )/4;
			//	rule = rule -y;
					
					
					if( rule < 150) rule=150;
				}
				
			else
				{
    			speed = 150 +(rule - 110)/4;
				//	rule = rule +y;
					if( rule > 150) rule=150;
				}

    		if (speed > 160) speed = 160;
    	//	if ( tormiz < 7)

    			if ( speed < 156) speed = 156;
    		//if(vidstan[1] < 20) speed = 78;


    			//if(tormiz < 7)


speed = 156;

    			if( vidstan[1] < 4)
    		    	    		tormiz++;
    			else
    				tormiz = 0;
					
					if( temp[0] < 80 && temp[0] > 60 )
						tormiz = 15;
    	}
    	else
    	if(tormiz > 14 && tormiz < 30)
    	{
    		TIM_SetCompare3(TIM3,146);
    		rule = 150;
    		TIM_SetCompare4(TIM3, 150);
    	tormiz++;
    	}
    		else if(tormiz >29 && tormiz <34)
    		{
    			TIM_SetCompare3(TIM3, 150);
    			TIM_SetCompare4(TIM3, 150);
    			rule = 150;
    		tormiz++;
    		if(vidstan[0]>vidstan[2])
    		    		 k=1;
    		else k = 0;

    		}
    			else
    		if(tormiz >33 && tormiz <44 )
    		{
    			tormiz++;
    			TIM_SetCompare3(TIM3, 140);

    			if(k == 1)
    		    		    			{
    		    		    			rule = 125;
    		    		    			  	TIM_SetCompare4(TIM3, 125);
    		    		    			}
    		    		    			else {
    		    		    				rule = 175;
    		    		    				   	TIM_SetCompare4(TIM3, 175);

    									}

    		}

    	else
    		if(tormiz >43 && tormiz <50 )
    		    		{
    		    			tormiz++;
    		    			if(k ==1)
    		    			{
    		    			rule = 125;
    		    			  	TIM_SetCompare4(TIM3, 125);
    		    			}
    		    			else {
    		    				rule = 175;
    		    				   	TIM_SetCompare4(TIM3, 175);

							}
    		    		}
    		else
    	if(tormiz >49 && tormiz <54 )
    	    		    		{
    	    		    			tormiz++;
    	    		    			rule = 150;
    	    		    			    			TIM_SetCompare4(TIM3, 125);
    	    		    		}


    				else tormiz = 0;



    	}
    	else
    	{
    		TIM_SetCompare3(TIM3, 150);


    		TIM_SetCompare4(TIM3, 125);
    	}

    	if( tormiz < 15)
    		TIM_SetCompare3(TIM3, speed);

    	TIM_SetCompare4(TIM3,rule);
	}
  
	
			
	
  TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
	
	
}








void TIM2_IRQHandler()
{


	if ( napram == 0)
	{
		if(impuls == 0)
		{
			TIM_SetCompare2(TIM2,vidstan[0]);
			TIM_SetCompare3(TIM2,0);
			TIM_SetCompare4(TIM2,0);


		}
		if ( impuls == impulscill )
		{
			if(tsopRight)
				if ( vidstan[0]< 10)

											vidstan[0]++;


										else vidstan[0]= vidstan[0] + vidstan[0]/5;
								else
									if(vidstan[0]< 10)
											vidstan[0]--;
									else
											vidstan[0] = vidstan[0] - vidstan[0]/5;


			TIM_SetCompare2(TIM2, 0);
		}

	}



	if ( napram == 1)
	{
		if(impuls == 0)
		{
			TIM_SetCompare2(TIM2, 0);
			TIM_SetCompare3(TIM2,vidstan[1]);
			TIM_SetCompare4(TIM2,0);


		}
		if ( impuls == impulscill )
		{

			if(tsopCentr)
					if ( vidstan[1]< 10)

							vidstan[1]++;

					else vidstan[1]= vidstan[1] + vidstan[1]/5;
				else
					if(vidstan[1]< 10)
							vidstan[1]--;
					else
							vidstan[1] = vidstan[1] - vidstan[1]/4;

			TIM_SetCompare3(TIM2, 0);
		}

	}



	if ( napram == 2)
	{
		if(impuls == 0)
		{
		TIM_SetCompare2(TIM2, 0);
		TIM_SetCompare3(TIM2,0);
		TIM_SetCompare4(TIM2,vidstan[2]);
		}

		if ( impuls == impulscill )
		{
			if(tsopLeft)
				if ( vidstan[2]< 10)

											vidstan[2]++;

										else vidstan[2]= vidstan[2] + vidstan[2]/5;
								else
									if(vidstan[2]< 10)
											vidstan[2]--;
									else
											vidstan[2] = vidstan[2] - vidstan[2]/5;
			TIM_SetCompare4(TIM2, 0);
		}

	}

	impuls++;

	if( impuls >= 2*impulscill)
	{
		napram++;
		impuls = 0;
	}


	if (napram > 2)
	napram = 0;


	if (vidstan[0] > 100)
		vidstan[0] = 100;

	if (vidstan[1] > 100)
		vidstan[1] = 100;

	if (vidstan[2] > 100)
		vidstan[2] = 100;

	if (vidstan[0] < 1)
			vidstan[0] = 1;

	if (vidstan[1] < 1)
			vidstan[1] = 1;

	if (vidstan[2] < 1)
			vidstan[2] = 1;

TIM2->SR &=~TIM_SR_UIF;

}



void Init_USART(void)
{
    //  ==============
    GPIO_InitTypeDef MyPin;  // 
    GPIO_StructInit(&MyPin);     // 

    // 
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE);

    // PA10 == RX 
    MyPin.GPIO_Pin   = GPIO_Pin_10;            // PA10 == RX.
    MyPin.GPIO_Mode  = GPIO_Mode_IN_FLOATING;  // 
    GPIO_Init( GPIOA , &MyPin);                // 
    // PA9 == TX -
    MyPin.GPIO_Pin   = GPIO_Pin_9;             // PA9 == TX
    MyPin.GPIO_Mode  = GPIO_Mode_AF_PP;        //
    MyPin.GPIO_Speed = GPIO_Speed_50MHz;       // 
    GPIO_Init( GPIOA , &MyPin);                //
    // ==============


  


    //
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 , ENABLE);

    MyUSART.USART_BaudRate            = 9600;
    MyUSART.USART_WordLength          = USART_WordLength_8b;
    MyUSART.USART_StopBits            = USART_StopBits_1;
    MyUSART.USART_Parity              = USART_Parity_No;
    MyUSART.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
    MyUSART.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    USART_Init( USART1 , &MyUSART);   // 
    USART_Cmd( USART1 , ENABLE);      // 
    // ==============
}






int main()
{
	
	
	
	
	
	GPIO_Configuration();
	SPI_ini();
	adxl_init();
	
	Init_USART();
	Init_timer(); 
	
	
	
	for(;;);
  
			
	
		
		
   //USART_SendData( USART1 , temp[2]+ temp[0]);
	//	USART_SendData( USART1 , vidstan[1]);
		// USART_SendData( USART1 , temp[2]/500);
	//Delay(0xFFFFF);
	 
	
	return 0;
}

