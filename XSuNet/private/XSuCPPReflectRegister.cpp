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

//定义一个全局的map保存字符串到动态类生成的函数指针的映射表
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
    //该函数应当在类反射定义初始化后调用，不支持线程安全。（类反射定义已在XSuNet初始化时执行，可以在任意XSuObject及其派生类中通过CreateXSuObjByClassName调用）
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
    //要反射的类必须添加
    //ADD_CLASS_REGISTER(SocketConnector); //XSuCPP反射系统暂不支持没有默认构造函数的类，请等待后续更新
    //ADD_CLASS_REGISTER(SocketHandler);   //XSuCPP反射系统暂不支持没有默认构造函数的类，请等待后续更新
    ADD_CLASS_REGISTER(Core);
    //ADD_CLASS_REGISTER(XDevice);         //XSuCPP反射系统暂不支持没有默认构造函数的类，请等待后续更新
    ADD_CLASS_REGISTER(DevicesContainer);
    ADD_CLASS_REGISTER(APIHandler);
    ADD_CLASS_REGISTER(JsonHandler_AnalysisTool);
    ADD_CLASS_REGISTER(JsonHandler_MakeTool);
    //ADD_CLASS_REGISTER(LuaScript);       //XSuCPP反射系统暂不支持没有默认构造函数的类，请等待后续更新
}