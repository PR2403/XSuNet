/*
This file is part of XSuNet Project.
Copyright (c) 2021-2022 Suyc323.
*/
#pragma once
#include <string>
#include <map>
#include <vector>
#include <winsock2.h>

class APIHandler
{
public:

	int APITaken(std::string Info,SOCKET Socket);


private:
	bool GenerateNewDevice_Warpper(std::string SInfo, int& result)
	{

	};

	bool UpdateInfo_Wrapper(std::string SInfo, int& result)
	{

	};
};


