#pragma once

#include <iostream>
#include <string>
#include "winsock2.h"
class LuaScript;

class XDevice{
public:
	XDevice(std::string DeviceID,std::string DeviceClass,SOCKET DeviceSocket);
	~XDevice();
	std::string DeviceID;//�豸ID
	std::string DeviceClass;//�豸����
	SOCKET DeviceSocket;//�豸�׽���������
	bool RemoteManualControlUpdate(std::string NewDeviceControlledVariables);
	std::string DeviceControlUpdate(std::string NewDeviceStateVariables);
protected:
	std::string DeviceStateVariables=""; //�豸״̬����(����������)
	std::string DeviceControlledVariables="";//�豸�ܿر���(����������)
	LuaScript* XDLua;
	bool AllowRemoteManualControl=true;
private:
	LuaScript* GetDeviceLuaInterface() {
		return XDLua;
	}
	//�豸״̬����(����������)��ȡ����
	std::string GetDeviceStateVariables() {
		return DeviceStateVariables;
	}
	//�豸״̬����(����������)���뺯��
	void SetDeviceStateVariables(std::string NewData) {
		DeviceStateVariables = NewData;
	}
	//�豸�ܿر���(����������)��ȡ����
	std::string GetDeviceControlledVariables() {
		return DeviceControlledVariables;
	}
	//�豸�ܿر���(����������)���뺯��
	void SetDeviceControlledVariables(std::string NewData) {
		DeviceControlledVariables = NewData;
	}
};