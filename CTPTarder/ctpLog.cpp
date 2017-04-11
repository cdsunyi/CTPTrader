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
* 20170313     ʯС��              ����
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

#include "ctpLog.h"


//log�ļ��е�ַ
extern string logFolderPathStr;
//log�ļ�TXT��ַ
extern string logTxtPathStr;

ctpLog::ctpLog() :logType("")
{
	//string ת const * char �� logpathstr -> logpathstr.c_str()
	_mkdir(logFolderPathStr.c_str());	 //����������ݵ��ļ��У�����ļ��д����򲻴���������������򴴽���
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
		cout << "log.txt ��־�ļ���ʧ�ܣ�" << endl;
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
	//time_t t = time(NULL) - 86400; //time��null���ǵ����ʱ��  ��ȥ 86400��ǰһ���ʱ��
	time_t t = time(NULL);//time��null���ǵ����ʱ�� 

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
	//time_t t = time(NULL) - 86400; //time��null���ǵ����ʱ��  ��ȥ 86400��ǰһ���ʱ��
	time_t t = time(NULL);//time��null���ǵ����ʱ�� 

	tm tp;
	localtime_s(&tp, &t);
	strtime << setw(2) << setfill('0') << tp.tm_hour
		<< setw(2) << setfill('0') << tp.tm_min;
	strtime >> pretime;
	return pretime;
}
