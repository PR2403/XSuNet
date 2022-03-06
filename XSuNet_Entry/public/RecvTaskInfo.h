/*
This file is part of XSuNet Project.
Copyright (c) 2021-2022 Suyc323.
*/
#pragma once
#include <winsock2.h> 

struct RecvTaskInfo 
{
	SOCKET client;
	char Sinfo[1024];
};