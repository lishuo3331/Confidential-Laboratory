#include "stdafx.h"
bool LDTDetect(void) //��ȡIDT��LDT��GDT��Ļ�ַ����������
{
	ULONG xdt = 0;
	ULONG InVM = 0;
	printf("IDTDetect......");
	__asm
	{
		push edx
		sidt [esp-2]
		pop edx
		nop
		mov xdt , edx
	}
	if (xdt > 0xd0000000) InVM = 1;
	printf("            Done.\n");
	printf("LDTDetect......");
	__asm
	{
		push edx
		sldt [esp-2]
		pop edx
		nop
		mov xdt , edx
	}
	if (xdt > 0xd0000000) InVM += 1;
	printf("            Done.\n");
	printf("GDTDetect......");
	__asm
	{
		push edx
		sgdt [esp-2]
		pop edx
		nop 
		mov xdt , edx
	}
	if (xdt > 0xd0000000) InVM += 1;
	printf("            Done.\n");
	if (InVM == 0) return true;
	else return false;
}