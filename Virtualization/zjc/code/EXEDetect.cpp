#include "stdafx.h"
#include <Tlhelp32.h>
bool CheckVMWare_exe()
{
	DWORD ret = 0; 
	PROCESSENTRY32 pe32; //����������ſ��ս�����Ϣ�Ľṹ��
	pe32.dwSize = sizeof(pe32); 
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //��ȡϵͳ�����е�ǰ���н��̵Ŀ���
	if (hProcessSnap == INVALID_HANDLE_VALUE) return true; //��ȡ����ʧ��
	bool bMore = Process32First(hProcessSnap, &pe32); 
	while (bMore)
	{
		if (_tcscmp(pe32.szExeFile, L"vmware.exe") == 0) return false;
		bMore = Process32Next(hProcessSnap, &pe32);
	} //�������������н�����Ϣ������Ƿ���vmware.exe�Ľ���
	CloseHandle(hProcessSnap);
	return true;
}
bool CheckVB_exe()
{
	DWORD ret = 0;
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) return true;
	bool bMore = Process32First(hProcessSnap, &pe32);
	while (bMore)
	{
		if (_tcscmp(pe32.szExeFile, L"VBoxService.exe") == 0) return false;
		bMore = Process32Next(hProcessSnap, &pe32);
	}
	CloseHandle(hProcessSnap);
}
bool EXEDetect()
{
	printf("EXEDetect......");
	bool answer1_exe = CheckVMWare_exe();
	bool answer2_exe = CheckVB_exe;
	printf("            Done.\n");
	if (answer1_exe == false || answer2_exe == false) return false;
	else return true;
}