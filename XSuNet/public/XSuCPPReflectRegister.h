#pragma once
#include <string>
#include <map>
#include "XSuObject.h"
#include "XSuNet.h"

//把类名添加到map
#define ADD_CLASS_REGISTER(ClassName) g_ReflectRegisterMap.insert(std::make_pair(#ClassName, []() -> XSuObject* {return new ClassName; }))

//创建对象的函数指针
typedef XSuObject* (*PF_CREATE_OBJECT)();

class XSuCPPReflectRegister{
	
public:
	XSuCPPReflectRegister(XSuNet* xsunet);
	~XSuCPPReflectRegister();
	//父类
	XSuNet* XSN;

	//类名创建对象
	XSuObject* CreateXSuObj(std::string _ClassName);

	//初始化类名注册，
	void InitClassReflect();
};

