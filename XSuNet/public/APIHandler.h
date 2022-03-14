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




class APIHandler:public XSuObject
{
public:
	APIHandler() {}
	int APITaken(Core* CORE, std::string Info,SOCKET Socket);
protected:
	std::string ClassName = "APIHandler";

	//�豸ע�� 
	void DEVICE_REGISTER(Core* CORE, std::string args, SOCKET Socket);
	void DEVICE_DEREGISTER(Core* CORE, std::string args, SOCKET Socket);
	//�豸��Ϣ����(���ñ����ܺ�����ִ��������������)
	void DEVICE_UPDATE_INFO(Core* CORE, std::string args, SOCKET Socket);
private:

};


