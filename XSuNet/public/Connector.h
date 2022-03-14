/*
This file is part of XSuNet Project.
Connector.h/cpp- The base code of connection and data transmission.
Copyright (c) 2021-2022 Suyc323.
*/
#pragma once

#define XSuNetVersion "3.0.3 Alpha"

#include "XSuObject.h"
#include "INIHandler.h"
#include "JsonHandler.h"
#include "MethodsLibrary.h"
#include <conio.h>
#include <iostream>
#include <thread>
#include <stdio.h>
#include <vector>

//WINDOWS
#include <winsock2.h> 
#include<ws2tcpip.h>//定义socklen_t
#pragma comment(lib, "WS2_32")  // 链接WS2_32.lib

/*LINUX
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>//定义socklen_t
*/


#include "Core.h"

struct SendTaskInfo;

//server_connector
class SocketConnector:public XSuObject
{
public:
    explicit SocketConnector(Core* SerCo,char* SER_IP,int SER_PORT);
    ~SocketConnector();
    Core* ServerCore;//指向服务器业务核心ServerCore的指针
    //初始化，由process函数自动调用
    void init();
    //connector主线程
    void process();
    void senddata(SendTaskInfo info);
protected:
    const std::string ClassName;
private:
    SOCKET listener;//客户端服务监听套接字
    sockaddr_in  serverAddr;//IPV4的地址方式
    std::vector <SOCKET> socnum;//存放创建的套接字
    char* SERVER_IP;//服务器IP
    int SERVER_PORT;//服务器监听端口
    
};

//对Socket收到的数据包转发至Core业务的SocketHandler
class SocketHandler:public XSuObject
{
public:
    explicit SocketHandler(SocketConnector* SERVER);
    ~SocketHandler();
    void TaskDistributor(SOCKET client, char info[1024]);
protected:
    const std::string ClassName;
private:
    bool IsJsonData(std::string strData);
    SocketConnector* Ser;
};