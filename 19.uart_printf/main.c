/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ��������ֲ�������
 * ���ܣ�������ֲprintf��������
 */
#include "stdio.h"
#include "uart.h"
 
int main(int argc, char **argv)
{
	// ����0��ʼ��
	uart_init();
	
	while(1)
	{
		printf("hello world.\r\n");
	}

	return 0;
}