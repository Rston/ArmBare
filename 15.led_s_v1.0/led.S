/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：编写LED程序及反汇编工具
 * 功能：汇编实现点亮第1个和第3个LED灯。
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
	
	// 第2步：将0b00001010写入0xE0200284位置（GPJ2DAT）
	// 即设置GPJ2DAT0~GPJ2DAT3为0b00000101
	ldr r0, =((1<<0) | (0<<1) | (1<<2) | (0<<3))
	ldr r1, =GPJ2DAT
	str r0, [r1]
	
	b .								// 死循环，程序停留在这里，.表示当前指针的地址
									// 裸机程序是直接在CPU上运行的，CPU会逐行运行裸机程序直至CPU断电关机
									// 如果裸机程序全部被执行完了CPU就会跑飞（跑飞结果未定义）
									// 为了不让CPU跑飞即在整个裸机程序执行完后添加死循环
