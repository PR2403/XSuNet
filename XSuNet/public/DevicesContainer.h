#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "winsock2.h"
#include "XDevice.h"
#include "XSuObject.h"


class DevicesContainer:public XSuObject {
public:
	int DevicesNum=0;
	XDevice* GetDevice(std::string DeviceID);
	XDevice* GetDevice(SOCKET Socket);
	int GenarateNewDevice(std::string DeviceID,std::string DeviceClass, SOCKET Socket);
	void DeleteDevice(std::string DeviceID);
	void DeleteDevice(SOCKET DeviceSocket);
	DevicesContainer() :ClassName("DeviceContainer"){};
	~DevicesContainer(){};
protected:
	const std::string ClassName;
	std::vector<XDevice> Devices;//�豸����
	std::unordered_map<std::string, SOCKET> Hashmap;//�豸ID���豸�׽����������Ĺ�ϣ��(�ӿ�����),�ƻ��ں���������ʹ��
private:
	
};