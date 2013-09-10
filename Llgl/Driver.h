#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Driver)
{
public:
	LLGL_CLASS(Load)
	{
	public:
		Load(const std::string& driverName);
		~Load();
	};
	static Driver* get();
	virtual ~Driver();
	ContextPtr createContext() = 0;
protected:
	Driver();
private:
	static Driver* _singleton;
};

LLGL_NAMESPACE_END;