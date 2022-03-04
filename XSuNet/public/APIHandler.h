/*
This file is part of XSuNet Project.
Copyright (c) 2021-2022 Suyc323.
*/
#pragma once
#include "XSuObject.h"
#include <string>
#include <map>
#include <vector>
#include <winsock2.h>
#include <unordered_map>
class Core;

/*DEVICE API*/
//设备注册 
void DEVICE_REGISTER(Core* CORE, std::string args, SOCKET Socket);

//设备信息更新(调用本功能函数即执行整个控制流程)
void DEVICE_UPDATE_INFO(Core* CORE, std::string args, SOCKET Socket);


/*CLIENT API*/
//查找设备
void CLIENT_FIND_DEVICE(Core* CORE, std::string args, SOCKET Socket);


class APIHandler:public XSuObject
{
public:
	APIHandler() {
		//DEVICE
		FuncsMap["DEVICE_REGISTER"] = (long)&DEVICE_REGISTER;
		FuncsMap["DEVICE_UPDATE_INFO"] = (long)&DEVICE_UPDATE_INFO;
		//CLIENT
		FuncsMap["CLIENT_FIND_DEVICE"] = (long)&CLIENT_FIND_DEVICE;
	}
	int APITaken(Core* CORE, std::string Info,SOCKET Socket);
protected:
	std::unordered_map<std::string, long> FuncsMap;
	std::string ClassName = "APIHandler";
private:
	long GetFunc(std::string FunName);
};


