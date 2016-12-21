/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：操作外设及重定位基本原理
 * 功能：C语言实现4个LED流水灯效果。	
 */

// 宏定义寄存器地址空间
#define rGPJ2CON	(*((volatile unsigned int *)0xE0200280))
#define rGPJ2DAT	(*((volatile unsigned int *)0xE0200284))

// 相关函数声明
void delay(void);
void water_lights(void);

