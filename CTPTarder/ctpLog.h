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
#ifndef CTPLOG_H
#define CTPLOG_H


#include "stdafx.h"


class ctpLog
{
public:
	ctpLog();
	//ctpLog(string ctplogType);
	~ctpLog();

	//************************************
	// Method:    log
	// FullName:  ctplog::log
	// Date:      2017/03/13
	// Access:    public 
	// Returns:   void
	// declaration: print log infomation
	// Parameter: string logInfo
	//************************************
	void log(string logInfo);

	//************************************
	// Method:    setlogType
	// FullName:  ctplog::setlogType
	// Date:      2017/03/13
	// Access:    public 
	// Returns:   void
	// declaration: set lyotype infomation
	// Parameter: string type
	//************************************
	void setlogType(string type);

private:
	string logType;
};

#endif // !1CTPLOG_H


