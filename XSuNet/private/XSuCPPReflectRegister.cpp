#include "XSuCPPReflectRegister.h"
#include "XSuNet.h"
#include "XSuGC.h"

#include "Connector.h"
#include "Core.h"
#include "XDevice.h"
#include "DevicesContainer.h"
#include "APIHandler.h"
#include "JsonHandler.h"
#include "LuaScript.h"

//����һ��ȫ�ֵ�map�����ַ�������̬�����ɵĺ���ָ���ӳ���
std::map<std::string, PF_CREATE_OBJECT> g_ReflectRegisterMap;

XSuCPPReflectRegister::XSuCPPReflectRegister(XSuNet* xsunet)
{
    XSN = xsunet;
}

XSuCPPReflectRegister::~XSuCPPReflectRegister()
{
}

XSuObject* XSuCPPReflectRegister::CreateXSuObj(std::string _ClassName)
{
    //�ú���Ӧ�����෴�䶨���ʼ������ã���֧���̰߳�ȫ�����෴�䶨������XSuNet��ʼ��ʱִ�У�����������XSuObject������������ͨ��CreateXSuObjByClassName���ã�
    if (0 == g_ReflectRegisterMap.size())
    {
        InitClassReflect();
    }
    auto itr = g_ReflectRegisterMap.find(_ClassName);
    if (itr != g_ReflectRegisterMap.end())
    {
        XSuObject* Obj = ((PF_CREATE_OBJECT)itr->second)();
        Obj->SetXSN(XSN);
        XSN->GetGC()->NewXSuObjectGen(Obj);
        return Obj;
    }
    return nullptr;
}

inline void XSuCPPReflectRegister::InitClassReflect()
{
    //Ҫ�������������
    //ADD_CLASS_REGISTER(SocketConnector); //XSuCPP����ϵͳ�ݲ�֧��û��Ĭ�Ϲ��캯�����࣬��ȴ���������
    //ADD_CLASS_REGISTER(SocketHandler);   //XSuCPP����ϵͳ�ݲ�֧��û��Ĭ�Ϲ��캯�����࣬��ȴ���������
    ADD_CLASS_REGISTER(Core);
    //ADD_CLASS_REGISTER(XDevice);         //XSuCPP����ϵͳ�ݲ�֧��û��Ĭ�Ϲ��캯�����࣬��ȴ���������
    ADD_CLASS_REGISTER(DevicesContainer);
    ADD_CLASS_REGISTER(APIHandler);
    ADD_CLASS_REGISTER(JsonHandler_AnalysisTool);
    ADD_CLASS_REGISTER(JsonHandler_MakeTool);
    //ADD_CLASS_REGISTER(LuaScript);       //XSuCPP����ϵͳ�ݲ�֧��û��Ĭ�Ϲ��캯�����࣬��ȴ���������
}