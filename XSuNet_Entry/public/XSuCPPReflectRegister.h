#pragma once
#include <string>
#include <map>
#include "XSuObject.h"
#include "XSuNet.h"

//��������ӵ�map
#define ADD_CLASS_REGISTER(ClassName) g_ReflectRegisterMap.insert(std::make_pair(#ClassName, []() -> XSuObject* {return new ClassName; }))

//��������ĺ���ָ��
typedef XSuObject* (*PF_CREATE_OBJECT)();

class XSuCPPReflectRegister{
	
public:
	XSuCPPReflectRegister(XSuNet* xsunet);
	~XSuCPPReflectRegister();
	//����
	XSuNet* XSN;

	//������������
	XSuObject* CreateXSuObj(std::string _ClassName);

	//��ʼ������ע�ᣬ
	void InitClassReflect();
};

