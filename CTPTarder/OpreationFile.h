/***********************************************************************
* ����:
* ���ļ����ڵ�Ŀ��
* ��д�ļ�����
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
* 20170329     ʯС��              ����
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
	// declaration: ���ļ� �ɹ�����true  ʧ�ܣ�false
	// Parameter: fstream & files
	// Parameter: string filename  �ļ���
	//************************************
	bool openfile(fstream &files, string filename);


	//************************************
	// Method:    writeInfo
	// FullName:  OpreationFile::writeInfo
	// Date:      2017/03/30
	// Access:    public 
	// Returns:   bool
	// declaration: ���ļ���д����Ϣ д��ɹ�����true ʧ�ܣ� false
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
	// declaration: ��ȡ�ļ���Ϣ
	//************************************
	void readinfo();

	//************************************
	// Method:    closefile
	// FullName:  OpreationFile::closefile
	// Date:      2017/03/30
	// Access:    public 
	// Returns:   void
	// declaration: �ر��ļ�
	// Parameter: fstream & files
	//************************************
	void closefile(fstream &files);

private:
	string fileName;
};

#endif