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
#include "transition.h"


trasition::trasition()
{

}

trasition::~trasition()
{

}

std::string trasition::intToString(int value)
{
	string str;
	stringstream sstream;
	sstream << value;
	sstream >> str;
	return str;
}

std::string trasition::doubleToString(double value)
{
	string str;
	stringstream sstream;
	sstream << setprecision(18) << value;
	sstream >> str;
	return str;

	//char buf[2000];
	//sprintf_s(buf, sizeof(buf), "%f", value);
	//return string(buf);

}
