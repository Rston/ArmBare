/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ��Ŀ������ָ��ʵս��typedef
 * ���ܣ��ṹ����Ƕ����ָ��ʵ�ֲַ㣬���ļ�Ϊ�ϲ㣬��Ҫʵ�ּ�����ҵ���߼���
 */
#include "framework.h"

// ʵ�ּ�����ҵ���߼�
int calculator(const struct cal_t *p)
{
	return (p->func(p->a, p->b)); 
}