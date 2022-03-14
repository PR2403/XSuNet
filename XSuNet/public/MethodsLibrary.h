/*
This file is part of XSuNet Project.
Copyright (c) 2021-2022 Suyc323.
*/
#pragma once
#include "stdio.h"
#include <iostream>
#include <string>
#include <thread>

/**
 * @brief 将纯整形string转为int的功能函数
 * @param str 纯整形string
 * @return 转化后的int
*/
static int getNumericValue(char str) {
	int ia = str - '0';
	return ia;
};

/**
 * @brief 将String转化为Char*
 * @param str 需要转化的String
 * @return 转化后的Char*
*/
static char* StringToChar(std::string str) {
	char* p = (char*)str.data();
	return p;
};

