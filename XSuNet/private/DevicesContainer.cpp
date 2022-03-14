#include "DevicesContainer.h"
#include "XDevice.h"

/**
 * @brief ��ȡDevice����
 * @param DeviceID Ŀ��Device�����ID
 * @return ָ��Device�����ָ��
*/
XDevice* DevicesContainer::GetDevice(std::string DeviceID)
{
	for (int i = 0; i < Devices.size(); i++)
	{
		if (Devices[i].DeviceID == DeviceID)
		{
			XDevice* device = &(Devices[i]);
			return device;
			break;
		}
		else return NULL;
	}
}

/**
 * @brief ��ȡDevice����
 * @param Socket Ŀ��Device������׽���������
 * @return ָ��Device�����ָ��
*/
XDevice* DevicesContainer::GetDevice(SOCKET Socket)
{
	for (int i = 0; i < Devices.size(); i++)
	{
		if (Devices[i].DeviceSocket == Socket)
		{
			XDevice* device = &(Devices[i]);
			return device;
			break;
		}
		else
		{
			return NULL;
		}
	}
	return NULL;
}

/**
 * @brief ������Device����
 * @param DeviceID ��Device��ID
 * @param DeviceClass ��Device�����
 * @param Socket ��Device���׽���������
 * @return �����0 ������������� 1 �ɹ���
*/
int DevicesContainer::GenarateNewDevice(std::string DeviceID,std::string DeviceClass, SOCKET Socket)
{
	if (Devices.size()>= 100)
	{
		return 0;
	}
	else
	{
		Devices.emplace_back(XDevice(DeviceID, DeviceClass, Socket));
		DevicesNum = int(Devices.size());
		return 1;
	}
}

/**
 * @brief ɾ��Device����
 * @param DeviceID Ŀ��Device��ID
*/
void DevicesContainer::DeleteDevice(std::string DeviceID)
{
	std::vector<XDevice>::iterator it;
	for (it = Devices.begin(); it != Devices.end();it++)
	{
		if (it->DeviceID == DeviceID)
		{
			Devices.erase(it);
			break;
		}
	}
}

/**
 * @brief ɾ��Device����
 * @param DeviceSocket Ŀ��Device���׽���������
*/
void DevicesContainer::DeleteDevice(SOCKET DeviceSocket) 
{
	std::vector<XDevice>::iterator it;
	for (it = Devices.begin(); it != Devices.end(); it++)
	{
		if (it->DeviceSocket == DeviceSocket)
		{
			Devices.erase(it);
			break;
		}
	}
}
