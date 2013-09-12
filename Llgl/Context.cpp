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

Texture1DPtr Context::createTexture1D(uint32_t width, uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming)
{
	std::lock_guard<std::mutex> lock(_mutex); 
	return createTexture1DImpl(width, numMips, arraySize, format, isStreaming);

}

Texture2DPtr Context::createTexture2D(uint32_t width, uint32_t height, uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming)
{
	std::lock_guard<std::mutex> lock(_mutex); 
	return createTexture2DImpl(width, height, numMips, arraySize, format, isStreaming);
}

LLGL_NAMESPACE_END;
