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
 * @brief ��������stringתΪint�Ĺ��ܺ���
 * @param str ������string
 * @return ת�����int
*/
static int getNumericValue(char str) {
	int ia = str - '0';
	return ia;
};

/**
 * @brief ��Stringת��ΪChar*
 * @param str ��Ҫת����String
 * @return ת�����Char*
*/
static char* StringToChar(std::string str) {
	char* p = (char*)str.data();
	return p;
};

