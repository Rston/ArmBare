/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ��������ֲ�������
 * ���ܣ�������ֲprintf��������
 */
#include "uart.h"
 
// ��ʼ������
void uart_init(void)
{
	// ��ʼ��RXD��TXD��GPIO����
	rGPA0CON &= ~(0xff<<0);			// ����Ĵ���
	rGPA0CON |= 0x00000022;			// bit[3:0]=0b0010��bit[7:4]=0b0010
	
	// ��ʼ���ؼ��Ĵ���
	rULCON0 = 0x03;					// ��ͨģʽ+0У��λ+1ֹͣλ+8����λ
	rUCON0  = 0x05;					// ѡ��PCLK_PSYS��Ϊ����ʱ��Դ+��ʹ�ûػ�ģʽ+���ͺͽ��ն����ж�/��ѯģʽ
	rUMCON0 = 0x00;					// ��ֹ���ص�һ������
	rUFCON0 = 0x00;					// ��ֹFIFOģʽ
	
	// ���ô��ڲ�����	
#if 1								// ʹ��66.7MHz����
	rUBRDIV0 = 35;					// DIV_VAL = (66700000/(115200*16)-1) = 35.18
	rUDIVSLOT0 = 0x0888;			// 1�ĸ��� = 16*0.18= 2.88 = 3��1����ٷ��Ƽ���
#endif

#if 0								// ʹ��66MHz����
	rUBRDIV0 = 34;					// DIV_VAL = (66000000/(115200*16)-1) = 34.08
	rUDIVSLOT0 = 0xDFDD;			// 1�ĸ��� = 16*0.8= 11 = 11��1����ٷ��Ƽ���
#endif
}

// ���ڷ���1���ַ�
void putc(char c)
{
	while (!(rUTRSTAT0 & (1<<1)));	// �����ͻ�����Ϊ�գ���������
	rUTXH0 = c;
}

// ���ڽ���1���ַ�
char getc(void)
{
	while (!(rUTRSTAT0 & (1<<0)));	// �����յ����ݣ��򷵻ؽ��յ�������
	return (rURXH0 & 0x0f);
}
