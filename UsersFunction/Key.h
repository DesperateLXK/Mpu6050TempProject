#ifndef __Key_h_
#define __Key_h_

#include "sys.h"

#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)   //��ȡ����0
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)  //��ȡ����3(WK_UP) 

 

#define KEY0_PRES 	1	//KEY0����
#define WKUP_PRES   4	//KEY_UP����(��WK_UP/KEY_UP)


void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��	
void Key_Init(void);

u8 Key_Scan(u8 mode);



#endif


