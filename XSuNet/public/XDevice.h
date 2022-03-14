#pragma once


#include <iostream>
#include <string>
#include "winsock2.h"
#include "XSuObject.h"
class LuaScript;

class XDevice:public XSuObject{
public:
	explicit XDevice(std::string DeviceID,std::string DeviceClass,SOCKET DeviceSocket);
	~XDevice();
	//XDevice类的复制构造函数
	XDevice& operator=(const XDevice& OldXD) 
	{
		DeviceID = OldXD.DeviceID;
		DeviceClass = OldXD.DeviceClass;
		DeviceSocket = OldXD.DeviceSocket;
		return *this;
	};
	std::string DeviceID;//设备ID
	std::string DeviceClass;//设备类型
	SOCKET DeviceSocket;//设备套接字描述符
	bool RemoteManualControlUpdate(std::string NewDeviceControlledVariables);
	std::string DeviceControlUpdate(std::string NewDeviceStateVariables);
protected:
	const std::string ClassName;
	std::string DeviceStateVariables=""; //设备状态变量(服务器缓存)
	std::string DeviceControlledVariables="";//设备受控变量(服务器缓存)
	LuaScript* XDLua;
	bool AllowRemoteManualControl=true;
private:
	LuaScript* GetDeviceLuaInterface() {
		return XDLua;
	}
	//设备状态变量(服务器缓存)读取函数
	std::string GetDeviceStateVariables() {
		return DeviceStateVariables;
	}
	//设备状态变量(服务器缓存)存入函数
	void SetDeviceStateVariables(std::string NewData) {
		DeviceStateVariables = NewData;
	}
	//设备受控变量(服务器缓存)读取函数
	std::string GetDeviceControlledVariables() {
		return DeviceControlledVariables;
	}
	//设备受控变量(服务器缓存)存入函数
	void SetDeviceControlledVariables(std::string NewData) {
		DeviceControlledVariables = NewData;
	}
};