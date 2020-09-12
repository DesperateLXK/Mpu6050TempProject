#ifndef __Key_h_
#define __Key_h_

#include "sys.h"

#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)   //读取按键0
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)  //读取按键3(WK_UP) 

 

#define KEY0_PRES 	1	//KEY0按下
#define WKUP_PRES   4	//KEY_UP按下(即WK_UP/KEY_UP)


void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数	
void Key_Init(void);

u8 Key_Scan(u8 mode);



#endif


