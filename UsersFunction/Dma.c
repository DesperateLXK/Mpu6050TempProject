#include "Dma.h"

void Dma_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{
	DMA_InitTypeDef DMA_InitInstructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	DMA_DeInit(DMA_CHx);
	DMA_InitInstructure.DMA_BufferSize=cndtr;
	DMA_InitInstructure.DMA_DIR=DMA_DIR_PeripheralDST;
	DMA_InitInstructure.DMA_M2M=DMA_M2M_Disable;
	DMA_InitInstructure.DMA_MemoryBaseAddr=cmar;
	DMA_InitInstructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	DMA_InitInstructure.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitInstructure.DMA_Mode=DMA_Mode_Normal;
	DMA_InitInstructure.DMA_PeripheralBaseAddr=cpar;
	DMA_InitInstructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	DMA_InitInstructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitInstructure.DMA_Priority=DMA_Priority_Medium;
	DMA_Init(DMA_CHx,&DMA_InitInstructure);
	DMA_Cmd(DMA_CHx,ENABLE);
}



