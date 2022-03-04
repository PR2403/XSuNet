#pragma once
#include <winsock2.h> 

struct SendTaskInfo
{
	SOCKET client;
	char Sinfo[1024];
};