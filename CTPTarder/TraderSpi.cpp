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
* 2017/03/07     石小林              创建
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
#include "stdafx.h"
#include "TraderSpi.h"


//初始化合约总量值(可根据合约的实际总量变化) 如果修改同时修改其他文件 ALLINSTRUMENTNUMBER 值
#define ALLINSTRUMENTNUMBER_TD 10000

extern CThostFtdcTraderApi* pUserApi;
// 前置地址
extern char FRONT_ADDR[];		
// 请求编号
extern int iRequestID;
//合约
extern char* p_TMInstrumentID[];
//合约数
extern int p_InstrumentNum;

//合约 test
//extern multiset <string> TraderInstrumentID_test;

TThostFtdcBrokerIDType	BROKER_ID = "2358";				// 经纪公司代码
TThostFtdcInvestorIDType INVESTOR_ID = "590195425";			// 投资者代码
TThostFtdcPasswordType  PASSWORD = "095891";			// 用户密码



TraderSqi::TraderSqi()
{
	//instrument numbers
	traderInstrumentNum = 0;

	//log info
	this->log_TD.setlogType("Trader------>:");

	//TraderInstrumentID
}

///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
void TraderSqi::OnFrontConnected()
{
	CThostFtdcReqUserLoginField logininfo;
	memset(&logininfo, 0, sizeof(logininfo));
	strcpy_s(logininfo.UserID, sizeof(TThostFtdcUserIDType), INVESTOR_ID);
	strcpy_s(logininfo.BrokerID, sizeof(TThostFtdcBrokerIDType), BROKER_ID);
	strcpy_s(logininfo.Password, sizeof(TThostFtdcPasswordType), PASSWORD);
	pUserApi->ReqUserLogin(&logininfo, iRequestID++);

}

///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
///@param nReason 错误原因
///        0x1001 网络读失败
///        0x1002 网络写失败
///        0x2001 接收心跳超时
///        0x2002 发送心跳失败
///        0x2003 收到错误报文
void TraderSqi::OnFrontDisconnected(int nReason)
{
	//cout << "OnFrontDisconnected----已断开" << endl;
	log_TD.log("OnFrontDisconnected----已断开");
}

///登录请求响应
void TraderSqi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo->ErrorID == 0)
	{
		//cout << "OnRspUserLogin -----登录成功" << endl;
		log_TD.log("OnRspUserLogin -----登录成功");
		CThostFtdcQryInstrumentField Instrument;
		memset(&Instrument, 0, sizeof(Instrument));
		int result = pUserApi->ReqQryInstrument(&Instrument, iRequestID);
		if (result == 0)
		{
			//cout << "订阅合约成功" << endl;
			log_TD.log("订阅合约成功");
		}
	}
	else
	{
		//cout << "OnRspUserLogin -----登录失败" << endl;
		log_TD.log("OnRspUserLogin -----登录失败");
	}
}

///登出请求响应
void TraderSqi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	//cout << "OnRspUserLogout -----用户已登出" << endl;
	log_TD.log("OnRspUserLogout -----用户已登出");
}


///请求查询合约响应
void TraderSqi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	traderInstrumentNum++;

	//存储合约
	setTraderInstrumentIDinfo(pInstrument->InstrumentID);
	//合约 test
	//TraderInstrumentID_test.insert(pInstrument->InstrumentID);

	if (bIsLast)
	{
		//cout << "请求查询合约数：" << traderInstrumentNum << endl;

		trasition intTostr;
		string str = "请求查询合约数：" + intTostr.intToString(traderInstrumentNum);
		log_TD.log(str);
		//Sleep(1000);

		vector<string>::iterator it;
		//返回合约信息
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

		//将合约信息写入instrumentfile.txt文件
		OpreationFile instrumentfile;
		fstream instrumentfiletxt;
		//判断打开文件是否成功

		if (!instrumentfile.openfile(instrumentfiletxt, "instrumentfile.txt"))
		{
			log_TD.log("instrumentfile.txt文件打开失败！");
		}

		//排序
		sort(vec.begin(), vec.end(), less<string>());
		for (it = vec.begin(); it != vec.end(); it++)
		{
			//写入文件信息
			instrumentfile.writeInfo(instrumentfiletxt, *it);
		}

		//关闭文件
		instrumentfile.closefile(instrumentfiletxt);

	}

}

///错误应答
void TraderSqi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	//cerr << "--->>> " << "OnRspError" << endl;
	//cout << pRspInfo->ErrorID << "," << pRspInfo->ErrorMsg << endl;
	trasition intTostr;

	string logstr = "OnRspError:" + intTostr.intToString(pRspInfo->ErrorID) + "," + (string)(pRspInfo->ErrorMsg);
	log_TD.log(logstr);
}

///心跳超时警告。当长时间未收到报文时，该方法被调用。
///@param nTimeLapse 距离上次接收报文的时间
void TraderSqi::OnHeartBeatWarning(int nTimeLapse)
{

}

//设置合约信息
void TraderSqi::setTraderInstrumentIDinfo(TThostFtdcInstrumentIDType instrument)
{
	TraderInstrumentID.push_back(instrument);
}

//返回合约信息
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