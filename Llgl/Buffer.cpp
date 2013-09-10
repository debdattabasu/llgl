#include "Library.h"

LLGL_NAMESPACE(Llgl);

Buffer::Buffer(ContextPtr parentContext, uint32_t width, FormatPtr format, bool isStreaming)
	: Resource(parentContext, ResourceType::Buffer, width, format, isStreaming)
{
}

Buffer::~Buffer()
{

}
	
void Buffer::initialize() 
{
	Resource::initialize();
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
}

LLGL_NAMESPACE_END;