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
* 20170310     ʯС��              ����
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

#include "MdSpi.h"
#include "TraderSpi.h"


// USER_API����
extern CThostFtdcMdApi* pUserMdApi;
// ������
extern int iRequestID_md;
//��Լ
extern char* p_TMInstrumentID[];
extern int p_InstrumentNum;

//��Լ test
//extern multiset <string> TraderInstrumentID_test;

TThostFtdcBrokerIDType	BROKER_ID_MD = "2358";				// ���͹�˾����
TThostFtdcInvestorIDType INVESTOR_ID_MD = "590135490";			// Ͷ���ߴ���
TThostFtdcPasswordType  PASSWORD_MD = "654321";			// �û�����
//��Ӧ�������Լ����
int oninstumentnum = 0;

MdSpi::MdSpi()
{
	this->log_Md.setlogType("Md---------->:");
}

MdSpi::~MdSpi()
{

}

///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
void MdSpi::OnFrontConnected()
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, sizeof(TThostFtdcBrokerIDType), BROKER_ID_MD);
	strcpy_s(req.UserID, sizeof(TThostFtdcUserIDType), INVESTOR_ID_MD);
	strcpy_s(req.Password, sizeof(TThostFtdcPasswordType), PASSWORD_MD);
	int iResult = pUserMdApi->ReqUserLogin(&req, ++iRequestID_md);
	//cerr << "--->>> �����û���¼����: " << ((iResult == 0) ? "�����¼�ɹ�" : "�����¼ʧ��") << endl;
	string logstr = "�����û���¼����: " + (string)((iResult == 0) ? "�����¼�ɹ�" : "�����¼ʧ��");
	log_Md.log(logstr);
}

///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
///@param nReason ����ԭ��
///        0x1001 �����ʧ��
///        0x1002 ����дʧ��
///        0x2001 ����������ʱ
///        0x2002 ��������ʧ��
///        0x2003 �յ�������
void MdSpi::OnFrontDisconnected(int nReason)
{
	//cerr << "--->>> " << "OnFrontDisconnected" << endl;
	string logstr = "OnFrontDisconnected";
	log_Md.log(logstr);
}

///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
void MdSpi::OnHeartBeatWarning(int nTimeLapse)
{
	//cerr << "--->>> " << "OnHeartBeatWarning" << endl;
	string logstr = "OnHeartBeatWarning";
	log_Md.log(logstr);
}


///��¼������Ӧ
void MdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	//cerr << "--->>> " << "OnRspUserLogin" << endl;
	if (pRspInfo->ErrorID == 0)
	{
		///��ȡ��ǰ������
		string logstr = "��ȡ����API��ǰ������" + (string)(pUserMdApi->GetTradingDay());
		log_Md.log(logstr);

		while (p_InstrumentNum == 0)
		{
			
		}
		// ����������
		pUserMdApi->SubscribeMarketData(p_TMInstrumentID, p_InstrumentNum);

	}
}

///�ǳ�������Ӧ
void MdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

///����Ӧ��
void MdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << "OnRspError" << endl;
	//cout << pRspInfo->ErrorID << "," << pRspInfo->ErrorMsg << endl;
	trasition intTostr;
	
	string logstr = "OnRspError:" + intTostr.intToString(pRspInfo->ErrorID) + "," + (string)(pRspInfo->ErrorMsg);
	log_Md.log(logstr);
}

///��������Ӧ��
void MdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	trasition intTostr;
	if (bIsLast)
	{
		log_Md.log("һ����Ӧ��������Ӧ����Ϊ��" + intTostr.intToString(oninstumentnum));
		//����д�� txt�ļ�
		/*OpreationFile file;
		fstream textFile;
		if (!file.openfile(textFile, "lack.txt"))
		{
			log_Md.log("lack.txt�ļ���ʧ��!");
		}
		multiset <string>::iterator it;
		for (it = TraderInstrumentID_test.begin(); it != TraderInstrumentID_test.end();it++)
		{
			file.writeInfo(textFile, *it);
		}
		file.writeInfo(textFile, "**********************************");
		file.closefile(textFile);*/
	}
	string instrument = pSpecificInstrument->InstrumentID;
	//log_Md.log("Ӧ��"+instrument);

	//test
	/*int tSize = TraderInstrumentID_test.size();

	multiset <string> ::iterator p;

	p = TraderInstrumentID_test.find(instrument);

	if (p == TraderInstrumentID_test.end())
	{
	OpreationFile file;
	fstream textFile;
	if (!file.openfile(textFile, "t.txt"))
	{
	log_Md.log("t.txt�ļ���ʧ��!");
	}
	file.writeInfo(textFile, instrument);
	file.closefile(textFile);
	}
	else
	{
	TraderInstrumentID_test.erase(instrument);
	}*/

	oninstumentnum++;
}

///ȡ����������Ӧ��
void MdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

///����ѯ��Ӧ��
void MdSpi::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

///ȡ������ѯ��Ӧ��
void MdSpi::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

///�������֪ͨ
void MdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{

}

///ѯ��֪ͨ
void MdSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{

}
