/*
This file is part of XSuNet Project.
Copyright (c) 2021-2022 Suyc323.
*/
#include "JsonHandler.h"
#include <iostream>

jsonhandler::jsonhandler()
{
}

jsonhandler::~jsonhandler()
{
}

std::string jsonhandler::_get_Json_value_string(char stringtemp[1024], std::string key)
{
	std::string TargetStr = "";
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(stringtemp, root))
	{
		TargetStr = root[key].asString();
	}
	return TargetStr;
}

std::string jsonhandler::_get_Json_value_string(std::string stringtemp, std::string key)
{
	std::string TargetStr = "";
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(stringtemp, root))
	{
		TargetStr = root[key].asString();
	}
	return TargetStr;
}

std::string jsonhandler::_get_Json_value_string(char stringtemp[1024], std::string key, std::string UKey)
{
	std::string TargetStr = "";
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(stringtemp, root))
	{
		TargetStr = root[UKey][key].asString();
	}
	return TargetStr;
}

std::string jsonhandler::_get_Json_value_string(std::string stringtemp, std::string key, std::string UKey)
{
	std::string TargetStr = "";
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(stringtemp, root))
	{
		TargetStr = root[UKey][key].asString();
	}
	return TargetStr;
}

std::string jsonhandler::_get_Json_value_string(char stringtemp[1024], std::string key, std::string ROOT2, std::string ROOT1)
{
	std::string TargetStr = "";
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(stringtemp, root))
	{
		TargetStr = root[ROOT1][ROOT2][key].asString();
	}
	return TargetStr;
}

std::string jsonhandler::_get_Json_value_string(std::string stringtemp, std::string key, std::string ROOT2, std::string ROOT1)
{
	std::string TargetStr = "";
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(stringtemp, root))
	{
		TargetStr = root[ROOT1][ROOT2][key].asString();
	}
	return TargetStr;
}

int jsonhandler::_get_Json_value_int(char stringtemp[1024], std::string key)
{
	int TargetInt = NULL;
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(stringtemp, root))
	{
		TargetInt = root[key].asInt();
	}
	return TargetInt;

}

bool jsonhandler::_get_Json_value_bool(char stringtemp[1024], std::string key)
{
	bool TargetBool = false;
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(stringtemp, root))
	{
		TargetBool = root[key].asBool();
	}
	return TargetBool;
}


jsonsendler::jsonsendler()
{
}

jsonsendler::~jsonsendler()
{
}

void jsonsendler::AddKeyAndValue_int(std::string key, int value)
{
	root[key] = Json::Value(value);
}

void jsonsendler::AddKeyAndValue_string(std::string key, std::string value)
{
	root[key] = Json::Value(value);
}

void jsonsendler::AddKeyAndValue_bool(std::string key, bool value)
{
	root[key] = Json::Value(value);
}

std::string jsonsendler::OutputJsonString()
{
	Json::StyledWriter sw;
	return sw.write(root);
	
}