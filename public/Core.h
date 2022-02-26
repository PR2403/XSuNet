/*
This file is part of XSuNet Project.
Core.h/cpp- The core of server.
Copyright (c) 2021-2022 Suyc323.
*/
#pragma once
#include "stdio.h"
#include "SegmentMes.h"
#include <winsock2.h> 
#include <mutex>
#include <thread>
#include <vector>
class APIHandler;
class server;

class Core
{
public:
	Core();
	~Core();
	//Core线程状态
	bool IsBusy();
	//添加Core收发任务
	void AddTask(SOCKET client, char info[1024]);

	server* CONNECTOR;//server_connector
	APIHandler* APIH;//APIHandler

private:
	//RecvTaskHanler线程A
	void TaskHandler_A();
	//RecvTaskHanler线程B
	void TaskHandler_B();
	//RecvTaskHanler线程C
	void TaskHandler_C();
	//RecvTaskHanler线程管理器
	void THPManager();
	void RInfoReader(RecvTaskInfo RInfo);


	std::vector<RecvTaskInfo> RecvTasks;
	std::vector<SegmentMes> SegmentML;
	std::mutex RTL_mutex;
	std::thread* THAP = NULL;
	std::thread* THBP = NULL;
	std::thread* THCP = NULL;
	std::thread* THPM;

	bool THA;
	bool THB;
	bool THC;
};