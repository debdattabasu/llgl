#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(ContextChild) : public NonCopyable
{
public:
	virtual ~ContextChild();
	ContextPtr getParentContext() const;
protected:
	ContextChild(ContextPtr parentContext);
private:
	ContextPtr _parentContext;
};

LLGL_NAMESPACE_END;