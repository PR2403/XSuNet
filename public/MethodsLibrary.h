/*
This file is part of XSuNet Project.
Copyright (c) 2021-2022 Suyc323.
*/
#pragma once
#include "stdio.h"
#include <iostream>
#include <string>
#include <thread>

/// @brief ��ȡchar���͵��������ֵ�ֵ
/// @param str ֻ���������ֵ�char
/// @return 
static int getNumericValue(char str) {
	int ia = str - '0';
	return ia;
};

/// @brief Stringת��ΪChar��ת������
/// @param str ��Ҫ��ת����String
/// @return ת�����Char
static char* StringToChar(std::string str) {
	char* p = (char*)str.data();
	return p;
};

/// @brief ��ȡ��ǰʱ��
/// @return ��ǰʱ���tm�ṹ��
static tm GetTime() {
	time_t nowtime;
	//���ȴ���һ��time_t ���͵ı���nowtime
	tm* p = new tm;
	//Ȼ�󴴽�һ����ʱ��ṹ��ָ�� p 
	time(&nowtime);
	//ʹ�øú����Ϳɵõ���ǰϵͳʱ�䣬ʹ�øú�����Ҫ������time_t���ͱ���nowtime�ĵ�ֵַ��
	localtime_s(p,&nowtime);
	//���Ƹ�ʽ���
	return *p;
}

/// @brief ��intת��Ϊstring
/// @param v ��Ҫת����int
/// @return ת�����string
static std::string intToString(int v)
{
	char buf[32] = { 0 };
	snprintf(buf, sizeof(buf), "%u", v);

	std::string str = buf;
	return str;
}

/// @brief ��ô�ӡ��Ϣ��Ҫ��ʱ���ǩ "[Time]"
/// @return ʱ���ǩ"[Time]"
static std::string GetTimeTag()
{
	tm NowTime = GetTime();
	std::string DGenInfo = "[" + intToString(NowTime.tm_year+1900) + "-"+intToString(NowTime.tm_mon)+ "-" + intToString(NowTime.tm_wday) + " " + intToString(NowTime.tm_hour) + ":" + intToString(NowTime.tm_min) + ":" + intToString(NowTime.tm_sec) + "]";
	return DGenInfo;
}