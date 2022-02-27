#include "LuaScript.h"




std::string LuaScript::RunLua(std::string DeviceStateVariables)
{

    // ��ʼ��Lua����ʱ����.  
    lua_State* luaEnv = initLuaEnv();
    if (!luaEnv)
    {
        return "LuaError0";
    }
    // ���ؽű���Lua������.  
    if (!loadLuaFile(luaEnv, DeviceLuaScriptPtr))
    {
        cout << "Load Lua File FAILED!" << endl;
        return "LuaError1";
    }
    // ��Ҫ���õĺ����ͺ������ò�����ջ.  
    lua_getglobal(luaEnv, "Run");
    lua_pushstring(luaEnv, DeviceStateVariables.c_str());

    // ����Lua������һ��������Json��,һ������ֵ��Json����.  
    lua_pcall(luaEnv, 1, 1, 0);

    // ��ȡ����ֵ
    if (lua_isstring(luaEnv, -1))
    {
        std::string result = lua_tostring(luaEnv, -1);
    }

    // ������ֵ��ջ.  
    lua_pop(luaEnv, 1);

    // �ͷ�Lua����ʱ����.  
    lua_close(luaEnv);
}

//  
// ��ʼ��Lua����.  
//  
lua_State* LuaScript::initLuaEnv()
{
    lua_State* luaEnv = luaL_newstate();
    luaopen_base(luaEnv);
    luaL_openlibs(luaEnv);
    return luaEnv;
}


//  
// ����Lua�ļ���Lua����ʱ������.  
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
// ��ȡȫ�ֺ���.  
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