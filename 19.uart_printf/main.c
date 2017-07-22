/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：串口移植输出函数
 * 功能：串口移植printf函数功能
 */
#include "stdio.h"
#include "uart.h"
 
int main(int argc, char **argv)
{
	// 串口0初始化
	uart_init();
	
	while(1)
	{
		printf("hello world.\r\n");
	}

	return 0;
}