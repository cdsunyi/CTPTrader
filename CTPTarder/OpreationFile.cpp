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
* 20160330     石小林              创建
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
#include "OpreationFile.h"


OpreationFile::OpreationFile()
{

}

OpreationFile::OpreationFile(fstream &files)
{
}

OpreationFile::~OpreationFile()
{

}

bool OpreationFile::openfile(fstream &files, string filename)
{
	files.open(filename, ios_base::out | ios_base::app);
	if (files.fail())
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool OpreationFile::writeInfo(fstream &files,string info)
{
	//files.open(filename, ios_base::out | ios_base::app);
	if (files.fail())
	{
		return false;
	}
	else
	{
		files << info << endl;
		return true;
	}
}

bool OpreationFile::writeInfoDouble(fstream &files, double info)
{
	if (files.fail())
	{
		return false;
	}
	else
	{
		files << info << endl;
		return true;
	}
}

void OpreationFile::closefile(fstream &files)
{
	files.close();
}

void OpreationFile::readinfo()
{

}

bool OpreationFile::writeInfoDouble2(fstream &files, double info)
{
	if (files.fail())
	{
		return false;
	}
	else
	{
		files << setprecision(18) << info << endl;
		return true;
	}
}


