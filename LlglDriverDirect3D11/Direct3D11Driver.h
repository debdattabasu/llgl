#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Driver) : public Driver
{
public:
	Direct3D11Driver();
	~Direct3D11Driver() override;
	ContextPtr createContext() override;

private:	
	static Direct3D11Driver _registrar;
};

LLGL_NAMESPACE_END2;