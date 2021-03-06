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

	//************************************
	// Method:    getdate
	// FullName:  compressFile::getdate
	// Date:      2017/04/10
	// Access:    public 
	// Returns:   std::string
	// declaration: 获得日期
	//************************************
	string getdate();

	//************************************
	// Method:    getdate
	// FullName:  compressFile::getdate
	// Date:      2017/04/10
	// Access:    public 
	// Returns:   std::string
	// declaration: 获得时间
	//************************************
	string gethour();

private:
	string logType;
};

#endif // !1CTPLOG_H


