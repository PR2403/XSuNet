/*
This file is part of XSuNet Project.
Copyright (c) 2021-2022 SuYichen.
*/
#pragma once
#include "stdio.h"
#include <iostream>
#include <string>
#include <thread>

static int getNumericValue(char str) {
	int ia = str - '0';
	return ia;
};

static char* StringToChar(std::string str) {
	char* p = (char*)str.data();
	return p;
};

