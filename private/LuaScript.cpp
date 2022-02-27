#include "LuaScript.h"




std::string LuaScript::RunLua(std::string DeviceStateVariables)
{

    // 初始化Lua运行时环境.  
    lua_State* luaEnv = initLuaEnv();
    if (!luaEnv)
    {
        return "LuaError0";
    }
    // 加载脚本到Lua环境中.  
    if (!loadLuaFile(luaEnv, DeviceLuaScriptPtr))
    {
        cout << "Load Lua File FAILED!" << endl;
        return "LuaError1";
    }
    // 将要调用的函数和函数调用参数入栈.  
    lua_getglobal(luaEnv, "Run");
    lua_pushstring(luaEnv, DeviceStateVariables.c_str());

    // 调用Lua函数（一个参数（Json）,一个返回值（Json））.  
    lua_pcall(luaEnv, 1, 1, 0);

    // 获取返回值
    if (lua_isstring(luaEnv, -1))
    {
        std::string result = lua_tostring(luaEnv, -1);
    }

    // 将返回值出栈.  
    lua_pop(luaEnv, 1);

    // 释放Lua运行时环境.  
    lua_close(luaEnv);
}

//  
// 初始化Lua环境.  
//  
lua_State* LuaScript::initLuaEnv()
{
    lua_State* luaEnv = luaL_newstate();
    luaopen_base(luaEnv);
    luaL_openlibs(luaEnv);
    return luaEnv;
}


//  
// 加载Lua文件到Lua运行时环境中.  
//  
bool LuaScript::loadLuaFile(lua_State* luaEnv, const string& fileName)
{
    int result = luaL_loadfile(luaEnv, fileName.c_str());
    if (result)
    {
        return false;
    }

    result = lua_pcall(luaEnv, 0, 0, 0);
    return result == 0;
}


//  
// 获取全局函数.  
//  
lua_CFunction LuaScript::getGlobalProc(lua_State* luaEnv, const string& procName)
{
    lua_getglobal(luaEnv, procName.c_str());
    if (!lua_iscfunction(luaEnv, 1))
    {
        return 0;
    }

    return lua_tocfunction(luaEnv, 1);
}