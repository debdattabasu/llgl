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
	Context::LockGuard lock(getParentContext()); 
	if(isMapped()) throw InvalidOperationException("already mapped");
	auto ret = mapImpl();
	_isMapped = true;
	return ret;
}

void BufferStream::unmap()
{
	Context::LockGuard lock(getParentContext()); 
	if(!isMapped()) throw InvalidOperationException("already unmapped");
	unmapImpl();
	_isMapped = false;
}

void BufferStream::initialize() 
{
	Context::LockGuard lock(getParentContext()); 
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

void BufferStream::readFrom(BufferPtr src, uint32_t offset)
{
	Context::LockGuard lock(getParentContext()); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("format mismatch");
	if((offset + getWidth()) > src->getWidth())
		throw InvalidArgumentException("out of bounds");
	readFromImpl(src, offset);
}

void BufferStream::writeTo(BufferPtr dest, uint32_t offset)
{
	Context::LockGuard lock(getParentContext());  
	if (!dest->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("format mismatch");
	if((offset + getWidth()) > dest->getWidth())
		throw InvalidArgumentException("out of bounds");
	writeToImpl(dest, offset);
}

LLGL_NAMESPACE_END;