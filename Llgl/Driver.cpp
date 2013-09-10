#include "Library.h"
#include <windows.h>

LLGL_NAMESPACE(Llgl);

Driver* Driver::_singleton = 0;
HMODULE g_module = 0;

Driver::Load::Load(const std::string& driverName)
{
	if(g_module) throw InvalidOperationException("driver already loaded");
	g_module = LoadLibrary((std::string("LlglDriver") + driverName + ".dll").c_str());
	if(!g_module || !Driver::_singleton) throw FileAccessException("driver not found");
}

Driver::Load::~Load()
{
	if(g_module)
	{
		FreeLibrary(g_module);
		g_module = 0;
	}
}

Driver::Driver()
{
	_singleton = this;
}

Driver::~Driver()
{
	_singleton = 0;
}

Driver* Driver::get()
{
	if(!_singleton) throw InvalidOperationException("driver not loaded"); 
	return _singleton;
}

LLGL_NAMESPACE_END;