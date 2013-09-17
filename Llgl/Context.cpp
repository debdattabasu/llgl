#include "Library.h"

LLGL_NAMESPACE(Llgl);

Context::Context()
{

}

Context::~Context()
{

}

BufferPtr Context::createBuffer(uint32_t width, FormatPtr format, bool isStreaming)
{
	auto ret = createBufferImpl(width, format, isStreaming);
	ret->initialize();
	return ret;
}

Texture1DPtr Context::createTexture1D(uint32_t width, uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming)
{
	auto ret = createTexture1DImpl(width, numMips, arraySize, format, isStreaming);
	ret->initialize();
	return ret;
}

Texture2DPtr Context::createTexture2D(uint32_t width, uint32_t height, uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming)
{
	auto ret = createTexture2DImpl(width, height, numMips, arraySize, format, isStreaming);
	ret->initialize();
	return ret;
}

Texture3DPtr Context::createTexture3D(uint32_t width, uint32_t height, uint32_t depth, uint32_t numMips, FormatPtr format, bool isStreaming)
{
	auto ret = createTexture3DImpl(width, height, depth, numMips, format, isStreaming);
	ret->initialize();
	return ret;
}

FormatPtr Context::createFormat(FormatType type, uint32_t vectorSize)
{
	auto ret = createFormatImpl(type, vectorSize);
	ret->initialize();
	return ret;
}




LLGL_NAMESPACE_END;
