#include "Library.h"

LLGL_NAMESPACE(Llgl);

Resource::Resource(ContextPtr parentContext, ResourceType resType, uint32_t width, FormatPtr format, bool isStreaming) : 
	ContextChild(parentContext), _resourceType(resType), _numDims(1), _width(width), _height(1), _depth(1), 
	_isStreaming(isStreaming), _isMapped(0), _format(format)
{
	
}

Resource::Resource(ContextPtr parentContext, ResourceType resType, uint32_t width, uint32_t height, FormatPtr format, bool isStreaming): 
	ContextChild(parentContext), _resourceType(resType), _numDims(2), _width(width), _height(height), _depth(1),
	_isStreaming(isStreaming), _isMapped(0), _format(format)
{

}

Resource::Resource(ContextPtr parentContext, ResourceType resType, uint32_t width, uint32_t height, uint32_t depth, FormatPtr format, bool isStreaming): 
	ContextChild(parentContext), _resourceType(resType), _numDims(3), _width(width), _height(height), _depth(depth), 
	_isStreaming(isStreaming), _isMapped(0), _format(format)
{

}

Resource::~Resource()
{
	
}

FormatPtr Resource::getFormat() const
{
	return _format;
}

uint32_t Resource::isStreaming() const
{
	return _isStreaming;
}

uint32_t Resource::isMapped() const
{
	return _isMapped;
}

uint32_t Resource::getWidth() const
{
	return _width;
}

uint32_t Resource::getHeight() const
{
	return _height;
}

uint32_t Resource::getDepth() const
{
	return _depth;
}

uint32_t Resource::getNumDimensions() const
{
	return _numDims;
}

ResourceType Resource::getType() const
{
	return _resourceType;
}
void Resource::initialize() 
{
	if(_width == 0 || _height == 0 || _depth == 0) throw InvalidArgumentException("dimensions invalid");
}


LLGL_NAMESPACE_END;