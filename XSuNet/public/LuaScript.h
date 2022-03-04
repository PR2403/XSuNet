#pragma once
extern "C"
{
#include <lua.h>  
#include <lualib.h>  
#include <lauxlib.h>  
#pragma comment(lib, "lua.lib")  
};

#include "XSuObject.h"
#include <iostream>  
#include <string>  
using namespace std;

class LuaScript:public XSuObject
{
public:
    std::string DeviceLuaScriptPtr;//�豸��ӦLua��·��
    std::string RunLua(std::string DeviceStateVariables);
    LuaScript(std::string LuaScriptPtr) {
        DeviceLuaScriptPtr = LuaScriptPtr;
    }
protected:
    std::string ClassName = "LuaScript";
    lua_State* luaEnv = NULL;//LuaRuntimeEnvironment
private:
    //GetLuaRuntimeEnvironment
    lua_State* GetluaEnv() {
        return luaEnv;
    }
    //Lua����ʱ������ʼ��
    lua_State* initLuaEnv();
    bool loadLuaFile(lua_State* luaEnv, const string& fileName);
    lua_CFunction getGlobalProc(lua_State* luaEnv, const string& procName);
};