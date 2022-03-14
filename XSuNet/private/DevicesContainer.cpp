#include "DevicesContainer.h"
#include "XDevice.h"

/**
 * @brief 获取Device对象
 * @param DeviceID 目标Device对象的ID
 * @return 指向Device对象的指针
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
 * @brief 获取Device对象
 * @param Socket 目标Device对象的套接字描述符
 * @return 指向Device对象的指针
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
 * @brief 生成新Device对象
 * @param DeviceID 新Device的ID
 * @param DeviceClass 新Device的类别
 * @param Socket 新Device的套接字描述符
 * @return 结果（0 数量超过最大负载 1 成功）
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
 * @brief 删除Device对象
 * @param DeviceID 目标Device的ID
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
 * @brief 删除Device对象
 * @param DeviceSocket 目标Device的套接字描述符
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
