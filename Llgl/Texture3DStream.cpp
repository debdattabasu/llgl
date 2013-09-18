#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture3DStream::Texture3DStream(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t depth, FormatPtr format):
	ContextChild(parentContext), _width(width), _height(height), _depth(depth), _format(format), _isMapped(0)
{

}

Texture3DStream::~Texture3DStream()
{

}
	
void Texture3DStream::initialize() 
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(_width == 0 || _height == 0 || _depth == 0) throw InvalidArgumentException("dimensions invalid");
	switch(getFormat()->getUsage())
	{
	case FormatUsage::General:
		break;
	default:
		throw InvalidArgumentException("format type unsupported by Texture3DStream");
	}
	initializeImpl();
}

FormatPtr Texture3DStream::getFormat() const
{
	return _format;
}

bool Texture3DStream::isMapped() const
{
	return _isMapped;
}

uint32_t Texture3DStream::getWidth() const
{
	return _width;
}

uint32_t Texture3DStream::getHeight() const
{
	return _height;
}

uint32_t Texture3DStream::getDepth() const
{
	return _depth;
}

Texture3DStream::MapDesc Texture3DStream::map()
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(_isMapped) throw InvalidOperationException("Texture3DStream already mapped");
	auto ret = mapImpl();
	_isMapped = 1;
	return ret;
}

void Texture3DStream::unmap()
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(!_isMapped) throw InvalidOperationException("Texture3DStream already unmapped");
	unmapImpl();
	_isMapped = 0;
}

void Texture3DStream::copyFrom(Texture3DPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ,
	uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t srcMipLevel, 
	uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("resource format mismatch");
	if(srcWidth == 0 || srcHeight == 0 || srcDepth == 0) throw InvalidArgumentException("invalid dimensions");
	if((srcMipLevel + 1) > src->getNumMips())
	   	throw InvalidArgumentException("out of bounds");
	if((srcOffsetX + srcWidth) > src->getWidth(srcMipLevel) || (destOffsetX + srcWidth) > getWidth() 
	  	|| (srcOffsetY + srcHeight) > src->getHeight(srcMipLevel) || (destOffsetY + srcHeight) > getHeight()
	  	|| (srcOffsetZ + srcDepth) > src->getDepth(srcMipLevel) || (destOffsetZ + srcDepth) > getDepth())
			throw InvalidArgumentException("out of bounds");
	copyFromImpl(src, srcOffsetX, srcOffsetY, srcOffsetZ, srcWidth, srcHeight, srcDepth, srcMipLevel, 
		destOffsetX, destOffsetY, destOffsetZ);
}

void Texture3DStream::copyFrom(Texture3DStreamPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("resource format mismatch");
	if(srcWidth == 0 || srcHeight == 0 || srcDepth == 0) throw InvalidArgumentException("invalid dimensions");
	if((srcOffsetX + srcWidth) > src->getWidth() || (destOffsetX + srcWidth) > getWidth() 
	  	|| (srcOffsetY + srcHeight) > src->getHeight() || (destOffsetY + srcHeight) > getHeight()
	  	|| (srcOffsetZ + srcDepth) > src->getDepth() || (destOffsetZ + srcDepth) > getDepth())
			throw InvalidArgumentException("out of bounds");
	copyFromImpl(src, srcOffsetX, srcOffsetY, srcOffsetZ, srcWidth, srcHeight, srcDepth, destOffsetX, destOffsetY, destOffsetZ);
}

LLGL_NAMESPACE_END;