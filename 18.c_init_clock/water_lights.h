/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ��SoCʱ��ϵͳ��������ʼ��
 * ���ܣ�C����ʵ��4��LED��ˮ��Ч����	
 */

// �궨��Ĵ�����ַ�ռ�
#define rGPJ2CON	(*((volatile unsigned int *)0xE0200280))
#define rGPJ2DAT	(*((volatile unsigned int *)0xE0200284))

// ��غ�������
void delay(void);
void water_lights(void);

