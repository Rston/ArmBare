/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：初始化SDRAM和代码重定位
 * 功能：C语言实现4个LED流水灯效果。	
 */
#include "water_lights.h"
 
void delay(void)
{
	volatile unsigned int i = 1000000;		// volatile让编译器不要优化，才能真正的减
	while (i--);							// 才能确实的消耗时间，实现delay
}
 
void water_lights(void)
{
	// 设置GPJ2CON0~GPJ2CON3共4个引脚为输出模式
	rGPJ2CON = ((1<<0) | (1<<4) | (1<<8) | (1<<12));
	
	// 实现LED流水灯功能
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