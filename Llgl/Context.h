#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Context)
{
public:
	virtual ~Context();
	virtual CapabilitiesPtr getCapabilities() = 0;
protected:
	Context();
	virtual void initialize() = 0;
private:
	void checkChildValid(ContextChildPtr child);
	std::mutex _mutex;
};

LLGL_NAMESPACE_END;