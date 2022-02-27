#pragma once
extern "C"
{
#include <lua.h>  
#include <lualib.h>  
#include <lauxlib.h>  
#pragma comment(lib, "lua.lib")  
};


#include <iostream>  
#include <string>  
using namespace std;

class LuaScript
{
public:
    std::string DeviceLuaScriptPtr;//设备对应Lua的路径
    //调用执行该Lua脚本
    std::string RunLua(std::string DeviceStateVariables);
    LuaScript(std::string LuaScriptPtr) {
        DeviceLuaScriptPtr = LuaScriptPtr;
    }
protected:
    lua_State* luaEnv = NULL;//LuaRuntimeEnvironment
private:
    //GetLuaRuntimeEnvironment
    lua_State* GetluaEnv() {
        return luaEnv;
    }
    //Lua运行时环境初始化
    lua_State* initLuaEnv();
    bool loadLuaFile(lua_State* luaEnv, const string& fileName);
    lua_CFunction getGlobalProc(lua_State* luaEnv, const string& procName);
};