#include "stdafx.h"
#include<wtypes.h>
#include<nb30.h>
#include<wincon.h>
#pragma comment(lib,"netapi32.lib")
using namespace std;
typedef struct _ASTAT_ //������������Ϣ�Ľṹ��
{
	ADAPTER_STATUS adapt; //����������״̬
	NAME_BUFFER NameBuff[30]; //���ֱ�
} ASTAT, *PASTAT;
void get_3part_mac(string &mac)
{
	NCB Ncb; //����һ��NCB��������ƿ飩���͵Ľṹ�����Ncb
	ASTAT Adapter;
	UCHAR uRetCode; //ִ��Netbios()�����ķ���ֵ
	LANA_ENUM lenum; //����ṹ�壬���mac��ַ
	memset(&Ncb, 0, sizeof(Ncb));
	Ncb.ncb_command = NCBENUM; //ͳ��ϵͳ������������
	Ncb.ncb_buffer = (UCHAR *)&lenum; //ncb_bufferָ����LANA_ENUM�ṹ���Ļ�����
	Ncb.ncb_length = sizeof(lenum);
	uRetCode = Netbios(&Ncb); //��ȡ�������к�
	for (int i = 0; i < lenum.length; i++) //��ÿһ�����������������Ϊ�����ţ���ȡmac��ַ
	{
		memset(&Ncb, 0, sizeof(Ncb));
		Ncb.ncb_command = NCBRESET; //����������NCBRESET������г�ʼ��
		Ncb.ncb_lana_num = lenum.lana[i]; //ָ��������
		uRetCode = Netbios(&Ncb);
		memset(&Ncb, 0, sizeof(Ncb));
		Ncb.ncb_command = NCBASTAT; //����������NCBSTAT�����ȡ������Ϣ
		Ncb.ncb_lana_num = lenum.lana[i];
		strcpy_s((char *)Ncb.ncb_callname,10, "*"); //Զ��ϵͳ����ֵΪ*
		Ncb.ncb_buffer = (unsigned char *)&Adapter; //ָ�����ص���Ϣ��ŵı���
		Ncb.ncb_length = sizeof(Adapter);
		uRetCode = Netbios(&Ncb); //���ŷ���NCBSTAT����Ի�ȡ������Ϣ
		//������MAC��ַ��ʽת��Ϊ����16���ƣ�������ַ���mac��
		if (uRetCode == 0)
		{
			char tmp[128]; 
			sprintf_s(tmp,128, "%02x-%02x-%02x",
				Adapter.adapt.adapter_address[0],
				Adapter.adapt.adapter_address[1],
				Adapter.adapt.adapter_address[2]
			);
			mac = tmp;
		}
	}
}
bool CheckVMWare()
{
	string mac;
	get_3part_mac(mac);
	if (mac == "00-05-69" || mac == "00-0c-29" || mac == "00-50-56")
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool CheckVirtualPC()
{
	string mac;
	get_3part_mac(mac);
	if (mac == "00-03-ff")
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool CheckVirtualBox()
{
	string mac;
	get_3part_mac(mac);
	if (mac == "08-00-27")
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool CheckVirtualMachine()
{
	printf("MacDetect......");
	bool answer1 = CheckVirtualPC();
	bool answer2 = CheckVMWare();
	bool answer3 = CheckVirtualBox();
	printf("            Done.\n");
	if (answer1 == false || answer2 == false || answer3 == false) return false;
	else return true;
}