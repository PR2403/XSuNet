/*
This file is part of XSuNet Project.
Copyright (c) 2021-2022 SuYichen.
*/
#include "APIHandler.h"
#include "JsonHandler.h"
#include "MethodsLibrary.h"
#include "Connector.h"

int APIHandler::APITaken(std::string Info,SOCKET Socket)
{
	jsonhandler* Jhandler = new jsonhandler;
	std::string FunName = Jhandler->_get_Json_value_string(StringToChar(Info), "API");
	std::string args = Jhandler->_get_Json_value_string(StringToChar(Info), "Args");
	return 1;
};