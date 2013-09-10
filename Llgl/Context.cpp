#include "Library.h"

LLGL_NAMESPACE(Llgl);

Context::Context()
{

}

Context::~Context()
{

}

void Context::checkChild(ContextChildPtr child)
{
	if(child->getParentContext()!= shared_from_this()) 
		throw InvalidArgumentException("context mismatch");
}

FormatPtr Context::createFormat(FormatType type, uint32_t vectorSize)
{
	std::lock_guard<std::mutex> lock(_mutex); 
	return createFormatImpl(type, vectorSize);
}

BufferPtr Context::createBuffer(uint32_t width, FormatPtr format, bool isStreaming)
{
	std::lock_guard<std::mutex> lock(_mutex); 
	return createBufferImpl(width, format, isStreaming);
}

void* Context::mapResource(ResourcePtr resource, MapType type)
{
	std::lock_guard<std::mutex> lock(_mutex); 
	checkChild(resource);
	if(!resource->_isStreaming) throw InvalidOperationException("can not map non-streaming rsource");
	if(resource->_isMapped) throw InvalidOperationException("resource already mapped");
	auto ret = mapResourceImpl(resource, type);
	resource->_isMapped = true;
	return ret;

}

void Context::unmapResource(ResourcePtr resource)
{
	std::lock_guard<std::mutex> lock(_mutex); 
	checkChild(resource);
	if(!resource->_isMapped) throw InvalidOperationException("resource already unmapped");
	unmapResourceImpl(resource);
	resource->_isMapped = false;
}

LLGL_NAMESPACE_END;
