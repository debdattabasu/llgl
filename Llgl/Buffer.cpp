#include "Library.h"

LLGL_NAMESPACE(Llgl);

Buffer::Buffer(ContextPtr parentContext, uint32_t width, FormatPtr format): 
	ContextChild(parentContext), _width(width), _format(format), _isMapped(false)
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

bool Buffer::isMapped() const
{
	return _isMapped;
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

void Buffer::write(BufferStreamPtr stream, uint32_t offset)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if (!stream->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("stream format mismatch");
	if((offset + stream->getWidth()) > getWidth())
		throw InvalidArgumentException("out of bounds");
	writeImpl(stream, offset);
}

void Buffer::read(BufferStreamPtr stream, uint32_t offset)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if (!stream->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("stream format mismatch");
	if((offset + stream->getWidth()) > getWidth())
		throw InvalidArgumentException("out of bounds");
	readImpl(stream, offset);
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