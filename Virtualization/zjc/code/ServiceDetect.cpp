#include "stdafx.h"
using namespace std;
bool CheckVM_service()
{
	int menu = 0;
	SC_HANDLE SCMan = OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE); //��ָ���ķ�����ƹ��������ݿ�
	if (SCMan == NULL)
	{
		cout << GetLastError() << endl;
		cout << "OpenSCManager Error" << endl;
		return -1;
	}
	//����ϵͳ����Ľṹ
	LPENUM_SERVICE_STATUSA service_status;
	DWORD cbBytesNeeded = NULL;
	DWORD ServicesReturned = NULL;
	DWORD ResumeHandle = NULL;
	service_status = (LPENUM_SERVICE_STATUSA)LocalAlloc(LPTR, 1024 * 64);
	//��ȡϵͳ����ļ���Ϣ
	bool ESS = EnumServicesStatusA(SCMan, //ϵͳ������
		SERVICE_WIN32,//��������
		SERVICE_STATE_ALL, //�����״̬
		(LPENUM_SERVICE_STATUSA)service_status, //���������ϵͳ����Ľṹ
		1024 * 64, //�ṹ�Ĵ�С
		&cbBytesNeeded, //������������ܷ�������ķ���
		&ServicesReturned, //������������ܷ��ط��������
		&ResumeHandle); //���������������һ�ε��ñ���Ϊ0������Ϊ0����ɹ�
	if (ESS == NULL)
	{
		cout << "EnumServicesStatus Error" << endl;
		return -1;
	}
	for (int i = 0; i < ServicesReturned; i++) //���ҷ��صķ������Ƿ����������־����
	{
		if (strstr(service_status[i].lpDisplayName, "VMware Tools") != NULL ||
			strstr(service_status[i].lpDisplayName, "VMware ����������ַ���") != NULL)
			return false;
	}
	//�رշ���������ľ��
	CloseServiceHandle(SCMan);
	return true;
}
bool CheckVirtualPC_service()
{
	int menu = 0;
	//��ϵͳ���������
	SC_HANDLE SCMan = OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE);
	if (SCMan == NULL)
	{
		cout << GetLastError() << endl
			<< "OpenSCManager Error" << endl;
		return -1;
	}
	//����ϵͳ����Ľṹ
	LPENUM_SERVICE_STATUSA service_status;
	DWORD cbBytesNeeded = NULL;
	DWORD ServicesReturned = NULL;
	DWORD ResumeHandle = NULL;
	service_status = (LPENUM_SERVICE_STATUSA)LocalAlloc(LPTR, 1024 * 64);
	//��ȡϵͳ����ļ���Ϣ
	bool ESS = EnumServicesStatusA(SCMan, //ϵͳ������
		SERVICE_WIN32, //���������
		SERVICE_STATE_ALL, //�����״̬
		(LPENUM_SERVICE_STATUSA)service_status, //���������ϵͳ����Ľṹ
		1024 * 64, //�ṹ�Ĵ�С
		&cbBytesNeeded, //������������ܷ�������ķ���
		&ServicesReturned, //������������ܷ��ط��������
		&ResumeHandle); //���������������һ�ε��ñ���Ϊ0������Ϊ0����ɹ�
	if (ESS == NULL)
	{
		cout << "EnumServicesStatus" << endl;
		return -1;
	}
	for (int i = 0; i < ServicesReturned; i++)
	{
		if (strstr(service_status[i].lpDisplayName, "Virtual Machine") != NULL) return false;
	}
	//�رշ���������ľ��
	CloseServiceHandle(SCMan);
	return true;
}
bool CheckVB_service()
{
	int menu = 0;
	//��ϵͳ���������
	SC_HANDLE SCMan = OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE);
	if (SCMan == NULL)
	{
		cout << GetLastError() << endl
			<< "OpenSCManager Error" << endl;
		return -1;
	}
	//����ϵͳ����Ľṹ
	LPENUM_SERVICE_STATUSA service_status;
	DWORD cbBytesNeeded = NULL;
	DWORD ServicesReturned = NULL;
	DWORD ResumeHandle = NULL;
	service_status = (LPENUM_SERVICE_STATUSA)LocalAlloc(LPTR, 1024 * 64);
	//��ȡϵͳ����ļ���Ϣ
	bool ESS = EnumServicesStatusA(SCMan, //ϵͳ������
		SERVICE_WIN32, //���������
		SERVICE_STATE_ALL, //�����״̬
		(LPENUM_SERVICE_STATUSA)service_status, //���������ϵͳ����Ľṹ
		1024 * 64, //�ṹ�Ĵ�С
		&cbBytesNeeded, //������������ܷ�������ķ���
		&ServicesReturned, //������������ܷ��ط��������
		&ResumeHandle); //���������������һ�ε��ñ���Ϊ0������Ϊ0����ɹ�
	if (ESS == NULL)
	{
		cout << "EnumServicesStatus Error" << endl;
		return -1;
	}
	for (int i = 0; i < ServicesReturned; i++)
	{
		if (strstr(service_status[i].lpDisplayName, "VirtualBox Guest") != NULL) return false;
	}
	//�رշ���������ľ��
	CloseServiceHandle(SCMan);
	return true;
}
bool ServiceDetect()
{
	printf("Service Detect......");
	bool answer1_service = CheckVM_service();
	bool answer2_service = CheckVirtualPC_service();
	bool answer3_service = CheckVB_service();
	printf("       Done.\n");
	if (answer1_service == false || answer2_service == false || answer3_service == false) return false;
	else return true;
}