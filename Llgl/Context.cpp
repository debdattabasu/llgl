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
	auto ret = createBufferImpl(width, format);
	ret->initialize();
	return ret;
}

BufferStreamPtr Context::createBufferStream(uint32_t width, FormatPtr format)
{
	auto ret = createBufferStreamImpl(width, format);
	ret->initialize();
	return ret;
}

Texture1DPtr Context::createTexture1D(uint32_t width, uint32_t numMips, FormatPtr format)
{
	auto ret = createTexture1DImpl(width, numMips, format);
	ret->initialize();
	return ret;
}

Texture1DStreamPtr Context::createTexture1DStream(uint32_t width, FormatPtr format)
{
	auto ret = createTexture1DStreamImpl(width, format);
	ret->initialize();
	return ret;
}

Texture2DPtr Context::createTexture2D(uint32_t width, uint32_t height, uint32_t numMips, FormatPtr format)
{
	auto ret = createTexture2DImpl(width, height, numMips, format);
	ret->initialize();
	return ret;
}

Texture2DStreamPtr Context::createTexture2DStream(uint32_t width, uint32_t height, FormatPtr format)
{
	auto ret = createTexture2DStreamImpl(width, height, format);
	ret->initialize();
	return ret;
}

Texture3DPtr Context::createTexture3D(uint32_t width, uint32_t height, uint32_t depth, uint32_t numMips, FormatPtr format)
{
	auto ret = createTexture3DImpl(width, height, depth, numMips, format);
	ret->initialize();
	return ret;
}

Texture3DStreamPtr Context::createTexture3DStream(uint32_t width, uint32_t height, uint32_t depth, FormatPtr format)
{
	auto ret = createTexture3DStreamImpl(width, height, depth, format);
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
