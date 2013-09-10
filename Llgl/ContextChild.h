#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(ContextChild) : std::enable_shared_from_this<ContextChild>
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