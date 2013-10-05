#include "Library.h"

LLGL_NAMESPACE(Llgl);

Context::Context()
{

}

Context::~Context()
{

}

Context::LockGuard::LockGuard(ContextPtr ctx) : _ctx(ctx) 
{
	_ctx->_mutex.lock();
}

Context::LockGuard::~LockGuard()
{
	_ctx->_mutex.unlock();
}

BufferPtr Context::createBuffer(uint32_t width, FormatPtr format)
{
	auto ret = createBufferDriver(width, format);
	ret->initialize();
	return ret;
}

Texture1DPtr Context::createTexture1D(uint32_t width, uint32_t numMips, uint32_t arraySize, FormatPtr format)
{
	auto ret = createTexture1DDriver(width, numMips, arraySize, format);
	ret->initialize();
	return ret;
}

Texture2DPtr Context::createTexture2D(uint32_t width, uint32_t height, uint32_t numMips, uint32_t arraySize, FormatPtr format)
{
	auto ret = createTexture2DDriver(width, height, numMips, arraySize, format);
	ret->initialize();
	return ret;
}

Texture3DPtr Context::createTexture3D(uint32_t width, uint32_t height, uint32_t depth, uint32_t numMips, FormatPtr format)
{
	auto ret = createTexture3DDriver(width, height, depth, numMips, format);
	ret->initialize();
	return ret;
}

FormatPtr Context::createFormat(FormatType type, uint32_t vectorSize)
{
	auto ret = createFormatDriver(type, vectorSize);
	ret->initialize();
	return ret;
}

LLGL_NAMESPACE_END;
