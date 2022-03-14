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
#include <condition_variable>
#include <sstream>
class APIHandler;
class SocketConnector;
class DevicesContainer;

class Core:public XSuObject
{
public:
	Core();
	~Core();

	bool IsBusy();
	void AddTask(int tasktype, SOCKET client, char info[1024]);
	SocketConnector* CONNECTOR;//server_connector
	APIHandler* APIH;//APIHandler
	DevicesContainer* DC;
protected:
	const std::string ClassName;
private:
	void TaskHandler_A();
	void TaskHandler_B();
	void TaskHandler_C();
	void TaskHandler_D();
	void TaskHandler_E();
	void TaskHandler_F();
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

class ThreadCtrl
{
public:
	ThreadCtrl()
		:m_flag(false)
	{}
	void wait()
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_cv.wait(lock, [=] { return m_flag; });
		m_flag = false;
	}
	void wake()
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_flag = true;
		m_cv.notify_one();
	}
private:
	std::mutex m_mutex;
	std::condition_variable m_cv;
	bool m_flag;
};

class ThreadManage
{
public:
	ThreadManage() {}
	~ThreadManage()
	{
		for (auto ctrl : m_CtrlVec)
			delete ctrl;
		m_CtrlVec.clear();
	}
	ThreadCtrl* createCtrl()
	{
		auto ctrl = new ThreadCtrl();
		m_mutex.lock();
		m_CtrlVec.push_back(std::move(ctrl));
		m_mutex.unlock();
		return ctrl;
	}
	std::vector<ThreadCtrl*>& getAllCtrl() { return m_CtrlVec; }
private:
	std::vector<ThreadCtrl*> m_CtrlVec;
	std::mutex m_mutex;
};