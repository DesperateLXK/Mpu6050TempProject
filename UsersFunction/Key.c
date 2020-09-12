#include "Key.h"
#include "delay.h"
void Key_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE2,3,4

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0设置成输入，默认下拉	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0
}

u8 Key_Scan(u8 mode)
{
	static u8 key_up=1;
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||WK_UP==1))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(WK_UP==1)return WKUP_PRES;
	}else if(KEY0==1&&WK_UP==0)key_up=1; 	    
 	return 0;        // 无按键按下
}


