#include "Library.h"

LLGL_NAMESPACE(Llgl);

ContextChild::ContextChild(ContextPtr parentContext) : _parentContext(parentContext)
{

}

ContextChild::~ContextChild()
{

}

ContextPtr ContextChild::getParentContext() const
{
	return _parentContext;
}

LLGL_NAMESPACE_END;