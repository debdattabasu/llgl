#include "Library.h"

LLGL_NAMESPACE(Llgl);

Context::Context()
{

}

Context::~Context()
{

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

LLGL_NAMESPACE_END;
