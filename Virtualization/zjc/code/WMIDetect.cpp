#include "stdafx.h"
#include <string>
#include <WbemIdl.h>
#include <comdef.h>
#include <atlbase.h>
#include <atlstr.h>
#pragma comment(lib,"wbemuuid.lib")
using namespace std;
bool ManageWMIInfo(string &result, string table, wstring wcol)
{
	HRESULT hres; //��������ֵ
	char bord[1024];
	//��ʼ��COM
	hres = CoInitialize(0);
	//���WMI����COM�ӿ�
	IWbemLocator *pLoc = NULL;
	hres = CoCreateInstance(
		CLSID_WbemLocator,
		0,
		CLSCTX_INPROC_SERVER,
		IID_IWbemLocator,
		(LPVOID *)&pLoc);
	if (FAILED(hres))
	{
		cout << "Failed to create IWbemLocator object."
			<< "Err code = 0x"
			<< hex << hres << endl;
		CoUninitialize();
		return false;
	}
	//ͨ�����ӽӿ�����WMI���ں˶�����ROOT//CIMV2
	IWbemServices *pSvc = NULL;
	hres = pLoc->ConnectServer(
		_bstr_t(L"ROOT\\CIMV2"),//Object path of WMI namespace
		NULL, //User name. NULL = current user
		NULL, //User password. NULL = current
		0, //Locale. NULL indicates current
		NULL, //Security flags.
		0, //Authority(e.r. Kerberos)
		0, //Context object
		&pSvc //pointer to IWbemServices proxy
	);
	if (FAILED(hres))
	{
		cout << "Could not connect.Error code = 0x"
			<< hex << hres << endl;
		pLoc->Release();
		CoUninitialize();
		return false;
	}
	//�����������İ�ȫ����
	hres = CoSetProxyBlanket(
		pSvc, // Indicates the proxy to set
		RPC_C_AUTHN_WINNT, //RPC_C_AUTHN_xxx
		RPC_C_AUTHZ_NONE, //RPC_C_AUTHZ_xxx
		NULL, // Server principal name
		RPC_C_AUTHN_LEVEL_CALL, // RPC_C_AUTHN_LEVEL_xxx
		RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
		NULL, // client identity
		EOAC_NONE //proxy capabilities
	);
	if (FAILED(hres))
	{
		cout << "Could noe set proxy blanket. Error code = 0x"
			<< hex << hres << endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return false;
	}
	//ͨ�������������WMI��������
	IEnumWbemClassObject* pEnumerator = NULL;
	string select = "SELECT * FROM " + table;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t(select.c_str()),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator
	);
	if (FAILED(hres))
	{
		cout << "Query for Network Adapter Configuration failed."
			<< "Error code = 0x"
			<< hex << hres << endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return false;
	}
	//ѭ��ö�����еĽ������
	ULONG uReturn = 0;
	IWbemClassObject *pclsObj = NULL;
	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		if (0 == uReturn)
		{
			break;
		}
		VARIANT vtProp;
		VariantInit(&vtProp);
		hr = pclsObj->Get(wcol.c_str(), 0, &vtProp, 0, 0);
		if (!FAILED(hr))
		{
			CW2A tmpstr1(vtProp.bstrVal);
			strcpy_s(bord, 200, tmpstr1);
			result = bord;
		}
		VariantClear(&vtProp);
	}
	//�ͷ���Դ
	pSvc->Release();
	pLoc->Release();
	pEnumerator->Release();
	pclsObj->Release();
	CoUninitialize();
	return true;
}
bool CheckVM_BaseBoard()
{
	string table = "Win32_BaseBoard";
	wstring wcol = L"SerialNumber";
	string ret;
	ManageWMIInfo(ret, table, wcol);
	if (ret == "None") return false;
	else return true;
}
bool CheckVM_DiskDrive()
{
	string table = "Win32_DiskDrive";
	wstring wcol = L"Caption";
	string ret;
	ManageWMIInfo(ret, table, wcol);
	if (ret.find("VMWare") != string::npos) return false;
	else return true;
}
bool CheckVM_computersystem()
{
	string table = "Win32_computersystem";
	wstring wcol = L"Model";
	string ret;
	ManageWMIInfo(ret, table, wcol);
	if (ret.find("VMWare") != string::npos) return false;
	else return true;
}
bool CheckVB_computersystem()
{
	string table = "Win32_computersystem";
	wstring wcol = L"Model";
	string ret;
	ManageWMIInfo(ret, table, wcol);
	if (ret.find("VirtualBox") != string::npos) return false;
	else return true;
}
bool CheckVB_DiskDrive()
{
	string table = "Win32_DiskDrive";
	wstring wcol = L"Caption";
	string ret;
	ManageWMIInfo(ret, table, wcol);
	if (ret.find("VBOX") != string::npos) return false;
	else return true;
}
bool CheckVP_DiskDrive()
{
	string table = "Win32_DiskDrive";
	wstring wcol = L"Caption";
	string ret;
	ManageWMIInfo(ret, table, wcol);
	if (ret.find("Virtual HD") != string::npos) return false;
	else return true;
}
bool CheckVP_computersystem()
{
	string table = "Win32_computersystem";
	wstring wcol = L"Model";
	string ret;
	ManageWMIInfo(ret, table, wcol);
	if (ret.find("Virtual Machine!") != string::npos) return false;
	else return true;
}
bool WMIDetect()
{
	printf("WMIDetect......");
	bool a_1_1 = CheckVM_BaseBoard();
	bool a_1_2 = CheckVM_computersystem();
	bool a_1_3 = CheckVM_DiskDrive();
	bool a_2_1 = CheckVB_computersystem();
	bool a_2_2 = CheckVB_DiskDrive();
	bool a_3_1 = CheckVP_computersystem();
	bool a_3_2 = CheckVP_DiskDrive();
	printf("            Done.\n");
	if (a_1_1 == false || a_1_2 == false || a_1_3 == false || a_2_1 == false || a_2_2 == false || a_3_1 == false || a_3_2 == false) return false;
	else return true;
}