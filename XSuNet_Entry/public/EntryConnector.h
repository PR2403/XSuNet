/*
This file is part of XSuNet Project.
Connector.h/cpp- The base code of connection and data transmission.
Copyright (c) 2021-2022 Suyc323.
*/
#pragma once

#define XSuNetVersion "2.0.2"

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

struct SendTaskInfo;

//server_connector
class SocketConnector:public XSuObject
{
public:
    SocketConnector(Core* SerCo,char* SER_IP,int SER_PORT);
    ~SocketConnector();
    //初始化，由process函数自动调用
    void init();
    //connector主线程
    void process();
    bool canrebootnow();
    void senddata(SendTaskInfo info);
protected:
    std::string ClassName = "SocketConnector";
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
    SocketHandler(SocketConnector* SERVER);
    ~SocketHandler();
    void TaskDistributor(SOCKET client, char info[1024]);
protected:
    std::string ClassName = "SocketHandler";
private:
    bool IsJsonData(std::string strData);
    SocketConnector* Ser;
};