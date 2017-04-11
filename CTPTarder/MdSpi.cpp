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

//��ȡ��������
int getMarketnum = 0;

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
			Sleep(1000);
		}
		//char* p_TMInstrumentID_test[] = {"IF1706","IF1709","IF1704","IF1705","IH1705","IC1705"};
		// ����������
		pUserMdApi->SubscribeMarketData(p_TMInstrumentID, p_InstrumentNum);

	}
}

///�ǳ�������Ӧ
void MdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	log_Md.log("OnRspUserLogout----ϵͳ�Ѿ��ǳ���");
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
	log_Md.log("OnRspUnSubMarketData-----���鶩���Ѿ�ȡ����");
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
	//log_Md.log("�������֪ͨ");
	getMarketnum++;
	///������
	string	TradingDay = pDepthMarketData->TradingDay;
	///��Լ����
	string	InstrumentID = pDepthMarketData->InstrumentID;
	///����������
	string	ExchangeID = pDepthMarketData->ExchangeID;
	///��Լ�ڽ������Ĵ���
	string	ExchangeInstID = pDepthMarketData->ExchangeInstID;
	///���¼�
	double	LastPrice = (pDepthMarketData->LastPrice > 1000000000000000) ? 0 : pDepthMarketData->LastPrice;
	///�ϴν����
	double	PreSettlementPrice = (pDepthMarketData->PreSettlementPrice> 1000000000000000) ? 0 : pDepthMarketData->PreSettlementPrice;
	///������
	double	PreClosePrice = (pDepthMarketData->PreClosePrice> 1000000000000000) ? 0 : pDepthMarketData->PreClosePrice;
	///��ֲ���
	double	PreOpenInterest = (pDepthMarketData->PreOpenInterest> 1000000000000000) ? 0 : pDepthMarketData->PreOpenInterest;
	///����
	double	OpenPrice = (pDepthMarketData->OpenPrice> 1000000000000000) ? 0 : pDepthMarketData->OpenPrice;
	///��߼�
	double	HighestPrice = (pDepthMarketData->HighestPrice> 1000000000000000) ? 0 : pDepthMarketData->HighestPrice;
	///��ͼ�
	double	LowestPrice = (pDepthMarketData->LowestPrice > 1000000000000000) ? 0 : pDepthMarketData->LowestPrice;
	///����
	int	Volume = pDepthMarketData->Volume> 1000000000000000;
	///�ɽ����
	double	Turnover = (pDepthMarketData->Turnover> 1000000000000000) ? 0 : pDepthMarketData->Turnover;
	///�ֲ���
	double	OpenInterest = (pDepthMarketData->OpenInterest> 1000000000000000) ? 0 : pDepthMarketData->OpenInterest;
	///������
	double	ClosePrice = (pDepthMarketData->ClosePrice> 1000000000000000) ? 0 : pDepthMarketData->ClosePrice;
	///���ν����
	double	SettlementPrice = (pDepthMarketData->SettlementPrice> 1000000000000000) ? 0 : pDepthMarketData->SettlementPrice;
	///��ͣ���
	double	UpperLimitPrice = (pDepthMarketData->UpperLimitPrice> 1000000000000000) ? 0 : pDepthMarketData->UpperLimitPrice;
	///��ͣ���
	double	LowerLimitPrice = (pDepthMarketData->LowerLimitPrice> 1000000000000000) ? 0 : pDepthMarketData->LowerLimitPrice;
	///����ʵ��
	double	PreDelta = (pDepthMarketData->PreDelta> 1000000000000000) ? 0 : pDepthMarketData->PreDelta;
	///����ʵ��
	double	CurrDelta = (pDepthMarketData->CurrDelta> 1000000000000000) ? 0 : pDepthMarketData->CurrDelta;
	///����޸�ʱ��
	string	UpdateTime = pDepthMarketData->UpdateTime;
	///����޸ĺ���
	int	UpdateMillisec = pDepthMarketData->UpdateMillisec;
	///�����һ
	double	BidPrice1 = (pDepthMarketData->BidPrice1> 1000000000000000) ? 0 : pDepthMarketData->BidPrice1;
	///������һ
	int	BidVolume1 = pDepthMarketData->BidVolume1;
	///������һ
	double	AskPrice1 = (pDepthMarketData->AskPrice1> 1000000000000000) ? 0 : pDepthMarketData->AskPrice1;
	///������һ
	int	AskVolume1 = pDepthMarketData->AskVolume1;
	///����۶�
	double	BidPrice2 = (pDepthMarketData->BidPrice2> 1000000000000000) ? 0 : pDepthMarketData->BidPrice2;
	///��������
	int	BidVolume2 = pDepthMarketData->BidVolume2;
	///�����۶�
	double	AskPrice2 = (pDepthMarketData->AskPrice2> 1000000000000000) ? 0 : pDepthMarketData->AskPrice2;
	///��������
	int	AskVolume2 = pDepthMarketData->AskVolume2;
	///�������
	double	BidPrice3 = (pDepthMarketData->BidPrice3> 1000000000000000) ? 0 : pDepthMarketData->BidPrice3;
	///��������
	int	BidVolume3 = pDepthMarketData->BidVolume3;
	///��������
	double	AskPrice3 = (pDepthMarketData->AskPrice3> 1000000000000000) ? 0 : pDepthMarketData->AskPrice3;
	///��������
	int	AskVolume3 = pDepthMarketData->AskVolume3;
	///�������
	double	BidPrice4 = (pDepthMarketData->BidPrice4> 1000000000000000) ? 0 : pDepthMarketData->BidPrice4;
	///��������
	int	BidVolume4 = pDepthMarketData->BidVolume4;
	///��������
	double	AskPrice4 = (pDepthMarketData->AskPrice4> 1000000000000000) ? 0 : pDepthMarketData->AskPrice4;
	///��������
	int	AskVolume4 = pDepthMarketData->AskVolume4;
	///�������
	double	BidPrice5 = (pDepthMarketData->BidPrice5> 1000000000000000) ? 0 : pDepthMarketData->BidPrice5;
	///��������
	int	BidVolume5 = pDepthMarketData->BidVolume5;
	///��������
	double	AskPrice5 = (pDepthMarketData->AskPrice5> 1000000000000000) ? 0 : pDepthMarketData->AskPrice5;
	///��������
	int	AskVolume5 = pDepthMarketData->AskVolume5;
	///���վ���
	double	AveragePrice = (pDepthMarketData->AveragePrice> 1000000000000000) ? 0 : pDepthMarketData->AveragePrice;
	///ҵ������
	string	ActionDay = pDepthMarketData->ActionDay;


	SYSTEMTIME folder;
	GetLocalTime(&folder);
	stringstream streamFolder;
	char folderpath[100];
	streamFolder << "data\\" << folder.wYear << setw(2) << setfill('0') << folder.wMonth << setw(2) << setfill('0') << folder.wDay;
	streamFolder >> folderpath;

	_mkdir("data");
	_mkdir(folderpath);	 //����������ݵ��ļ��У�����ļ��д����򲻴���������������򴴽���

	//intת string
	trasition trasition;
	string str = trasition.intToString(getMarketnum) + ", "+ InstrumentID ;

	string InstrumentIDdir =  "\\" + InstrumentID+".txt";
	//д���ļ�
	fstream writefile(folderpath + InstrumentIDdir, ios_base::out | ios_base::app);
	if (!writefile.fail())
	{
		writefile.setf(ios::left);
		writefile << fixed<<setprecision(2);
		writefile << setw(9) << log_Md.gethour() + ": "
			<< setw(18) << pDepthMarketData->InstrumentID << ", "
			<< setw(15) << LastPrice << ", "
			<< setw(15) << PreSettlementPrice << ", "
			<< setw(15) << PreClosePrice << ", "
			<< setw(15) << PreOpenInterest << ", "
			<< setw(15) << OpenPrice << ", "
			<< setw(15) << HighestPrice << ", "
			<< setw(15) << LowestPrice << ", "
			<< setw(15) << Volume << ", "
			<< setw(15) << Turnover << ", "
			<< setw(15) << OpenInterest << ", "
			<< setw(15) << ClosePrice << ", "
			<< setw(15) << SettlementPrice << ", "
			<< setw(15) << UpperLimitPrice << ", "
			<< setw(15) << LowerLimitPrice << ", "
			<< setw(15) << PreDelta << ", "
			<< setw(15) << CurrDelta << ", "
			<< setw(15) << UpdateTime << ", "
			<< setw(15) << UpdateMillisec << ", "
			<< setw(15) << BidPrice1 << ", "
			<< setw(15) << BidVolume1 << ", "
			<< setw(15) << AskPrice1 << ", "
			<< setw(15) << AskVolume1 << ", "
			<< setw(15) << BidPrice2 << ", "
			<< setw(15) << BidVolume2 << ", "
			<< setw(15) << AskPrice2 << ", "
			<< setw(15) << AskVolume2 << ", "
			<< setw(15) << BidPrice3 << ", "
			<< setw(15) << BidVolume3 << ", "
			<< setw(15) << AskPrice3 << ", "
			<< setw(15) << AskVolume3 << ", "
			<< setw(15) << BidPrice4 << ", "
			<< setw(15) << BidVolume4 << ", "
			<< setw(15) << AskPrice4 << ", "
			<< setw(15) << AskVolume4 << ", "
			<< setw(15) << BidVolume5 << ", "
			<< setw(15) << AskPrice5 << ", "
			<< setw(15) << AskVolume5 << ", "
			<< setw(15) << AveragePrice << ", "
			<< setw(15) << ActionDay
			<< endl;

		/*writefile << setw(9) << trasition.intToString(getMarketnum) + ": "
			<< setw(18) << pDepthMarketData->InstrumentID << ", "
			<< setw(15) << "���¼�:" << LastPrice << ", "
			<< setw(15) <<  "�ϴν����:" << PreSettlementPrice << ", "
			<< setw(15) << "������:"  << PreClosePrice << ", "
			<< setw(15) << "��ֲ���:"  << PreOpenInterest << ", "
			<< setw(15) << "����:"  << OpenPrice << ", "
			<< setw(15) << "��߼�:" << HighestPrice << ", "
			<< setw(15) << "��ͼ�:" << LowestPrice << ", "
			<< setw(15) << "����:" << Volume << ", "
			<< setw(15) << "�ɽ����:" << Turnover << ", "
			<< setw(15) << "�ֲ���:" << OpenInterest << ", "
			<< setw(15) << "������:" << ClosePrice << ", "
			<< setw(15) << "���ν����:" << SettlementPrice << ", "
			<< setw(15) << "��ͣ���:" << UpperLimitPrice << ", "
			<< setw(15) << "��ͣ���:" << LowerLimitPrice << ", "
			<< setw(15) << "����ʵ��:" << PreDelta << ", "
			<< setw(15) << "����ʵ��:" << CurrDelta << ", "
			<< setw(15) << "����޸�ʱ��:" << UpdateTime << ", "
			<< setw(15) << "����޸ĺ���:" << UpdateMillisec << ", "
			<< setw(15) << "�����һ:" << BidPrice1 << ", "
			<< setw(15) << "������һ:" << BidVolume1 << ", "
			<< setw(15) << "������һ:" << AskPrice1 << ", "
			<< setw(15) << "������һ:" << AskVolume1 << ", "
			<< setw(15) << ":" << BidPrice2 << ", "
			<< setw(15) << ":" << BidVolume2 << ", "
			<< setw(15) << ":" << AskPrice2 << ", "
			<< setw(15) << ":" << AskVolume2 << ", "
			<< setw(15) << ":" << BidPrice3 << ", "
			<< setw(15) << ":" << BidVolume3 << ", "
			<< setw(15) << ":" << AskPrice3 << ", "
			<< setw(15) << ":" << AskVolume3 << ", "
			<< setw(15) << ":" << BidPrice4 << ", "
			<< setw(15) << ":" << BidVolume4 << ", "
			<< setw(15) << ":" << AskPrice4 << ", "
			<< setw(15) << ":" << AskVolume4 << ", "
			<< setw(15) << ":" << BidVolume5 << ", "
			<< setw(15) << ":" << AskPrice5 << ", "
			<< setw(15) << ":" << AskVolume5 << ", "
			<< setw(15) << ":" << AveragePrice << ", "
			<< setw(15) << "���վ���:" << ActionDay
			<< endl;*/
	}
	else
	{
		log_Md.log("open market file fail!");
	}

	writefile.close();

}

///ѯ��֪ͨ
void MdSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{

}
