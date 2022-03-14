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
 * @brief API���ú���
 * @param CORE ָ��Core�����ָ��
 * @param Info ���ݰ�������
 * @param Socket �����豸���׽���������
 * @return ���(0 ʧ�� 1 �ɹ�)
*/
int APIHandler::APITaken(Core* CORE, std::string Info,SOCKET Socket)
{
	JsonHandler_AnalysisTool* Jhandler = new JsonHandler_AnalysisTool;
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
/**
 * @brief ��ȡ�������Ĺ��ܺ���
 * @param FunName API��������
 * @return ָ��Ŀ�꺯����ָ��
*/
long APIHandler::GetFunc(std::string FunName)
{
	unordered_map<std::string, long>::iterator it = FuncsMap.find(FunName);

	if (it != FuncsMap.end()) {
		return it->second;
	}
	else return 0;

}

/**
 * @brief API���豸ע��
 * @param CORE ָ��Core�����ָ��
 * @param args ���ݰ��е���API��Ӧ��Args����
 * @param Socket Ŀ���豸���׽���������
*/
void DEVICE_REGISTER(Core* CORE, std::string args, SOCKET Socket)
{
	JsonHandler_AnalysisTool* Jhandler = new JsonHandler_AnalysisTool;
	std::string DeviceID = Jhandler->_get_Json_value_string(StringToChar(args), "DeviceID");
	std::string DeviceClass = Jhandler->_get_Json_value_string(StringToChar(args), "DeviceClass");
	CORE->DC->GenarateNewDevice(DeviceID, DeviceClass, Socket);
	delete Jhandler;
}

/**
 * @brief API:�豸ע��
 * @param CORE ָ��Core�����ָ��
 * @param args ���ݰ��е���API��Ӧ��Args����
 * @param Socket Ŀ���豸���׽���������
*/
void DEVICE_DEREGISTER(Core* CORE, std::string args, SOCKET Socket)
{
	CORE->DC->DeleteDevice(Socket);
}

/**
 * @brief API:�豸״̬����
 * @param CORE 
 * @param args 
 * @param Socket 
*/
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

/**
 * @brief 
 * @param CORE 
 * @param args 
 * @param Socket 
*/
void CLIENT_FIND_DEVICE(Core* CORE, std::string args, SOCKET Socket)
{
	//�ȴ�ǰ�˿������ȣ�������δʵװ
}
