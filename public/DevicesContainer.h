#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "winsock2.h"

class XDevice;


class DevicesContainer {
public:

protected:
	std::vector<XDevice> Devices;//�豸����
	std::unordered_map<std::string, SOCKET> Hashmap;//�豸ID���豸�׽����������Ĺ�ϣ��(�ӿ�����)
private:
	//�������йܵ��豸����
	int DevicesNum;
	//�����豸ID��ȡ�豸(ָ��)
	XDevice* GetDevice(std::string DeviceID);
	//�����豸�׽�����������ȡ�豸(ָ��)
	XDevice* GetDevice(SOCKET Socket);
	//ע�����豸
	int GenarateNewDevice(std::string DeviceID,SOCKET Socket);
	//ע����ע����豸
	void DeleteDevice(std::string DeviceID);
};