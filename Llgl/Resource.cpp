#include "Library.h"

LLGL_NAMESPACE(Llgl);

Resource::Resource(ContextPtr parentContext, uint32_t numDimensions, FormatPtr format):
	ContextChild(parentContext), _numDimensions(numDimensions), _format(format)
{

}

Resource::~Resource()
{

}

void Resource::initialize()
{
	if(!getFormat())
		throw InvalidArgumentException("format can not be null");
}

FormatPtr Resource::getFormat() const
{
	return _format;
}

uint32_t Resource::getNumDimensions() const
{
	return _numDimensions;
}

LLGL_NAMESPACE_END;