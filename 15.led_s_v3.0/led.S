/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：编写LED程序及反汇编工具
 * 功能：汇编实现同时点亮4个LED灯。
 */
 
#define GPJ2CON 0xE0200280
#define GPJ2DAT 0xE0200284
 
.global _start						// 把_start链接属性改为外部，则外部其它文件可看见_start 
_start:
	// 第1步：将0x00001111写入0xE0200280位置（GPJ2CON）
	// 即设置GPJ2CON0~GPJ2CON3共4个引脚为输出模式
	ldr r0, =((1<<0) | (1<<4) | (1<<8) | (1<<12))	
	ldr r1, =GPJ2CON				// 通过=号看出使用的是ldr伪指令，因为编译器可判断该立即数
	str r0, [r1]					// 是合法立即数/非法立即数。
									// 寄存器间接寻址，把r0中的数写入到以r1中的数为地址的内存中去
flash:	
	// 第2步：点亮LED0
	ldr r0, =~(1<<0)
	ldr r1, =GPJ2DAT
	str r0, [r1]
	bl delay						
	
	// 第3步：点亮LED1
	ldr r0, =~(1<<1)
	ldr r1, =GPJ2DAT
	str r0, [r1]
	bl delay						
	
	// 第4步：点亮LED2
	ldr r0, =~(1<<2)
	ldr r1, =GPJ2DAT
	str r0, [r1]
	bl delay						
	
	// 第3步：点亮LED3
	ldr r0, =~(1<<3)
	ldr r1, =GPJ2DAT
	str r0, [r1]
	bl delay						// 使用bl调用延时函数，会将返回地址保存在lr寄存器中
	
	b flash							// 继续循环，使用b跳转，不保存返回地址到lr寄存器中

// 延时函数，函数名为delay
delay:
	ldr r2, =9000000
	ldr r3, =0x0
delay_loop:
	sub r2, r2, #1					// r2 = r2 - 1
	cmp r2, r3						// cmp会影响CPSR中的Z标志位，若r2等于r3，则Z标志位置1，下句中的bne不成立
	bne delay_loop
	mov pc, lr						// 函数调用返回
