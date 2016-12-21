/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：操作外设及重定位基本原理
 * 功能：由汇编实现关闭或打开icache。
 */

#define WTCON		0xE2700000
#define SVC_STACK 	0xD0037D80

.global _start						// 把_start链接属性改为外部，则外部其它文件可看见_start 
_start:
	// 关闭看门狗
	ldr r0, =WTCON
	ldr r1, =0x0
	str r1, [r0]
	
	// 设置SVC_STACK栈
	ldr sp, =SVC_STACK
	
	// 关闭或开的icache
	mrc p15,0,r0,c1,c0,0;	// 读出协处理器C1 
	bic r0, r0, #(1<<12)	// 第12位置0，关闭icache
	//orr r0, r0, #(1<<12)	// 第12位置1，打开icache
	mcr p15,0,r0,c1,c0,0;   // 给C1赋值
	
	// 调用C程序
	bl water_lights
	
	// 汇编最后的这个死循环绝对不能丢
	b .
