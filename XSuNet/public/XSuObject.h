#pragma once
#include "stdio.h"
#include <string>
#include "XSuNet.h"

class XSuObject {
public:
	std::string GetXSuClassName() {
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

	XSuObject():ClassName("XSuObject"){};
	~XSuObject(){};
protected:
	const std::string ClassName;
	bool Discarded = false;
	XSuNet* XSN = NULL;
};