/***********************************************************************
* ����:
* ���ļ����ڵ�Ŀ��
*
*
*
* ȫ�ֱ���:
* ���ļ��������Ҫȫ�ֱ���
*
*
*
*
*
* ����:
* ʹ�ô��ļ�Ӧ��Ҫע��ĵط�
*
* �޸���ʷ:
* ����          �޸���             �޸�����
* 2017/03/07     ʯС��              ����
*
*
*
*
*
*
* ��������:
* ������������
*
**********************************************************************
***                                                                ***
***            ��Ȩ����  �㷢�ڻ����޹�˾ 2010~1016                 ***
***                                                                ***
***      �������������İ汾���ڹ㷢�ڻ����κζԱ������ʹ�û򿽱�   ***
***    ��Ҫ�õ��㷢�ڻ���������ɣ�������㷢�ڻ���ǩ���ĺ�ͬ������   ***
***    ������������Ȩ���                                       ***
***                                                                ***
**********************************************************************/
#include "stdafx.h"
#include "TraderSpi.h"
#include "MdSpi.h"

//��ʼ����Լ����ֵ(�ɸ��ݺ�Լ��ʵ�������仯) ����޸�ͬʱ�޸������ļ� ALLINSTRUMENTNUMBER_TD ֵ
#define ALLINSTRUMENTNUMBER 10000

// UsertraderApi����
CThostFtdcTraderApi* pUserApi;
//// UsermdApi����
CThostFtdcMdApi* pUserMdApi;
//��ʼ����Լ
char* p_TMInstrumentID[ALLINSTRUMENTNUMBER];
//��ʼ���ĺ�Լ��ֵ

//��ʼ����Լ��
int p_InstrumentNum = 0;
//�����ַ
char FRONT_ADDR_MD[] = "tcp://ctpsim-front01.gfqh.cn:42213 ";
//���׵�ַ
char FRONT_ADDR[] = "tcp://192.168.71.21:42205";
// ������
int iRequestID = 0;
// ����������
int iRequestID_md = 0;

//��Լ test
//multiset <string> TraderInstrumentID_test;

int main(int argc, char* argv[])
{
	//���ײ���
	TraderSqi* sqi = new TraderSqi();
	pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();			// ����UserApi
	pUserApi->RegisterSpi((CThostFtdcTraderSpi*)sqi);
	pUserApi->SubscribePublicTopic(THOST_TERT_RESTART);				// ע�ṫ����
	pUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);				// ע��˽����
	pUserApi->RegisterFront(FRONT_ADDR);							// connect
	pUserApi->Init();

	//pUserApi->Join();
	//	pUserApi->Release();


	//���鲿��
	// ��ʼ��UserApi
	pUserMdApi = CThostFtdcMdApi::CreateFtdcMdApi();			// ����UserApi
	CThostFtdcMdSpi* pUserMdSpi = new MdSpi();
	pUserMdApi->RegisterSpi(pUserMdSpi);						// ע���¼���
	pUserMdApi->RegisterFront(FRONT_ADDR_MD);					// connect
	pUserMdApi->Init();

	pUserMdApi->Join();


	////	pUserMdApi->Release();

	/*char *test[100];
	string ss[3] = { "ccc", "bbb", "aaa" };
	char s[3][20];
	for (int i = 0; i < 3; i++)
	{

	for (int j = 0; j < ss[i].length(); j++)
	s[i][j] = ss[i][j];
	s[i][ss[i].length()] = '\0';


	test[i] = &s[i][0];
	}

	for (int j = 0; j < 3;j++)
	{
	cout << test[j] << endl;
	}*/



	return 0;

}



