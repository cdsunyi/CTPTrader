/***********************************************************************
* ����:
* ���ļ����ڵ�Ŀ��
* �������͵�ת��
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
* 20170314     ʯС��              ����
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
	// declaration:int תstring �� 
	// Parameter: int value
	//************************************
	string intToString(int value);

	//************************************
	// Method:    doubleToString
	// FullName:  trasition::doubleToString
	// Date:      2017/03/31
	// Access:    public 
	// Returns:   std::string
	// declaration:double תstring �� 
	// Parameter: double value
	//************************************
	string doubleToString(double value);
private:

};

#endif


