#include "XSuObject.h"
#include "XSuCPPReflectRegister.h"

XSuObject* XSuObject::CreateXSuObjByClassName(std::string ClassName)
{
	return GetXSuNet()->GetCPPReflectSystem()->CreateXSuObj(ClassName);
}
