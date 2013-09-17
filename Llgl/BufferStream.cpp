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

void* BufferStream::map()
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(isMapped()) throw InvalidOperationException("buffer already mapped");
	auto ret = mapImpl();
	_isMapped = true;
	return ret;
}

void BufferStream::unmap()
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(!isMapped()) throw InvalidOperationException("resource already unmapped");
	unmapImpl();
	_isMapped = false;
}

void BufferStream::initialize() 
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(_width == 0) throw InvalidArgumentException("dimensions invalid");
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

LLGL_NAMESPACE_END;