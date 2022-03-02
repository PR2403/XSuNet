/*
This file is part of XSuNet Project.
Connector.h/cpp- The base code of connection and data transmission.
Copyright (c) 2021-2022 Suyc323.
*/

#include "Connector.h"
#include "stdio.h"
#include "SendTaskInfo.h"
#include "DevicesContainer.h"

SocketConnector::SocketConnector(Core* SerCo,char* SER_IP,int SER_PORT)
{
    ServerCore = SerCo;
    listener = 0;
    SERVER_IP = SER_IP;
    SERVER_PORT = SER_PORT;
    serverAddr.sin_family = PF_INET;
    serverAddr.sin_port = SERVER_PORT;
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr.s_addr);//将字符串类型转换uint32_t
}
SocketConnector::~SocketConnector()
{
    delete ServerCore;
}
//初始化函数，功能创建监听套接字，绑定端口，并进行监听
void SocketConnector::init()
{
    int   Ret;
    WSADATA   wsaData;// 用于初始化套接字环境
    // 初始化WinSock环境
    if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    {
        printf("WSAStartup()   failed   with   error   %d\n", Ret);
        WSACleanup();
    }


    listener = socket(AF_INET, SOCK_STREAM, 0);//采用ipv4,TCP传输
    if (listener == -1) { printf("Error at socket(): %ld\n", WSAGetLastError()); perror("listener failed"); exit(1); }
    std::string TimeTag = GetTimeTag();
    std::cout<<TimeTag<<":监听服务已开启√ \n"<<std::endl;

    unsigned long ul = 1;
    if (ioctlsocket(listener, FIONBIO, (unsigned long*)&ul) == -1) { perror("ioctl failed"); exit(1); };
    if (bind(listener, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("bind error");
        exit(1);
    }
    if (listen(listener, 6) < 0) { perror("listen failed"); exit(1); };
    socnum.push_back(listener);//加入监听套接字
}

void SocketConnector::process()
{

    int mount = 0;
    fd_set fds;
    FD_ZERO(&fds);//将fds清零
    init();
    std::vector<int> SWD;
    while (1)
    {
        mount = int(socnum.size());
        //每次都将fds重新赋值
        for (int i = 0; i < mount; ++i)
        {
            FD_SET(socnum[i], &fds);
        }

        struct timeval timeout = { 0,50000 };
        switch (select(0, &fds, NULL, NULL, &timeout))
        {
        case -1:
        {
            perror("select\n");
            printf("Error at socket(): %ld\n", WSAGetLastError());
            std::cout << mount << std::endl;
            /*          for (int i = 0; i < mount; ++i)
                        {
                            printf("%d\n", socnum[i]);
                        }*/
            Sleep(1000);
            break;
        }
        case 0:
        {
            //printf("select timeout......");
            break;
        }
        default:
        {
            //将数组中的每一个套接字都和剩余的额套接字进行比较得到当前的任务
            for (int i = 0; i < mount; ++i)
            {
                //如果第一个套接字可读的消息。就要建立连接
                if (i == 0 && FD_ISSET(socnum[i], &fds))
                {
                    struct sockaddr_in client_address;
                    socklen_t client_addrLength = sizeof(struct sockaddr_in);
                    //返回一个用户的套接字
                    SOCKET clientfd = accept(listener, (struct sockaddr*)&client_address, &client_addrLength);
                    //添加用户
                    socnum.push_back(clientfd);

                }
                else if (i != 0 && FD_ISSET(socnum[i], &fds))
                {
                    char buf[1024];
                    memset(buf, '\0', sizeof(buf));
                    int size = recv(socnum[i], buf, sizeof(buf) - 1, 0);
                    //检测是否断线
                    if (size == 0 || size == -1)
                    {
                        ServerCore->DC->DeleteDevice(socnum[i]);//注销设备
                        closesocket(socnum[i]);//先关闭这个套接字
                        SWD.push_back(i);
                    }
                    //若是没有掉线
                    else
                    {
                        SocketHandler* handler = new SocketHandler(this);
                        char NewBuf[1024];
                        strcpy_s(NewBuf, buf);
                        handler->TaskDistributor(socnum[i], NewBuf);
                        delete(handler);
                    }

                }
            }
            for (int X = 0; X < SWD.size(); X++)
            {
                FD_CLR(socnum[SWD[X]], &fds);//在列表列表中删除
                socnum.erase(socnum.begin() + SWD[X]);//在vector数组中删除
            }
            SWD.clear();
            break;
        }
        }

    }
}
bool SocketConnector::canrebootnow()
{
    return (ServerCore->IsBusy());
}
void SocketConnector::senddata(SendTaskInfo info)
{
    send(info.client, info.Sinfo, 1024, 0);
}
SocketHandler::SocketHandler(SocketConnector* SERVER)
{
    Ser = SERVER;
}

SocketHandler::~SocketHandler()
{
}


void SocketHandler::TaskDistributor(SOCKET Socket, char info[1024])
{

    Core* core = Ser->ServerCore;
    core->AddTask(0,Socket,info);
}