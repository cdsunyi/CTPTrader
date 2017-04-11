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


//��ʼ����Լ����ֵ(�ɸ��ݺ�Լ��ʵ�������仯) ����޸�ͬʱ�޸������ļ� ALLINSTRUMENTNUMBER ֵ
#define ALLINSTRUMENTNUMBER_TD 10000

extern CThostFtdcTraderApi* pUserApi;
// ǰ�õ�ַ
extern char FRONT_ADDR[];		
// ������
extern int iRequestID;
//��Լ
extern char* p_TMInstrumentID[];
//��Լ��
extern int p_InstrumentNum;

//��Լ test
//extern multiset <string> TraderInstrumentID_test;

TThostFtdcBrokerIDType	BROKER_ID = "2358";				// ���͹�˾����
TThostFtdcInvestorIDType INVESTOR_ID = "590195425";			// Ͷ���ߴ���
TThostFtdcPasswordType  PASSWORD = "095891";			// �û�����



TraderSqi::TraderSqi()
{
	//instrument numbers
	traderInstrumentNum = 0;

	//log info
	this->log_TD.setlogType("Trader------>:");

	//TraderInstrumentID
}

///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
void TraderSqi::OnFrontConnected()
{
	CThostFtdcReqUserLoginField logininfo;
	memset(&logininfo, 0, sizeof(logininfo));
	strcpy_s(logininfo.UserID, sizeof(TThostFtdcUserIDType), INVESTOR_ID);
	strcpy_s(logininfo.BrokerID, sizeof(TThostFtdcBrokerIDType), BROKER_ID);
	strcpy_s(logininfo.Password, sizeof(TThostFtdcPasswordType), PASSWORD);
	pUserApi->ReqUserLogin(&logininfo, iRequestID++);

}

///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
///@param nReason ����ԭ��
///        0x1001 �����ʧ��
///        0x1002 ����дʧ��
///        0x2001 ����������ʱ
///        0x2002 ��������ʧ��
///        0x2003 �յ�������
void TraderSqi::OnFrontDisconnected(int nReason)
{
	//cout << "OnFrontDisconnected----�ѶϿ�" << endl;
	log_TD.log("OnFrontDisconnected----�ѶϿ�");
}

///��¼������Ӧ
void TraderSqi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo->ErrorID == 0)
	{
		//cout << "OnRspUserLogin -----��¼�ɹ�" << endl;
		log_TD.log("OnRspUserLogin -----��¼�ɹ�");
		CThostFtdcQryInstrumentField Instrument;
		memset(&Instrument, 0, sizeof(Instrument));
		int result = pUserApi->ReqQryInstrument(&Instrument, iRequestID);
		if (result == 0)
		{
			//cout << "���ĺ�Լ�ɹ�" << endl;
			log_TD.log("���ĺ�Լ�ɹ�");
		}
	}
	else
	{
		//cout << "OnRspUserLogin -----��¼ʧ��" << endl;
		log_TD.log("OnRspUserLogin -----��¼ʧ��");
	}
}

///�ǳ�������Ӧ
void TraderSqi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	//cout << "OnRspUserLogout -----�û��ѵǳ�" << endl;
	log_TD.log("OnRspUserLogout -----�û��ѵǳ�");
}


///�����ѯ��Լ��Ӧ
void TraderSqi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	traderInstrumentNum++;

	//�洢��Լ
	setTraderInstrumentIDinfo(pInstrument->InstrumentID);
	//��Լ test
	//TraderInstrumentID_test.insert(pInstrument->InstrumentID);

	if (bIsLast)
	{
		//cout << "�����ѯ��Լ����" << traderInstrumentNum << endl;

		trasition intTostr;
		string str = "�����ѯ��Լ����" + intTostr.intToString(traderInstrumentNum);
		log_TD.log(str);
		//Sleep(1000);

		vector<string>::iterator it;
		//���غ�Լ��Ϣ
		vector<string> vec = getTraderInstrumentIDinfo();

		int j = 0;
		char s[ALLINSTRUMENTNUMBER_TD][31];
		for (it = vec.begin(); it != vec.end(); it++)
		{
			//cout << *it << endl;


			for (int i = 0; i < (*it).length(); i++)
				s[j][i] = (*it)[i];
			s[j][(*it).length()] = '\0';

			p_TMInstrumentID[j] = &s[j][0];
			j++;
		}
		p_InstrumentNum = traderInstrumentNum;

		//����Լ��Ϣд��instrumentfile.txt�ļ�
		OpreationFile instrumentfile;
		fstream instrumentfiletxt;
		//�жϴ��ļ��Ƿ�ɹ�

		if (!instrumentfile.openfile(instrumentfiletxt, "instrumentfile.txt"))
		{
			log_TD.log("instrumentfile.txt�ļ���ʧ�ܣ�");
		}

		//����
		sort(vec.begin(), vec.end(), less<string>());
		for (it = vec.begin(); it != vec.end(); it++)
		{
			//д���ļ���Ϣ
			instrumentfile.writeInfo(instrumentfiletxt, *it);
		}

		//�ر��ļ�
		instrumentfile.closefile(instrumentfiletxt);

	}

}

///����Ӧ��
void TraderSqi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	//cerr << "--->>> " << "OnRspError" << endl;
	//cout << pRspInfo->ErrorID << "," << pRspInfo->ErrorMsg << endl;
	trasition intTostr;

	string logstr = "OnRspError:" + intTostr.intToString(pRspInfo->ErrorID) + "," + (string)(pRspInfo->ErrorMsg);
	log_TD.log(logstr);
}

///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
void TraderSqi::OnHeartBeatWarning(int nTimeLapse)
{

}

//���ú�Լ��Ϣ
void TraderSqi::setTraderInstrumentIDinfo(TThostFtdcInstrumentIDType instrument)
{
	TraderInstrumentID.push_back(instrument);
}

//���غ�Լ��Ϣ
vector <string> TraderSqi::getTraderInstrumentIDinfo()
{
	return TraderInstrumentID;
}

int TraderSqi::compare( void *a,  void *b)
{
	char *s1 = (char *)a;
	char *s2 = (char *)b;
	return strcmp(s1, s2);
}