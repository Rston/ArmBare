/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ���򵥵Ĵ��ڲ���
 * ���ܣ�����0���������ַ�
 */
#include "uart.h"
 
int main(int argc, char **argv)
{
	char recvdata;
	
	// ����0��ʼ��
	uart_init();
	
	while(1)
	{
		uart_putc('H');
	}
	
	return 0;
}