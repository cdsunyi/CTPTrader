/***********************************************************************
* 描述:
* 此文件用于的目的
* 数据类型的转换
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
* 20170314     石小林              创建
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
#ifndef TRANSITION_H
#define TRANSITION_H

#include "stdafx.h"

class trasition
{
public:
	trasition();
	~trasition();

	//************************************
	// Method:    intToString
	// FullName:  trasition::intToString
	// Date:      2017/03/30
	// Access:    public 
	// Returns:   std::string
	// declaration:int 转string 型 
	// Parameter: int value
	//************************************
	string intToString(int value);

	//************************************
	// Method:    doubleToString
	// FullName:  trasition::doubleToString
	// Date:      2017/03/31
	// Access:    public 
	// Returns:   std::string
	// declaration:double 转string 型 
	// Parameter: double value
	//************************************
	string doubleToString(double value);
private:

};

#endif


