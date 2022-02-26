#pragma once

#include <iostream>
#include <string>
#include "winsock2.h"


class XDevice{
public:
	XDevice(std::string DeviceID, SOCKET DeviceSocket);
	~XDevice();
	std::string DeviceID;//�豸ID
	SOCKET DeviceSocket;//�豸�׽���������
protected:
	std::string DeviceStateVariables=""; //�豸״̬����(����������)
	std::string DeviceControlledVariables="";//�豸�ܿر���(����������)

private:
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