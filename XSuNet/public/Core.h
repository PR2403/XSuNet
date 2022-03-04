/*
This file is part of XSuNet Project.
Core.h/cpp- The core of SocketConnector.
Copyright (c) 2021-2022 Suyc323.
*/
#pragma once

#include "XSuObject.h"
#include "stdio.h"
#include "SegmentMes.h"
#include "RecvTaskInfo.h"
#include "SendTaskInfo.h"
#include <winsock2.h> 
#include <mutex>
#include <thread>
#include <vector>
class APIHandler;
class SocketConnector;
class DevicesContainer;

class Core:public XSuObject
{
public:
	Core();
	~Core();
	//Core�߳�״̬
	bool IsBusy();
	//���Core�շ�����
	void AddTask(int tasktype, SOCKET client, char info[1024]);

	SocketConnector* CONNECTOR;//server_connector
	APIHandler* APIH;//APIHandler
	DevicesContainer* DC;
protected:
	std::string ClassName = "Core";
private:
	//RecvTaskHandler�߳�1
	void TaskHandler_A();
	//RecvTaskHandler�߳�2
	void TaskHandler_B();
	//RecvTaskHandler�߳�3
	void TaskHandler_C();
	//SendTaskHandler�߳�4
	void TaskHandler_D();
	//SendTaskHandler�߳�5
	void TaskHandler_E();
	//SendTaskHandler�߳�6
	void TaskHandler_F();

	//RecvTaskHanler�̹߳�����

	void THPManager();
	void RInfoReader(RecvTaskInfo RInfo);


	std::vector<RecvTaskInfo> RecvTasks;
	std::vector<SendTaskInfo> SendTasks;
	std::vector<SegmentMes> SegmentML;
	std::mutex RTL_mutex;
	std::mutex STL_mutex;
	std::thread* THAP = NULL;
	std::thread* THBP = NULL;
	std::thread* THCP = NULL;
	std::thread* THDP = NULL;
	std::thread* THEP = NULL;
	std::thread* THFP = NULL;
	std::thread* THPM;

	bool THA;
	bool THB;
	bool THC;
	bool THD;
	bool THE;
	bool THF;
};