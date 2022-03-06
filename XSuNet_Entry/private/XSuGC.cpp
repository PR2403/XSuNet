#include "XSuGC.h"

XSuGC::XSuGC()
{
}

XSuGC::~XSuGC()
{
}

bool XSuGC::NewXSuObjectGen(XSuObject* NewXSO)
{
	if (NewXSO != NULL) {
		XSuObjectsList.emplace_back(NewXSO);
		return true;
	}
	else
		return false;
}

void XSuGC::DoGC()
{
	for (int i = 0; i < XSuObjectsList.size(); i++) {
		XSuObject* Obj = XSuObjectsList[i];
		if (Obj->ObjectIsDiscarded() == true) {
			delete Obj;
			XSuObjectsList.erase(XSuObjectsList.begin()+i);
		}
	}
	
}