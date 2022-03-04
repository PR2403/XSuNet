#include "XDevice.h"
#include "JsonHandler.h"
#include "LuaScript.h"

XDevice::XDevice(std::string ID, std::string Class, SOCKET Socket)
{
	DeviceID = ID;
	DeviceSocket = Socket;
	DeviceClass = Class;
	XDLua = new LuaScript(".\\Scripts\\"+ID + ".lua");
}

XDevice::~XDevice() {
	delete XDLua;
}

bool XDevice::RemoteManualControlUpdate(std::string NewDeviceControlledVariables)
{
	if (AllowRemoteManualControl == false) 
	{
		return false;
	}
	else
	{
		DeviceControlledVariables = NewDeviceControlledVariables;
		return true;
	}

}

std::string XDevice::DeviceControlUpdate(std::string NewDeviceStateVariables)
{
	DeviceStateVariables = NewDeviceStateVariables;
	DeviceControlledVariables=GetDeviceLuaInterface()->RunLua(DeviceStateVariables);
	return DeviceControlledVariables;
}

