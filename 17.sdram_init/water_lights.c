/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ����ʼ��SDRAM�ʹ����ض�λ
 * ���ܣ�C����ʵ��4��LED��ˮ��Ч����	
 */
#include "water_lights.h"
 
void delay(void)
{
	volatile unsigned int i = 1000000;		// volatile�ñ�������Ҫ�Ż������������ļ�
	while (i--);							// ����ȷʵ������ʱ�䣬ʵ��delay
}
 
void water_lights(void)
{
	// ����GPJ2CON0~GPJ2CON3��4������Ϊ���ģʽ
	rGPJ2CON = ((1<<0) | (1<<4) | (1<<8) | (1<<12));
	
	// ʵ��LED��ˮ�ƹ���
	while (1)
	{
		//rGPJ2DAT = ~(1<<0);
		//delay();
		
		rGPJ2DAT = ~(1<<1);
		delay();
		
		rGPJ2DAT = ~(1<<2);
		delay();
		
		//rGPJ2DAT = ~(1<<3);
		//delay();
	}
}