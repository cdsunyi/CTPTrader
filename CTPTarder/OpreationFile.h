/***********************************************************************
* 描述:
* 此文件用于的目的
* 读写文件操作
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
* 20170329     石小林              创建
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
#ifndef OPREATIONFILE_H
#define OPREATIONFILE_H


#include "stdafx.h"

class OpreationFile
{
public:
	OpreationFile();
	OpreationFile(fstream &files);
	~OpreationFile();
	
	//************************************
	// Method:    openfile
	// FullName:  OpreationFile::openfile
	// Date:      2017/03/30
	// Access:    public 
	// Returns:   bool 
	// declaration: 打开文件 成功返回true  失败：false
	// Parameter: fstream & files
	// Parameter: string filename  文件名
	//************************************
	bool openfile(fstream &files, string filename);


	//************************************
	// Method:    writeInfo
	// FullName:  OpreationFile::writeInfo
	// Date:      2017/03/30
	// Access:    public 
	// Returns:   bool
	// declaration: 网文件中写入信息 写入成功返回true 失败： false
	// Parameter: fstream & files
	// Parameter: string info
	//************************************
	bool writeInfo(fstream &files, string info);


	//************************************
	// Method:    readinfo
	// FullName:  OpreationFile::readinfo
	// Date:      2017/03/30
	// Access:    public 
	// Returns:   void
	// declaration: 读取文件信息
	//************************************
	void readinfo();

	//************************************
	// Method:    closefile
	// FullName:  OpreationFile::closefile
	// Date:      2017/03/30
	// Access:    public 
	// Returns:   void
	// declaration: 关闭文件
	// Parameter: fstream & files
	//************************************
	void closefile(fstream &files);

private:
	string fileName;
};

#endif