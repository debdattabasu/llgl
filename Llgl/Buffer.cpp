#include "Library.h"

LLGL_NAMESPACE(Llgl);

Buffer::Buffer(ContextPtr parentContext, uint32_t width, FormatPtr format, bool isStreaming): 
	ContextChild(parentContext), _width(width), _format(format), 
	_isStreaming(isStreaming), _isMapped(false)
{
}

Buffer::~Buffer()
{

}

uint32_t Buffer::getWidth() const
{
	return _width;
}

FormatPtr Buffer::getFormat() const
{
	return _format;
}

bool Buffer::isStreaming() const
{
	return _isStreaming;
}

bool Buffer::isMapped() const
{
	return _isMapped;
}


void* Buffer::map(MapType type)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(!_isStreaming) throw InvalidOperationException("can not map non-streaming buffer");
	if(isMapped()) throw InvalidOperationException("buffer already mapped");
	auto ret = mapImpl(type);
	_isMapped = true;
	return ret;
}

void Buffer::unmap()
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(!isMapped()) throw InvalidOperationException("resource already unmapped");
	unmapImpl();
	_isMapped = false;
}

void Buffer::copyFrom(BufferPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("resource format mismatch");

	if((srcOffset + srcWidth) > src->getWidth() || (destOffset + srcWidth) > getWidth())
		throw InvalidArgumentException("out of bounds");

	copyFromImpl(src, srcOffset, srcWidth, destOffset);

}

void Buffer::initialize() 
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
			throw InvalidArgumentException("raw buffers unsupported");
		break;

	case FormatUsage::IndexBuffer:
		break;
		
	default:
		throw InvalidArgumentException("format type unsupported by buffers");
	}
	initializeImpl();
}

LLGL_NAMESPACE_END;