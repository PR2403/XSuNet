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
	//XDevice��ĸ��ƹ��캯��
	XDevice& operator=(const XDevice& OldXD) 
	{
		DeviceID = OldXD.DeviceID;
		DeviceClass = OldXD.DeviceClass;
		DeviceSocket = OldXD.DeviceSocket;
		return *this;
	};
	std::string DeviceID;//�豸ID
	std::string DeviceClass;//�豸����
	SOCKET DeviceSocket;//�豸�׽���������
	bool RemoteManualControlUpdate(std::string NewDeviceControlledVariables);
	std::string DeviceControlUpdate(std::string NewDeviceStateVariables);
protected:
	const std::string ClassName;
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