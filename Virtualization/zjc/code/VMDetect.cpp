#include "stdafx.h" 
bool IsInsideVMWare()
{
	bool rc = true;

	__try
	{
		__asm
		{
			push   edx
			push   ecx
			push   ebx

			mov    eax, 'VMXh'
			mov    ebx, 0
			mov    ecx, 10 //ָ�����ܺţ����ڻ�ȡVMWare�汾
			mov    edx, 'VX' //�˿ں�
			in     eax, dx //�Ӷ˿�dx��ȡ�汾��eax

			cmp    ebx, 'VMXh' //�ж�ebx���Ƿ����VMWare�汾
			setz[rc]

			pop    ebx
			pop    ecx
			pop    edx
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		rc = false;
	}

	return rc;
}
bool VMDetect()
{
	printf("VMware Detect......");
	bool rc;
	rc = IsInsideVMWare();
	printf("        Done.\n");
	if (rc == false) return true;
	else return false;
}