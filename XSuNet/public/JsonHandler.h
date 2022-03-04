/*
This file is part of XSuNet Project.
Copyright (c) 2021-2022 Suyc323.
*/
#pragma once
#include "XSuObject.h"
#include "json\json.h"

class JsonHandler_AnalysisTool:public XSuObject
{
public:
	JsonHandler_AnalysisTool();
	~JsonHandler_AnalysisTool();
	std::string _get_Json_value_string(char stringtemp[1024], std::string key);
	std::string _get_Json_value_string(std::string stringtemp, std::string key);
	std::string _get_Json_value_string(char stringtemp[1024], std::string key, std::string ROOT);
	std::string _get_Json_value_string(std::string stringtemp, std::string key, std::string UKey);
	std::string _get_Json_value_string(char stringtemp[1024], std::string key, std::string ROOT2,std::string ROOT1);
	std::string _get_Json_value_string(std::string stringtemp, std::string key, std::string ROOT2, std::string ROOT1);
	int _get_Json_value_int(char stringtemp[1024], std::string key);
	bool _get_Json_value_bool(char stringtemp[1024],std::string key);
protected:
	std::string ClassName = "JsonHandler_AnalysisTool";
private:

};

class JsonHandler_MakeTool :public XSuObject
{
public:
	JsonHandler_MakeTool();
	~JsonHandler_MakeTool();
	void AddKeyAndValue_int(std::string key,int value);
	void AddKeyAndValue_string(std::string key, std::string value);
	void AddKeyAndValue_bool(std::string key, bool value);
	std::string OutputJsonString();
protected:
	std::string ClassName = "JsonHandler_MakeTool";
private:
	Json::Value root;

};