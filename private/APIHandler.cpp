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
/// @brief 远程API消息处理函数
/// @param CORE 指向Core的指针
/// @param Info 远程消息的内容
/// @param Socket 消息来源设备的套接字描述符
/// @return API调用的结果反馈
int APIHandler::APITaken(Core* CORE, std::string Info,SOCKET Socket)
{
	JsonHandler_AnalysisTool* Jhandler = new JsonHandler_AnalysisTool;
	std::string FunName = Jhandler->_get_Json_value_string(StringToChar(Info), "API");
	std::string args = Jhandler->_get_Json_value_string(StringToChar(Info), "ARGS");
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
/// @brief 获得指向目标函数的地址
/// @param FunName 目标函数的名称
/// @return 目标函数的地址
long APIHandler::GetFunc(std::string FunName)
{
	unordered_map<std::string, long>::iterator it = FuncsMap.find(FunName);

	if (it != FuncsMap.end()) {
		return it->second;
	}
	else return 0;

}
/// @brief 设备注册API
/// @param CORE 指向Core的指针
/// @param args 远程消息的内容
/// @param Socket 正在注册设备的套接字描述符
void DEVICE_REGISTER(Core* CORE, std::string args, SOCKET Socket)
{
	JsonHandler_AnalysisTool* Jhandler = new JsonHandler_AnalysisTool;
	std::string DeviceID = Jhandler->_get_Json_value_string(StringToChar(args), "DEVICE_ID");
	std::string DeviceClass = Jhandler->_get_Json_value_string(StringToChar(args), "DEVICE_CLASS");
	CORE->DC->GenarateNewDevice(DeviceID, DeviceClass, Socket);
	delete Jhandler;
}

/// @brief 设备注销API
/// @param CORE 指向Core的指针
/// @param args 远程消息的内容(无效输入)
/// @param Socket 正在注销设备的套接字描述符
void DEVICE_DEREGISTER(Core* CORE, std::string args, SOCKET Socket)
{
	CORE->DC->DeleteDevice(Socket);
}

/// @brief 信息更新API
/// @param CORE 指向Core的指针
/// @param args 远程消息的内容
/// @param Socket 正在上报信息的设备的套接字描述符
void DEVICE_UPDATE_INFO(Core* CORE, std::string args, SOCKET Socket)
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

/// @brief 设备信息查询API
/// @param CORE 指向Core的指针
/// @param args 远程消息的内容
/// @param Socket 正在获取信息的客户端的套接字描述符
void CLIENT_FIND_DEVICE(Core* CORE, std::string args, SOCKET Socket)
{
	//等待前端开发进度，功能暂未实装
}
