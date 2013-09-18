#include "Library.h"

LLGL_NAMESPACE(Llgl);

BufferStream::BufferStream(ContextPtr parentContext, uint32_t width, FormatPtr format): 
	ContextChild(parentContext), _width(width), _format(format), _isMapped(0)
{
	
}

BufferStream::~BufferStream()
{

}

uint32_t BufferStream::getWidth() const
{
	return _width;
}

FormatPtr BufferStream::getFormat() const
{
	return _format;
}

bool BufferStream::isMapped() const
{
	return _isMapped;
}

BufferStream::MapDesc BufferStream::map()
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(isMapped()) throw InvalidOperationException("already mapped");
	auto ret = mapImpl();
	_isMapped = true;
	return ret;
}

void BufferStream::unmap()
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(!isMapped()) throw InvalidOperationException("already unmapped");
	unmapImpl();
	_isMapped = false;
}

void BufferStream::initialize() 
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(_width == 0) throw InvalidArgumentException("invalid dimensions");
	auto caps = getParentContext()->getCapabilities();
	switch(getFormat()->getUsage())
	{
	case FormatUsage::General:
		break;
	case FormatUsage::RawBuffer:
		if(!caps->supportsRawBuffer())
			throw InvalidArgumentException("raw buffer streams unsupported");
		break;
	case FormatUsage::IndexBuffer:
		break;
	default:
		throw InvalidArgumentException("format type unsupported by buffer streams");
	}
	initializeImpl();
}

void BufferStream::copyFrom(BufferPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("format mismatch");
	if((srcOffset + srcWidth) > src->getWidth() || (destOffset + srcWidth) > getWidth())
		throw InvalidArgumentException("out of bounds");
	copyFromImpl(src, srcOffset, srcWidth, destOffset);
}

void BufferStream::copyFrom(BufferStreamPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("format mismatch");
	if((srcOffset + srcWidth) > src->getWidth() || (destOffset + srcWidth) > getWidth())
		throw InvalidArgumentException("out of bounds");
	copyFromImpl(src, srcOffset, srcWidth, destOffset);
}

LLGL_NAMESPACE_END;