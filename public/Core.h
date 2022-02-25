/*
This file is part of XSuNet Project.
Core.h/cpp- The core of server.
Copyright (c) 2021-2022 SuYichen.
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
	bool IsBusy();
	void AddTask(SOCKET client, char info[1024]);

	server* CONNECTOR;
	APIHandler* APIH;

private:
	void TaskHandler_A();
	void TaskHandler_B();
	void TaskHandler_C();
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