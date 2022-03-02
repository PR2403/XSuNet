#include "DevicesContainer.h"
#include "MethodsLibrary.h"

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
		else return NULL;
	}
}

int DevicesContainer::GenarateNewDevice(std::string DeviceID,std::string DeviceClass, SOCKET Socket)
{
	if (Devices.size()>= 100)
	{
		return 0;
	}
	else
	{
		Devices.push_back(XDevice(DeviceID, DeviceClass, Socket));
		std::string TimeTag = GetTimeTag();
		std::cout<<TimeTag.data()<<":"<<DeviceID<<" "<<"ÐÂÉè±¸×¢²á"<<std::endl;
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
			Devices.erase(it);
			break;
		}
	}
}
