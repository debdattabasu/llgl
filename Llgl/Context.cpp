#include "Library.h"

LLGL_NAMESPACE(Llgl);

Context::Context()
{

}

Context::~Context()
{

}

void Context::checkChildValid(ContextChildPtr child)
{
	if(child->getParentContext().get() != this) throw InvalidOperationException("context mismatch");
}

LLGL_NAMESPACE_END;
