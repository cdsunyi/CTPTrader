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
* 20160330     ʯС��              ����
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


