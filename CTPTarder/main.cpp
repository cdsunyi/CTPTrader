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
#include "MdSpi.h"

//初始化合约总量值(可根据合约的实际总量变化) 如果修改同时修改其他文件 ALLINSTRUMENTNUMBER_TD 值
#define ALLINSTRUMENTNUMBER 10000

// UsertraderApi对象
CThostFtdcTraderApi* pUserApi;
//// UsermdApi对象
CThostFtdcMdApi* pUserMdApi;
//初始化合约
char* p_TMInstrumentID[ALLINSTRUMENTNUMBER];
//初始化的合约数值

//初始化合约数
int p_InstrumentNum = 0;
//行情地址
char FRONT_ADDR_MD[] = "tcp://ctpsim-front01.gfqh.cn:42213 ";
//交易地址
char FRONT_ADDR[] = "tcp://192.168.71.21:42205";
// 请求编号
int iRequestID = 0;
// 行情请求编号
int iRequestID_md = 0;

//合约 test
//multiset <string> TraderInstrumentID_test;

int main(int argc, char* argv[])
{
	//交易部分
	TraderSqi* sqi = new TraderSqi();
	pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();			// 创建UserApi
	pUserApi->RegisterSpi((CThostFtdcTraderSpi*)sqi);
	pUserApi->SubscribePublicTopic(THOST_TERT_RESTART);				// 注册公有流
	pUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);				// 注册私有流
	pUserApi->RegisterFront(FRONT_ADDR);							// connect
	pUserApi->Init();

	//pUserApi->Join();
	//	pUserApi->Release();


	//行情部分
	// 初始化UserApi
	pUserMdApi = CThostFtdcMdApi::CreateFtdcMdApi();			// 创建UserApi
	CThostFtdcMdSpi* pUserMdSpi = new MdSpi();
	pUserMdApi->RegisterSpi(pUserMdSpi);						// 注册事件类
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



