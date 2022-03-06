#include "DevicesContainer.h"
#include "XDevice.h"

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

int DevicesContainer::GenarateNewDevice(std::string DeviceID,std::string DeviceClass, SOCKET Socket)
{
	if (Devices.size()>= 10)
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

void DevicesContainer::DeleteDevice(std::string DeviceID)
{
	std::vector<XDevice>::iterator it;
	for (it = Devices.begin(); it != Devices.end();it++)
	{
		if (it->DeviceID == DeviceID)
		{
			it->DeleteThisObject();
			Devices.erase(it);
			break;
		}
	}
}

void DevicesContainer::DeleteDevice(SOCKET DeviceSocket) 
{
	std::vector<XDevice>::iterator it;
	for (it = Devices.begin(); it != Devices.end(); it++)
	{
		if (it->DeviceSocket == DeviceSocket)
		{
			it->DeleteThisObject();
			Devices.erase(it);
			break;
		}
	}
}
