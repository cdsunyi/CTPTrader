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

}

///询价通知
void MdSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{

}
