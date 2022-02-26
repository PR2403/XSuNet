#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "winsock2.h"

class XDevice;


class DevicesContainer {
public:

protected:
	std::vector<XDevice> Devices;//设备容器
	std::unordered_map<std::string, SOCKET> Hashmap;//设备ID和设备套接字描述符的哈希表(加快索引)
private:
	//该容器托管的设备总数
	int DevicesNum;
	//根据设备ID获取设备(指针)
	XDevice* GetDevice(std::string DeviceID);
	//根据设备套接字描述符获取设备(指针)
	XDevice* GetDevice(SOCKET Socket);
	//注册新设备
	int GenarateNewDevice(std::string DeviceID,SOCKET Socket);
	//注销已注册的设备
	void DeleteDevice(std::string DeviceID);
};