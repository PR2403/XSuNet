// XSuNet.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Core.h"
#include "Connector.h"
#include "Windows.h"
class Core;
class SocketConnector;

int main() {
    system("chcp 65001");
    Core* CO = new Core;
    SocketConnector* CON=CO->CONNECTOR;
    CON->process();
}