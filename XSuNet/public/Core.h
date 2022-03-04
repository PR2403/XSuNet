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
	//Core线程状态
	bool IsBusy();
	//添加Core收发任务
	void AddTask(int tasktype, SOCKET client, char info[1024]);

	SocketConnector* CONNECTOR;//server_connector
	APIHandler* APIH;//APIHandler
	DevicesContainer* DC;
protected:
	std::string ClassName = "Core";
private:
	//RecvTaskHandler线程1
	void TaskHandler_A();
	//RecvTaskHandler线程2
	void TaskHandler_B();
	//RecvTaskHandler线程3
	void TaskHandler_C();
	//SendTaskHandler线程4
	void TaskHandler_D();
	//SendTaskHandler线程5
	void TaskHandler_E();
	//SendTaskHandler线程6
	void TaskHandler_F();

	//RecvTaskHanler线程管理器

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