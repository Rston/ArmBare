/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ������ָ��ʵս��typedef
 * ���ܣ��ṹ����Ƕ����ָ��ʵ�ֲַ㣬���ļ�Ϊ�²㣬��Ҫʵ�־���ļ��������㡣
 */
#include <stdio.h>
#include "framework.h"
#include "cal.h"

int main(int argc, char **argv)
{
	int ret = 0;
	struct cal_t myCal;			// ����ṹ�����
	
	myCal.a = 14;				// ���ṹ�������ֵ
	myCal.b = 2;
	myCal.func = multiply;		
	
	ret = calculator(&myCal);	// �����ϲ�ӿ�
	printf("ret = %d.\n", ret);
	
	return 0;
}

// �ӷ�
int add(int a, int b)
{
	return (a + b);
}

// ����
int sub(int a, int b)
{
	return (a - b);
}

// �˷�
int multiply(int a, int b)
{
	return (a * b);
}

// ����
int divide(int a, int b)
{
	return (a / b);
}