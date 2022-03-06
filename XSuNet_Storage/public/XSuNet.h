#pragma once
class XSuCPPReflectRegister;
class Core;
class Connector;
class XSuGC;

class XSuNet {
public:
	XSuNet();
	~XSuNet();
	Core* GetCore();
	XSuCPPReflectRegister* GetCPPReflectSystem();
	XSuGC* GetGC();
protected:
	XSuCPPReflectRegister* CPPReflectSystem;
	Core* XuSNetCore;
	XSuGC* GC;
private:
	
};