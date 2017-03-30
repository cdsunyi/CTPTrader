/***********************************************************************
* 描述:
* 此文件用于的目的
*
*
*
* 全局变量:
* 此文件定义的重要全局变量
*
*
*
*
*
* 警告:
* 使用此文件应该要注意的地方
*
* 修改历史:
* 日期          修改人             修改描述
* 20170310     石小林              创建
*
*
*
*
*
*
* 其它事项:
* 有无其它事项
*
**********************************************************************
***                                                                ***
***            版权所有  广发期货有限公司 2010~1016                 ***
***                                                                ***
***      本计算机机程序的版本属于广发期货，任何对本程序的使用或拷贝   ***
***    需要得到广发期货的书面许可，或者与广发期货所签订的合同中已有   ***
***    本程序的相关授权条款。                                       ***
***                                                                ***
**********************************************************************/

#include "MdSpi.h"
#include "TraderSpi.h"


// USER_API参数
extern CThostFtdcMdApi* pUserMdApi;
// 请求编号
extern int iRequestID_md;
//合约
extern char* p_TMInstrumentID[];
extern int p_InstrumentNum;

//合约 test
//extern multiset <string> TraderInstrumentID_test;

TThostFtdcBrokerIDType	BROKER_ID_MD = "2358";				// 经纪公司代码
TThostFtdcInvestorIDType INVESTOR_ID_MD = "590135490";			// 投资者代码
TThostFtdcPasswordType  PASSWORD_MD = "654321";			// 用户密码
//相应的行情合约数量
int oninstumentnum = 0;

MdSpi::MdSpi()
{
	this->log_Md.setlogType("Md---------->:");
}

MdSpi::~MdSpi()
{

}

///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
void MdSpi::OnFrontConnected()
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, sizeof(TThostFtdcBrokerIDType), BROKER_ID_MD);
	strcpy_s(req.UserID, sizeof(TThostFtdcUserIDType), INVESTOR_ID_MD);
	strcpy_s(req.Password, sizeof(TThostFtdcPasswordType), PASSWORD_MD);
	int iResult = pUserMdApi->ReqUserLogin(&req, ++iRequestID_md);
	//cerr << "--->>> 发送用户登录请求: " << ((iResult == 0) ? "行情登录成功" : "行情登录失败") << endl;
	string logstr = "发送用户登录请求: " + (string)((iResult == 0) ? "行情登录成功" : "行情登录失败");
	log_Md.log(logstr);
}

///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
///@param nReason 错误原因
///        0x1001 网络读失败
///        0x1002 网络写失败
///        0x2001 接收心跳超时
///        0x2002 发送心跳失败
///        0x2003 收到错误报文
void MdSpi::OnFrontDisconnected(int nReason)
{
	//cerr << "--->>> " << "OnFrontDisconnected" << endl;
	string logstr = "OnFrontDisconnected";
	log_Md.log(logstr);
}

///心跳超时警告。当长时间未收到报文时，该方法被调用。
///@param nTimeLapse 距离上次接收报文的时间
void MdSpi::OnHeartBeatWarning(int nTimeLapse)
{
	//cerr << "--->>> " << "OnHeartBeatWarning" << endl;
	string logstr = "OnHeartBeatWarning";
	log_Md.log(logstr);
}


///登录请求响应
void MdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	//cerr << "--->>> " << "OnRspUserLogin" << endl;
	if (pRspInfo->ErrorID == 0)
	{
		///获取当前交易日
		string logstr = "获取行情API当前交易日" + (string)(pUserMdApi->GetTradingDay());
		log_Md.log(logstr);

		while (p_InstrumentNum == 0)
		{
			
		}
		// 请求订阅行情
		pUserMdApi->SubscribeMarketData(p_TMInstrumentID, p_InstrumentNum);

	}
}

///登出请求响应
void MdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	log_Md.log("OnRspUserLogout----系统已经登出！");
}

///错误应答
void MdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << "OnRspError" << endl;
	//cout << pRspInfo->ErrorID << "," << pRspInfo->ErrorMsg << endl;
	trasition intTostr;
	
	string logstr = "OnRspError:" + intTostr.intToString(pRspInfo->ErrorID) + "," + (string)(pRspInfo->ErrorMsg);
	log_Md.log(logstr);
}

