#include "stdafx.h"
DWORD IsInsideVPC_exceptionFilter(LPEXCEPTION_POINTERS ep)
{
	PCONTEXT ctx = ep->ContextRecord;
	ctx->Ebx = -1;
	ctx->Eip += 4;
	return EXCEPTION_CONTINUE_EXECUTION;
}
bool ISADetect() //ִ����Ч�����룬����ִ��Ϊ������������쳣Ϊ�����
{
	printf("VirtualPC Detect......");
	bool rc = false;
	__try
	{
		__asm
		{
			push ebx
			mov ebx, 0
			mov eax, 1
			__emit 0fh
			__emit 3fh
			__emit 07h
			__emit 0bh
			test ebx, ebx
			setz[rc]
			pop ebx
		}
	}
	__except (IsInsideVPC_exceptionFilter(GetExceptionInformation()))
	{
		rc = true;
	}
	printf("     Done.\n");
	return rc;
}