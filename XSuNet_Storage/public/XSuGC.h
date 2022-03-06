#pragma once
#include "stdio.h"
#include <vector>
#include "XSuObject.h"

class XSuGC
{
public:
	XSuGC();
	~XSuGC();
	bool NewXSuObjectGen(XSuObject* NewXSO);
	void DoGC();
private:
	std::vector<XSuObject*> XSuObjectsList;
};