///订阅行情应答
void MdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	trasition intTostr;
	if (bIsLast)
	{
		log_Md.log("一共响应订阅行情应答数为：" + intTostr.intToString(oninstumentnum));
		//行情写入 txt文件
		/*OpreationFile file;
		fstream textFile;
		if (!file.openfile(textFile, "lack.txt"))
		{
			log_Md.log("lack.txt文件打开失败!");
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
	//log_Md.log("应答"+instrument);

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
	log_Md.log("t.txt文件打开失败!");
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

///取消订阅行情应答
void MdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	log_Md.log("OnRspUnSubMarketData-----行情订阅已经取消！");
}

///订阅询价应答
void MdSpi::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

///取消订阅询价应答
void MdSpi::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

///深度行情通知
void MdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	//log_Md.log("深度行情通知");
	
	///交易日
	string	TradingDay = pDepthMarketData->TradingDay;
	///合约代码
	string	InstrumentID = pDepthMarketData->InstrumentID;
	///交易所代码
	string	ExchangeID = pDepthMarketData->ExchangeID;
	///合约在交易所的代码
	string	ExchangeInstID = pDepthMarketData->ExchangeInstID;
	///最新价
	double	LastPrice = pDepthMarketData->LastPrice;
	///上次结算价
	double	PreSettlementPrice = pDepthMarketData->PreSettlementPrice;
	///昨收盘
	double	PreClosePrice = pDepthMarketData->PreClosePrice;
	///昨持仓量
	double	PreOpenInterest = pDepthMarketData->PreOpenInterest;
	///今开盘
	double	OpenPrice = pDepthMarketData->OpenPrice;
	///最高价
	double	HighestPrice = pDepthMarketData->HighestPrice;
	///最低价
	double	LowestPrice = pDepthMarketData->LowestPrice;
	///数量
	double	Volume = pDepthMarketData->Volume;
	///成交金额
	double	Turnover = pDepthMarketData->Turnover;
	///持仓量
	double	OpenInterest = pDepthMarketData->OpenInterest;
	///今收盘
	double	ClosePrice = pDepthMarketData->ClosePrice;
	///本次结算价
	double	SettlementPrice = pDepthMarketData->SettlementPrice;
	///涨停板价
	double	UpperLimitPrice = pDepthMarketData->UpperLimitPrice;
	///跌停板价
	double	LowerLimitPrice = pDepthMarketData->LowerLimitPrice;
	///昨虚实度
	double	PreDelta = pDepthMarketData->PreDelta;
	///今虚实度
	double	CurrDelta = pDepthMarketData->CurrDelta;
	///最后修改时间
	string	UpdateTime = pDepthMarketData->UpdateTime;
	///最后修改毫秒
	int	UpdateMillisec = pDepthMarketData->UpdateMillisec;
	///申买价一
	double	BidPrice1 = pDepthMarketData->BidPrice1;
	///申买量一
	int	BidVolume1 = pDepthMarketData->BidVolume1;
	///申卖价一
	double	AskPrice1 = pDepthMarketData->AskPrice1;
	///申卖量一
	int	AskVolume1 = pDepthMarketData->AskVolume1;
	///申买价二
	double	BidPrice2 = pDepthMarketData->BidPrice2;
	///申买量二
	int	BidVolume2 = pDepthMarketData->BidVolume2;
	///申卖价二
	double	AskPrice2 = pDepthMarketData->AskPrice2;
	///申卖量二
	int	AskVolume2 = pDepthMarketData->AskVolume2;
	///申买价三
	double	BidPrice3 = pDepthMarketData->BidPrice3;
	///申买量三
	int	BidVolume3 = pDepthMarketData->BidVolume3;
	///申卖价三
	double	AskPrice3 = pDepthMarketData->AskPrice3;
	///申卖量三
	int	AskVolume3 = pDepthMarketData->AskVolume3;
	///申买价四
	double	BidPrice4 = pDepthMarketData->BidPrice4;
	///申买量四
	int	BidVolume4 = pDepthMarketData->BidVolume4;
	///申卖价四
	double	AskPrice4 = pDepthMarketData->AskPrice4;
	///申卖量四
	int	AskVolume4 = pDepthMarketData->AskVolume4;
	///申买价五
	double	BidPrice5 = pDepthMarketData->BidPrice5;
	///申买量五
	int	BidVolume5 = pDepthMarketData->BidVolume5;
	///申卖价五
	double	AskPrice5 = pDepthMarketData->AskPrice5;
	///申卖量五
	int	AskVolume5 = pDepthMarketData->AskVolume5;
	///当日均价
	double	AveragePrice = pDepthMarketData->AveragePrice;
	///业务日期
	string	ActionDay = pDepthMarketData->ActionDay;
	

	OpreationFile Marketfile;
	fstream Mkfile;
	Marketfile.openfile(Mkfile,"market.txt");
	Marketfile.writeInfo(Mkfile, info);
	Marketfile.closefile(Mkfile);

}

///询价通知
void MdSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{

}
