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
* 20170313     石小林              创建
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

#include "ctpLog.h"


//log文件夹地址
extern string logFolderPathStr;
//log文件TXT地址
extern string logTxtPathStr;

ctpLog::ctpLog() :logType("")
{
	//string 转 const * char 型 logpathstr -> logpathstr.c_str()
	_mkdir(logFolderPathStr.c_str());	 //创建存放数据的文件夹，如果文件夹存在则不创建，如果不存在则创建；
}

//ctpLog::ctpLog(string ctplogType)
//{
//	this->logType = ctplogType;
//}

ctpLog::~ctpLog()
{

}

void ctpLog::log(string logInfo)
{
	string infostr = getdate() + ":" +logType + logInfo;

	fstream input(logTxtPathStr, ios_base::out | ios_base::app);
	if (input.fail())
	{
		cout << "log.txt 日志文件打开失败！" << endl;
	}
	else
	{
		input << infostr << endl;
		input.close();

		cout << infostr << endl;
	}
	cout << infostr << endl;

}

void ctpLog::setlogType(string type)
{
	this->logType = type;
}

std::string ctpLog::getdate()
{
	stringstream strtime;
	string pretime;
	//time_t t = time(NULL) - 86400; //time（null）是当天的时间  减去 86400是前一天的时间
	time_t t = time(NULL);//time（null）是当天的时间 

	tm tp;
	localtime_s(&tp, &t);
	strtime << tp.tm_year + 1900 
		<< setw(2) << setfill('0') << tp.tm_mon + 1 
		<< setw(2) << setfill('0') << tp.tm_mday
		<< setw(2) << setfill('0') << tp.tm_hour
		<< setw(2) << setfill('0') << tp.tm_min;
	strtime >> pretime;
	return pretime;
}

std::string ctpLog::gethour()
{
	stringstream strtime;
	string pretime;
	//time_t t = time(NULL) - 86400; //time（null）是当天的时间  减去 86400是前一天的时间
	time_t t = time(NULL);//time（null）是当天的时间 

	tm tp;
	localtime_s(&tp, &t);
	strtime << setw(2) << setfill('0') << tp.tm_hour
		<< setw(2) << setfill('0') << tp.tm_min;
	strtime >> pretime;
	return pretime;
}
