/*
This file is part of XSuNet Project.
Core.h/cpp- The core of SocketConnector.
Copyright (c) 2021-2022 Suyc323.
*/
#include "Core.h"
#include "stdio.h"
#include <thread>
#include <RecvTaskInfo.h>
#include <JsonHandler.h>
#include <iostream>
#include "Connector.h"
#include "APIHandler.h"
#include "DevicesContainer.h"

Core::Core()
{
    std::cout << "XSuNet版本:"<<XSuNetVersion<< std::endl;
    std::string TimeTag1 = GetTimeTag();
    std::cout<<TimeTag1<<":正在启用XSuNet核心服务...\n"<<std::endl;
    THA = false;
    THB = false;
    THC = false;
    THD = false;
    THE = false;
    THF = false;
    CMyINI* p = new CMyINI();
    p->ReadINI("./Configs/ServerSettings.ini");
    std::string s_ip = p->GetValue("Network", "SERVER_IP");
    char* SERVER_IP = StringToChar(s_ip);
    std::string s_port = p->GetValue("Network", "SERVER_PORT");
    int SERVER_PORT= atoi(s_port.c_str());
    CONNECTOR = new SocketConnector(this, SERVER_IP, SERVER_PORT);
    THPM=new std::thread(&Core::THPManager, this);
    std::string TimeTag2 = GetTimeTag();
    std::cout << TimeTag2 << ":核心服务已启用√ \n" << std::endl;
    APIH = new APIHandler;
    DC = new DevicesContainer;
}

Core::~Core()
{
    delete THAP;
    delete THBP;
    delete THCP;
    delete THPM;
    delete CONNECTOR;
}

bool Core::IsBusy()
{
	return (sizeof(RecvTasks) > 0);
}

/// @brief 将收到的信息加入Core的信息处理任务列表
/// @param tasktype 任务类型 0:处理收到的信息 1:创建信息发送任务
/// @param client 信息来源/目标的套接字描述符
/// @param info 消息的内容
void Core::AddTask(int tasktype,SOCKET client, char info[1024])
{
    if (tasktype == 0)
    {
        RecvTaskInfo Newinfo = { client,*info };
        RecvTasks.emplace_back(Newinfo);
    }
    else if (tasktype == 1)
    {
        SendTaskInfo Newinfo = { client,*info };
        SendTasks.emplace_back(Newinfo);
    }
}

void Core::TaskHandler_A()
{
    while (true)
    {
        RTL_mutex.lock();
        if (RecvTasks.size() > 0)
        {
            RecvTaskInfo info = RecvTasks[0];
            RecvTasks.erase(RecvTasks.begin());
            RTL_mutex.unlock();
            RInfoReader(info);
        }
        else
        {
            RTL_mutex.unlock();
        }
        if (THA = false)
        {
            break;
        }
    }
}

void Core::TaskHandler_B()
{
    while (true)
    {
        RTL_mutex.lock();
        if (RecvTasks.size() > 0)
        {
            RecvTaskInfo info = RecvTasks[0];
            RecvTasks.erase(RecvTasks.begin());
            RTL_mutex.unlock();
            RInfoReader(info);
        }
        else
        {
            RTL_mutex.unlock();
        }
        if (THB = false)
        {
            break;
        }
    }
}
void Core::TaskHandler_C()
{
    while (true)
    {
        RTL_mutex.lock();
        if (RecvTasks.size() > 0)
        {
            RecvTaskInfo info = RecvTasks[0];
            RecvTasks.erase(RecvTasks.begin());
            RTL_mutex.unlock();
            RInfoReader(info);
        }
        else
        {
            RTL_mutex.unlock();
        }
        if (THC = false)
        {
            break;
        }
    }
}
void Core::TaskHandler_D()
{
    while (true)
    {
        STL_mutex.lock();
        if (SendTasks.size() > 0)
        {
            SendTaskInfo info = SendTasks[0];
            SendTasks.erase(SendTasks.begin());
            STL_mutex.unlock();
            CONNECTOR->senddata(info);
        }
        else
        {
            STL_mutex.unlock();
        }
        if (THD = false)
        {
            break;
        }
    }
}

void Core::TaskHandler_E()
{
    while (true)
    {
        STL_mutex.lock();
        if (SendTasks.size() > 0)
        {
            SendTaskInfo info = SendTasks[0];
            SendTasks.erase(SendTasks.begin());
            STL_mutex.unlock();
            CONNECTOR->senddata(info);
        }
        else
        {
            STL_mutex.unlock();
        }
        if (THE = false)
        {
            break;
        }
    }
}

void Core::TaskHandler_F()
{
    while (true)
    {
        STL_mutex.lock();
        if (SendTasks.size() > 0)
        {
            SendTaskInfo info = SendTasks[0];
            SendTasks.erase(SendTasks.begin());
            STL_mutex.unlock();
            CONNECTOR->senddata(info);
        }
        else
        {
            STL_mutex.unlock();
        }
        if (THF = false)
        {
            break;
        }
    }
}

void Core::THPManager()
{
    while (true)
    {
        
        if (sizeof(RecvTasks) > 0)
        {
            
            THA = true;
            if (THAP = NULL)
            {
                THAP = new std::thread(&Core::TaskHandler_A, this);
            }
            if (sizeof(RecvTasks) > 2)
            {
                THB = true;
                if (THBP = NULL)
                {
                    THBP = new std::thread(&Core::TaskHandler_B, this);
                }
                
                if (sizeof(RecvTasks) > 4)
                {
                    THC = true;
                    if (THCP = NULL)
                    {
                        THCP = new std::thread(&Core::TaskHandler_C, this);
                    }
                }
                else
                {
                    THC = false;
                }
            }
            else
            {
                THB = false;
                THC = false;
            }
        }
        else
        {
            THA = false;
            THB = false;
            THC = false;
        }
        if (sizeof(SendTasks) > 0)
        {

            THD = true;
            if (THDP = NULL)
            {
                THDP = new std::thread(&Core::TaskHandler_D, this);
            }
            if (sizeof(SendTasks) > 2)
            {
                THE = true;
                if (THEP = NULL)
                {
                    THEP = new std::thread(&Core::TaskHandler_E, this);
                }

                if (sizeof(SendTasks) > 4)
                {
                    THF = true;
                    if (THFP = NULL)
                    {
                        THFP = new std::thread(&Core::TaskHandler_F, this);
                    }
                }
                else
                {
                    THF = false;
                }
            }
            else
            {
                THE = false;
                THF = false;
            }
        }
        else
        {
            THD = false;
            THE = false;
            THF = false;
        }
    }
}

/// @brief 按照消息属性处理信息
/// @param RInfo 收到的信息 
void Core::RInfoReader(RecvTaskInfo RInfo)
{
    JsonHandler_AnalysisTool* Jhandler = new JsonHandler_AnalysisTool;
    bool IsSegmentMes = Jhandler->_get_Json_value_bool(RInfo.Sinfo, "SegmentMes");
    if (IsSegmentMes)//分包数据处理
    {
        std::string MesID = Jhandler->_get_Json_value_string(RInfo.Sinfo, "MesID");;
        int Section = Jhandler->_get_Json_value_int(RInfo.Sinfo, "Section");
        int SectionNum = Jhandler->_get_Json_value_int(RInfo.Sinfo, "SectionNum");
        SegmentMes SM = { MesID,Section,SectionNum,RInfo };
        delete Jhandler;
        //实际功能实现

        //
    }
    else//常规数据处理
    {
        delete Jhandler;
        APIH->APITaken(this,RInfo.Sinfo,RInfo.client);
    }
}


