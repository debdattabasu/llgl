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

void Context::copyResource(ResourcePtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ, 
	uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
	ResourcePtr dest, uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ, 
	uint32_t destMipLevel, uint32_t destArrayIndex)
{
	std::lock_guard<std::mutex> lock(_mutex); 
	checkChild(src); checkChild(dest);
	if (!src->getFormat()->equals(dest->getFormat()))
		throw InvalidArgumentException("resource format mismatch");

	if (src->getType() != dest->getType())
		throw InvalidArgumentException("resource type mismatch");

	if((srcOffsetX + srcWidth) > src->getWidth() || (destOffsetX + srcWidth) > dest->getWidth() 
	  	|| (srcOffsetY + srcHeight) > src->getHeight() || (destOffsetY + srcHeight) > dest->getHeight()
	   	|| (srcOffsetZ + srcDepth) > src->getDepth() || (destOffsetZ + srcDepth) > dest->getDepth()
	   	|| (srcMipLevel + 1) > src->getNumMips() || (srcArrayIndex + 1) > src->getArraySize() 
	   	|| (destMipLevel + 1) > dest->getNumMips() || (destArrayIndex + 1) > dest->getArraySize())
			throw InvalidArgumentException("out of bounds");

	copyResourceImpl(src, srcOffsetX, srcOffsetY, srcOffsetZ, srcWidth, srcHeight, srcDepth, srcMipLevel, srcArrayIndex, 
	dest, destOffsetX, destOffsetY, destOffsetZ, destMipLevel, destArrayIndex);
}


LLGL_NAMESPACE_END;
