#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(ContextChild)
{
public:
	virtual ~ContextChild();
	ContextPtr getParentContext() const;
protected:
	ContextChild(ContextPtr parentContext);
	virtual void initialize() = 0;
private:
	ContextPtr _parentContext;
};

LLGL_NAMESPACE_END;