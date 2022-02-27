/*
This file is part of XSuNet Project.
Copyright (c) 2021-2022 Suyc323.
*/
#include "APIHandler.h"
#include "Core.h"
#include "DevicesContainer.h"
#include "XDevice.h"
#include "JsonHandler.h"
#include "MethodsLibrary.h"
#include "Connector.h"
#include <cstdio>

typedef void(*FUNC)(Core* CORE, std::string,SOCKET);
int APIHandler::APITaken(Core* CORE, std::string Info,SOCKET Socket)
{
	jsonhandler* Jhandler = new jsonhandler;
	std::string FunName = Jhandler->_get_Json_value_string(StringToChar(Info), "API");
	std::string args = Jhandler->_get_Json_value_string(StringToChar(Info), "Args");
	long APIFunc = GetFunc(FunName);
	if (APIFunc!=0)
	{
		(FUNC(APIFunc)(CORE, args, Socket));
		return 1;
	}
	else
	{
		return 0;
	}
}
;
long APIHandler::GetFunc(std::string FunName)
{
	unordered_map<std::string, long>::iterator it = FuncsMap.find(FunName);

	if (it != FuncsMap.end()) {
		return it->second;
	}
	else return 0;

}

void DEVICE_REGISTER(Core* CORE, std::string args, SOCKET Socket)
{
	jsonhandler* Jhandler = new jsonhandler;
	std::string DeviceID = Jhandler->_get_Json_value_string(StringToChar(args), "DeviceID");
	std::string DeviceClass = Jhandler->_get_Json_value_string(StringToChar(args), "DeviceClass");
	CORE->DC->GenarateNewDevice(DeviceID, DeviceClass, Socket);
	delete Jhandler;
}

void DEVICE_DEREGISTER(Core* CORE, std::string args, SOCKET Socket)
{
	CORE->DC->DeleteDevice(Socket);
}

void DEVICE_UPDATE_INFO(Core* CORE, std::string args, SOCKET Socket)
{
	jsonhandler* Jhandler = new jsonhandler;
	std::string Rep = Jhandler->_get_Json_value_string(StringToChar(args), "Rep");
	std::string CON = CORE->DC->GetDevice(Socket)->DeviceControlUpdate(Rep);
	delete Jhandler;
	jsonsendler* JSender = new jsonsendler;
	JSender->AddKeyAndValue_string("Control", CON);
	std::string senddata = JSender->OutputJsonString();
	char content[1024];
	strcpy_s(content,senddata.c_str());
	CORE->AddTask(1, Socket, content);
}

void CLIENT_FIND_DEVICE(Core* CORE, std::string args, SOCKET Socket)
{
	//等待前端开发进度，功能暂未实装
}
