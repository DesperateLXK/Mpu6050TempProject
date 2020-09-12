#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "Led.h"
#include "Key.h"
#include "Lcd.h"
#include "Mpu6050.h"
#include "Mpu6050_iic.h"
#include "Timer.h"
int main(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
	uart_init(115200);
	Led_Init();	
	while(Mpu6050_Init());
	Timer7_init(7199,50);
	//LCD_Init();
	while(1);
	
}

//#include "Dma.h"




//#define SEND_BUF_SIZE 8200


//u8 SendBuff[SEND_BUF_SIZE];
//u16 i;

//int main(void)
//{		
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	delay_init();
//	uart_init(115200);
//	Led_Init();	
//	LCD_Init();
//	POINT_COLOR=BLUE;
//	LCD_ShowString(80,80,200,16,16," Who Am I????");
//	Dma_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,SEND_BUF_SIZE);
//	for (i=0; i< SEND_BUF_SIZE;i++)
//	{
//		SendBuff[i]=0xFF;
//	}
//	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
//	while(1)
//	{
//		
//	}
//} 




