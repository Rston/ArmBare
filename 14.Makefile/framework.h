#ifndef __FRAMEWORK_H__
#define __FRAMEWORK_H__

// ���庯��ָ������pFunc
typedef int (*pFunc)(int, int);

// ����ṹ������struct cal_t
struct cal_t
{
	int a;				// ��������a
	int b;				// ��������b
	pFunc func;			// ���庯���ķ�װ
};

// �������ϲ㺯���ӿڣ����²����
int calculator(const struct cal_t *p);

#endif