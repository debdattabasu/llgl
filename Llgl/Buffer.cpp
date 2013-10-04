#include "Library.h"

LLGL_NAMESPACE(Llgl);

Buffer::Buffer(ContextPtr parentContext, uint32_t width, FormatPtr format): 
	Resource(parentContext, 1, format), _width(width)
{
}

Buffer::~Buffer()
{

}

uint32_t Buffer::getWidth() const
{
	return _width;
}

BufferDataAccessViewPtr Buffer::getDataAccessView(uint32_t offset, uint32_t width)
{
	auto ret = getDataAccessViewDriver(offset, width);
	ret->initialize();
	return ret;
}

BufferShaderResourceViewPtr Buffer::getShaderResourceView()
{
	auto ret = getShaderResourceViewDriver();
	ret->initialize();
	return ret;
}

BufferUnorderedAccessViewPtr Buffer::getUnorderedAccessView()
{
	auto ret = getUnorderedAccessViewDriver();
	ret->initialize();
	return ret;
}

BufferVertexArrayViewPtr Buffer::getVertexArrayView()
{
	auto ret = getVertexArrayViewDriver();
	ret->initialize();
	return ret;
}

BufferIndexArrayViewPtr Buffer::getIndexArrayView()
{
	auto ret = getIndexArrayViewDriver();
	ret->initialize();
	return ret;
}

void Buffer::initialize() 
{
	Resource::initialize();
	if(_width == 0) throw InvalidArgumentException("invalid dimensions");
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


	Context::LockGuard lock(getParentContext());
	initializeDriver();
}

LLGL_NAMESPACE_END;