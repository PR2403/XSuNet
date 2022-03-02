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
/// @brief Զ��API��Ϣ������
/// @param CORE ָ��Core��ָ��
/// @param Info Զ����Ϣ������
/// @param Socket ��Ϣ��Դ�豸���׽���������
/// @return API���õĽ������
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
/// @brief ���ָ��Ŀ�꺯���ĵ�ַ
/// @param FunName Ŀ�꺯��������
/// @return Ŀ�꺯���ĵ�ַ
long APIHandler::GetFunc(std::string FunName)
{
	unordered_map<std::string, long>::iterator it = FuncsMap.find(FunName);

	if (it != FuncsMap.end()) {
		return it->second;
	}
	else return 0;

}
/// @brief �豸ע��API
/// @param CORE ָ��Core��ָ��
/// @param args Զ����Ϣ������
/// @param Socket ����ע���豸���׽���������
void DEVICE_REGISTER(Core* CORE, std::string args, SOCKET Socket)
{
	JsonHandler_AnalysisTool* Jhandler = new JsonHandler_AnalysisTool;
	std::string DeviceID = Jhandler->_get_Json_value_string(StringToChar(args), "DEVICE_ID");
	std::string DeviceClass = Jhandler->_get_Json_value_string(StringToChar(args), "DEVICE_CLASS");
	CORE->DC->GenarateNewDevice(DeviceID, DeviceClass, Socket);
	delete Jhandler;
}

/// @brief �豸ע��API
/// @param CORE ָ��Core��ָ��
/// @param args Զ����Ϣ������(��Ч����)
/// @param Socket ����ע���豸���׽���������
void DEVICE_DEREGISTER(Core* CORE, std::string args, SOCKET Socket)
{
	CORE->DC->DeleteDevice(Socket);
}

/// @brief ��Ϣ����API
/// @param CORE ָ��Core��ָ��
/// @param args Զ����Ϣ������
/// @param Socket �����ϱ���Ϣ���豸���׽���������
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

/// @brief �豸��Ϣ��ѯAPI
/// @param CORE ָ��Core��ָ��
/// @param args Զ����Ϣ������
/// @param Socket ���ڻ�ȡ��Ϣ�Ŀͻ��˵��׽���������
void CLIENT_FIND_DEVICE(Core* CORE, std::string args, SOCKET Socket)
{
	//�ȴ�ǰ�˿������ȣ�������δʵװ
}
