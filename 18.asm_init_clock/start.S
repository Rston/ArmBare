/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：SoC时钟系统概述及初始化
 * 功能：通过汇编设置系统典型时钟。
 */

#define WTCON		0xE2700000
#define SVC_STACK 	0xD0037D80

.global _start				// 把_start链接属性改为外部，则外部其它文件可看见_start 
_start:
	// 关闭看门狗
	ldr r0, =WTCON
	ldr r1, =0x0
	str r1, [r0]
	
	// 设置系统典型时钟
	bl clock_init
	
	// 设置SVC_STACK栈
	ldr sp, =SVC_STACK
	
	// 关闭或开启icache
	mrc p15,0,r0,c1,c0,0;	// 读出协处理器C1 
	//bic r0, r0, #(1<<12)	// 第12位置0，关闭icache
	orr r0, r0, #(1<<12)	// 第12位置1，打开icache
	mcr p15,0,r0,c1,c0,0;   // 给C1赋值
	
	// 初始化DDR2
	bl sdram_asm_init
	
	// 重定位
	adr r0, _start  		// adr指令加载_start运行时地址		
	ldr r1, =_start 		// ldr指令用于加载_start的链接地址	
	ldr r2, =bss_start		// bss段的起始地址，此地址为链接地址
	cmp r0, r1				// 比较_start的运行时地址和链接地址是否相等
	beq clean_bss		    // 若相等则不需重定位，则跳过copy_loop，直接clean_bss
	
copy_loop:
	ldr r3, [r0], #4    	// 运行时地址的源代码内容，即_start运行时地址的内容
	str r3, [r1], #4		// 拷贝到链接地址处形成第2份源代码，完成4个字节内容的拷贝
	cmp r1, r2				// r1和r2都是用ldr加载的，都是链接地址，所以r1不断+4总能等于r2
	bne copy_loop

clean_bss:					// 清bss段，其实就是在链接地址处把bss段全部清零
	ldr r0, =bss_start					
	ldr r1, =bss_end
	cmp r0, r1				// 如果r0等于r1，说明bss段为空，直接下去
	beq run_on_dram			// 清除bss完之后的地址
	mov r2, #0
clear_loop:
	str r2, [r0], #4		// 先将r2中的值放入r0所指向的内存地址，然后r0 = r0 + 4
	cmp r0, r1				
	bne clear_loop			

run_on_dram:	
	ldr pc, =water_lights	// ldr指令实现长跳转
	
	// 汇编最后的这个死循环不能丢
	b .						