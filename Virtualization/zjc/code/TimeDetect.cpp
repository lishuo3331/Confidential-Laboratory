#include "stdafx.h"
bool TimeDetect()
{
	printf("TimeDetect......");
	//ͨ��rdtscָ�����ִ��һ��ָ�������ĵ�ʱ��
	__asm
	{
		rdtsc
		xchg ebx,eax
		rdtsc
		sub eax,ebx
		cmp eax,0xff
		jg detected
	}
	printf("           Done.\n");
	return true;
detected:
	return false;
}