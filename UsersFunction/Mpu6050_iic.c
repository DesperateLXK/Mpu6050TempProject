#include "sys.h"
#include "Mpu6050_iic.h"
#include "delay.h"
////mpu��ʱ����
void MPU_IIC_Delay(void)
{
	delay_us(2);
}

void MPU_IIC_Init(void)
{					     
  GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//��ʹ������IO PORTBʱ�� 
		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;	 // �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIO 
	
  GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11);						 //PB10,PB11 �����	
 
}
//////��ʼ�ź�
void MPU_IIC_Start(void)
{
	MPU_SDA_OUT();
	SDA=1;
	SCL=1;
	MPU_IIC_Delay();
	SDA=0;
	MPU_IIC_Delay();
	SCL=0;
}
//////ֹͣ�ź�	
void MPU_IIC_Stop(void)
{
	MPU_SDA_OUT();
	SCL=0;
	SDA=0;
	MPU_IIC_Delay();
	SCL=1;
	SDA=1;
	MPU_IIC_Delay();
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 MPU_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	MPU_SDA_IN();      //SDA����Ϊ����  
	SDA=1;
	MPU_IIC_Delay();	   
	SCL=1;
	MPU_IIC_Delay();	 
	while(MPU_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			MPU_IIC_Stop();
			return 1;
		}
	}
	SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void MPU_IIC_Ack(void)
{
	SCL=0;
	MPU_SDA_OUT();
	SDA=0;
	MPU_IIC_Delay();
	SCL=1;
	MPU_IIC_Delay();
	SCL=0;
}
//������ACKӦ��		    
void MPU_IIC_NAck(void)
{
	SCL=0;
	MPU_SDA_OUT();
  SDA=1;
	MPU_IIC_Delay();
	SCL=1;
	MPU_IIC_Delay();
	SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void MPU_IIC_Send_Byte(u8 txd)
{                        
  u8 t;   
	MPU_SDA_OUT(); 	    
  SCL=0;//����ʱ�ӿ�ʼ���ݴ���
  for(t=0;t<8;t++)
  {              
    SDA=(txd&0x80)>>7;
    txd<<=1; 	  
	  SCL=1;
	  MPU_IIC_Delay(); 
		SCL=0;	
		MPU_IIC_Delay();
  }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 MPU_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	MPU_SDA_IN();//SDA����Ϊ����
  for(i=0;i<8;i++ )
	{
    SCL=0; 
    MPU_IIC_Delay();
		SCL=1;
    receive<<=1;
    if(MPU_READ_SDA)
			receive++;   
		MPU_IIC_Delay(); 
  }					 
  if (!ack)
    MPU_IIC_NAck();//����nACK
  else
    MPU_IIC_Ack(); //����ACK   
  return receive;
}








