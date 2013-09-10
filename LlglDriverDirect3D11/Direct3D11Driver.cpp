#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

Direct3D11Driver Direct3D11Driver::_registrar;

Direct3D11Driver::Direct3D11Driver() : Driver()
{

}

Direct3D11Driver::~Direct3D11Driver()
{

}

ContextPtr Direct3D11Driver::createContext()
{
	auto ret = std::make_shared<Direct3D11Context>();
	ret->initialize();
	return ret;
}

LLGL_NAMESPACE_END2;