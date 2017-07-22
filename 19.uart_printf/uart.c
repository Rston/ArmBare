/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：串口移植输出函数
 * 功能：串口移植printf函数功能
 */
#include "uart.h"
 
// 初始化串口
void uart_init(void)
{
	// 初始化RXD和TXD的GPIO引脚
	rGPA0CON &= ~(0xff<<0);			// 清零寄存器
	rGPA0CON |= 0x00000022;			// bit[3:0]=0b0010；bit[7:4]=0b0010
	
	// 初始化关键寄存器
	rULCON0 = 0x03;					// 普通模式+0校验位+1停止位+8数据位
	rUCON0  = 0x05;					// 选择PCLK_PSYS做为串口时钟源+不使用回环模式+发送和接收都是中断/轮询模式
	rUMCON0 = 0x00;					// 禁止流控的一切配置
	rUFCON0 = 0x00;					// 禁止FIFO模式
	
	// 设置串口波特率	
#if 1								// 使用66.7MHz计算
	rUBRDIV0 = 35;					// DIV_VAL = (66700000/(115200*16)-1) = 35.18
	rUDIVSLOT0 = 0x0888;			// 1的个数 = 16*0.18= 2.88 = 3个1，查官方推荐表
#endif

#if 0								// 使用66MHz计算
	rUBRDIV0 = 34;					// DIV_VAL = (66000000/(115200*16)-1) = 34.08
	rUDIVSLOT0 = 0xDFDD;			// 1的个数 = 16*0.8= 11 = 11个1，查官方推荐表
#endif
}

// 串口发送1个字符
void putc(char c)
{
	while (!(rUTRSTAT0 & (1<<1)));	// 若发送缓冲区为空，则发送数据
	rUTXH0 = c;
}

// 串口接收1个字符
char getc(void)
{
	while (!(rUTRSTAT0 & (1<<0)));	// 若接收到数据，则返回接收到的数据
	return (rURXH0 & 0x0f);
}
