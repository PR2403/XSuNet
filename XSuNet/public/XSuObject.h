#pragma once
#include "stdio.h"
#include <string>
#include "XSuNet.h"

class XSuObject {
public:
	std::string GetClassName() {
		return ClassName;
	};
	bool ObjectIsDiscarded() {
		return Discarded;
	};
	void DeleteThisObject() {
		Discarded = true;
	}
	void SetXSN(XSuNet* XSNet) {
		XSN = XSNet;
	}
	XSuNet* GetXSuNet() {
		return XSN;
	};
	XSuObject* CreateXSuObjByClassName(std::string ClassName);
protected:
	std::string ClassName = "XSuObject";
	bool Discarded = false;
	XSuNet* XSN = NULL;
};