// XSuNet.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "XSuNet.h"
#include "XSuObject.h"
#include <iostream>
#include "Core.h"
#include "Connector.h"
#include "Windows.h"
#include "XSuCPPReflectRegister.h"
#include "XSuGC.h"
class Core;
class SocketConnector;


XSuNet::XSuNet()
{
    CPPReflectSystem = new XSuCPPReflectRegister(this);
    GC = new XSuGC;
    XuSNetCore =(Core*)CPPReflectSystem->CreateXSuObj("Core");
}

XSuNet::~XSuNet()
{
    delete CPPReflectSystem;
}

Core* XSuNet::GetCore()
{
    return XuSNetCore;
}

XSuCPPReflectRegister* XSuNet::GetCPPReflectSystem()
{
    return CPPReflectSystem;
}

XSuGC* XSuNet::GetGC()
{
    return GC;
}


int main() {
    system("chcp 65001");
    XSuNet* XSUNET=new XSuNet;
    SocketConnector* CON = XSUNET->GetCore()->CONNECTOR;
    CON->process();
}