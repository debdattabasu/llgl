#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture2DStream::Texture2DStream(ContextPtr parentContext, uint32_t width, uint32_t height, FormatPtr format):
	ContextChild(parentContext), _width(width), _height(height), _format(format), _isMapped(0)
{

}

Texture2DStream::~Texture2DStream()
{

}
	
void Texture2DStream::initialize() 
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(_width == 0 || _height == 0) throw InvalidArgumentException("invalid dimensions");
	switch(getFormat()->getUsage())
	{
	case FormatUsage::General:
		break;
	case FormatUsage::DepthTexture:
		break;
	default:
		throw InvalidArgumentException("format type unsupported by texture2d stream");
	}
	initializeImpl();
}

FormatPtr Texture2DStream::getFormat() const
{
	return _format;
}

bool Texture2DStream::isMapped() const
{
	return _isMapped;
}

uint32_t Texture2DStream::getWidth() const
{
	return _width;
}

uint32_t Texture2DStream::getHeight() const
{
	return _height;
}

Texture2DStream::MapDesc Texture2DStream::map()
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(_isMapped) throw InvalidOperationException("already mapped");
	auto ret = mapImpl();
	_isMapped = 1;
	return ret;
}

void Texture2DStream::unmap()
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(!_isMapped) throw InvalidOperationException("already unmapped");
	unmapImpl();
	_isMapped= 0;
}

void Texture2DStream::copyFrom(Texture2DPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY,
	uint32_t srcWidth, uint32_t srcHeight, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
	uint32_t destOffsetX, uint32_t destOffsetY)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("format mismatch");
	if(srcWidth == 0 || srcHeight == 0) throw InvalidArgumentException("invalid dimensions");
	if((srcMipLevel + 1) > src->getNumMips() || (srcArrayIndex + 1) > src->getArraySize())
	   	throw InvalidArgumentException("out of bounds");
	if((srcOffsetX + srcWidth) > src->getWidth(srcMipLevel) || (destOffsetX + srcWidth) > getWidth() 
	  	|| (srcOffsetY + srcHeight) > src->getHeight(srcMipLevel) || (destOffsetY + srcHeight) > getHeight())
			throw InvalidArgumentException("out of bounds");
	copyFromImpl(src, srcOffsetX, srcOffsetY, srcWidth, srcHeight, srcMipLevel, srcArrayIndex, 
		destOffsetX, destOffsetY);
}

void Texture2DStream::copyFrom(Texture2DStreamPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcWidth, uint32_t srcHeight, 
		uint32_t destOffsetX, uint32_t destOffsetY)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("format mismatch");
	if(srcWidth == 0 || srcHeight == 0) throw InvalidArgumentException("invalid dimensions");
	if((srcOffsetX + srcWidth) > src->getWidth() || (destOffsetX + srcWidth) > getWidth() 
	  	|| (srcOffsetY + srcHeight) > src->getHeight() || (destOffsetY + srcHeight) > getHeight())
			throw InvalidArgumentException("out of bounds");
	copyFromImpl(src, srcOffsetX, srcOffsetY, srcWidth, srcHeight, destOffsetX, destOffsetY);
}

LLGL_NAMESPACE_END;