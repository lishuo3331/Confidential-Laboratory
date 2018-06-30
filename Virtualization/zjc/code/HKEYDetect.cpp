#include "stdafx.h"
bool CheckVM_hkey()
{
	HKEY hkey;
	if (RegOpenKey(HKEY_CLASSES_ROOT, (LPCWSTR)"\\Applications\\VMwareHostOpen.exe", &hkey) == ERROR_SUCCESS) return false; //���Դ�������������ע���
	else return true;
}
bool CheckVB_hkey()
{
	HKEY hkey;
	if (RegOpenKey(HKEY_CLASSES_ROOT, (LPCWSTR)"SOFTWARE\\Oracle\\VirtualBox Guest Assitions", &hkey) == ERROR_SUCCESS) return false;
	else return true;
}
bool HKEYDetect()
{
	printf("HKEYDetect......");
	bool answer1_hkey = CheckVM_hkey();
	bool answer2_hkey = CheckVB_hkey();
	printf("           Done.\n");
	if (answer1_hkey == false || answer2_hkey == false) return false;
	else return true;
}