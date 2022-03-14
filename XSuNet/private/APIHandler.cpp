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
/**
 * @brief API调用函数
 * @param CORE 指向Core对象的指针
 * @param Info 数据包的内容
 * @param Socket 请求设备的套接字描述符
 * @return 结果(0 失败 1 成功)
*/
int APIHandler::APITaken(Core* CORE, std::string Info,SOCKET Socket)
{
	JsonHandler_AnalysisTool* Jhandler = new JsonHandler_AnalysisTool;
	std::string FunName = Jhandler->_get_Json_value_string(StringToChar(Info), "API");
	std::string args = Jhandler->_get_Json_value_string(StringToChar(Info), "Args");
	if (FunName =="DEVICE_REGISTER")
	{
		DEVICE_REGISTER(CORE, args, Socket);
		return 1;
	}
	else if (FunName == "DEVICE_DEREGISTER")
	{
		DEVICE_DEREGISTER(CORE, args, Socket);
		return 1;
	}
	else if (FunName == "DEVICE_UPDATE_INFO")
	{
		DEVICE_UPDATE_INFO(CORE, args, Socket);
		return 1;
	}
	else 
	{
		return 0;
	}

}
;

/**
 * @brief API：设备注册
 * @param CORE 指向Core对象的指针
 * @param args 数据包中调用API对应的Args内容
 * @param Socket 目标设备的套接字描述符
*/
void APIHandler::DEVICE_REGISTER(Core* CORE, std::string args, SOCKET Socket)
{
	JsonHandler_AnalysisTool* Jhandler = new JsonHandler_AnalysisTool;
	std::string DeviceID = Jhandler->_get_Json_value_string(StringToChar(args), "DeviceID");
	std::string DeviceClass = Jhandler->_get_Json_value_string(StringToChar(args), "DeviceClass");
	CORE->DC->GenarateNewDevice(DeviceID, DeviceClass, Socket);
	delete Jhandler;
}

/**
 * @brief API:设备注销
 * @param CORE 指向Core对象的指针
 * @param args 数据包中调用API对应的Args内容
 * @param Socket 目标设备的套接字描述符
*/
void APIHandler::DEVICE_DEREGISTER(Core* CORE, std::string args, SOCKET Socket)
{
	CORE->DC->DeleteDevice(Socket);
}

/**
 * @brief API:设备状态更新
 * @param CORE 
 * @param args 
 * @param Socket 
*/
void APIHandler::DEVICE_UPDATE_INFO(Core* CORE, std::string args, SOCKET Socket)
{
	JsonHandler_AnalysisTool* Jhandler = new JsonHandler_AnalysisTool;
	std::string Rep = Jhandler->_get_Json_value_string(StringToChar(args), "Rep");
	std::string CON = CORE->DC->GetDevice(Socket)->DeviceControlUpdate(Rep);
	delete Jhandler;
	JsonHandler_MakeTool* JSender = new JsonHandler_MakeTool;
	JSender->AddKeyAndValue_string("Control", CON);
	std::string senddata = JSender->OutputJsonString();
	char content[1024];
	strcpy_s(content,senddata.c_str());
	CORE->AddTask(1, Socket, content);
}