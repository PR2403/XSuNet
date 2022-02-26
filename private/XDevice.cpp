#include "XDevice.h"
#include "JsonHandler.h"

XDevice::XDevice(std::string ID, SOCKET Socket)
{
	DeviceID = ID;
	DeviceSocket = Socket;
}

XDevice::~XDevice() {

}