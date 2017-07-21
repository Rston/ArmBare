/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：简单的串口操作
 * 功能：串口0持续发送字符
 */
#include "uart.h"
 
int main(int argc, char **argv)
{
	char recvdata;
	
	// 串口0初始化
	uart_init();
	
	while(1)
	{
		uart_putc('H');
	}
	
	return 0;
}