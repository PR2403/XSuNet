/*
This file is part of XSuNet Project.
Copyright (c) 2021-2022 Suyc323.
*/
#pragma once
#include "stdio.h"
#include <iostream>
#include <string>
#include <thread>

/// @brief 获取char类型的整形数字的值
/// @param str 只含整形数字的char
/// @return 
static int getNumericValue(char str) {
	int ia = str - '0';
	return ia;
};

/// @brief String转化为Char的转换函数
/// @param str 需要的转化的String
/// @return 转化后的Char
static char* StringToChar(std::string str) {
	char* p = (char*)str.data();
	return p;
};

/// @brief 获取当前时间
/// @return 当前时间的tm结构体
static tm GetTime() {
	time_t nowtime;
	//首先创建一个time_t 类型的变量nowtime
	tm* p = new tm;
	//然后创建一个新时间结构体指针 p 
	time(&nowtime);
	//使用该函数就可得到当前系统时间，使用该函数需要将传入time_t类型变量nowtime的地址值。
	localtime_s(p,&nowtime);
	//控制格式输出
	return *p;
}

/// @brief 将int转化为string
/// @param v 需要转化的int
/// @return 转化后的string
static std::string intToString(int v)
{
	char buf[32] = { 0 };
	snprintf(buf, sizeof(buf), "%u", v);

	std::string str = buf;
	return str;
}

/// @brief 获得打印消息需要的时间标签 "[Time]"
/// @return 时间标签"[Time]"
static std::string GetTimeTag()
{
	tm NowTime = GetTime();
	std::string DGenInfo = "[" + intToString(NowTime.tm_year+1900) + "-"+intToString(NowTime.tm_mon)+ "-" + intToString(NowTime.tm_wday) + " " + intToString(NowTime.tm_hour) + ":" + intToString(NowTime.tm_min) + ":" + intToString(NowTime.tm_sec) + "]";
	return DGenInfo;
}