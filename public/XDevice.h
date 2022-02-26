#pragma once

#include <iostream>
#include <string>
#include "winsock2.h"


class XDevice{
public:
	XDevice(std::string DeviceID, SOCKET DeviceSocket);
	~XDevice();
	std::string DeviceID;//设备ID
	SOCKET DeviceSocket;//设备套接字描述符
protected:
	std::string DeviceStateVariables=""; //设备状态变量(服务器缓存)
	std::string DeviceControlledVariables="";//设备受控变量(服务器缓存)

private:
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