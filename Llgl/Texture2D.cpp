#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture2D::Texture2D(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t numMips, uint32_t arraySize, FormatPtr format):
	ContextChild(parentContext), _width(width), _height(height), _numMips(numMips), _arraySize(arraySize), _format(format)
{

}

Texture2D::~Texture2D()
{

}
	
void Texture2D::initialize() 
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(_width == 0 || _height == 0 || _arraySize == 0) throw InvalidArgumentException("dimensions invalid");
	auto maxNumMips = uint32_t(1 + floor(log(double(max(_width, _height))) /log(2.f)));
	_numMips =  _numMips? _numMips: maxNumMips;
	if(_numMips > maxNumMips) throw InvalidArgumentException("dimensions invalid");
	switch(getFormat()->getUsage())
	{
	case FormatUsage::General:
		break;
	case FormatUsage::DepthTexture:
		break;
	default:
		throw InvalidArgumentException("format type unsupported by Texture2D");
	}
	initializeImpl();
}

FormatPtr Texture2D::getFormat() const
{
	return _format;
}

uint32_t Texture2D::getWidth(uint32_t mipLevel) const
{
	if((mipLevel + 1) > getNumMips()) throw InvalidArgumentException("out of bounds");
	return uint32_t(max(1, floor(_width / pow(2 , mipLevel))));
}

uint32_t Texture2D::getHeight(uint32_t mipLevel) const
{
	if((mipLevel+1) > getNumMips()) throw InvalidArgumentException("out of bounds");
	return uint32_t(max(1, floor(_height / pow(2 , mipLevel))));
}

uint32_t Texture2D::getNumMips()  const
{
	return _numMips;
}

uint32_t Texture2D::getArraySize() const
{
	return _arraySize;
}

void Texture2D::copyFrom(Texture2DPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY,
	uint32_t srcWidth, uint32_t srcHeight, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
	uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destMipLevel, uint32_t destArrayIndex)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("resource format mismatch");
	if(srcWidth == 0 || srcHeight == 0) throw InvalidArgumentException("invalid dimensions");
	if((srcMipLevel + 1) > src->getNumMips() || (srcArrayIndex + 1) > src->getArraySize() 
	   	|| (destMipLevel + 1) > getNumMips() || (destArrayIndex + 1) > getArraySize())
	   	throw InvalidArgumentException("out of bounds");
	if((srcOffsetX + srcWidth) > src->getWidth(srcMipLevel) || (destOffsetX + srcWidth) > getWidth(destMipLevel) 
	  	|| (srcOffsetY + srcHeight) > src->getHeight(srcMipLevel) || (destOffsetY + srcHeight) > getHeight(destMipLevel))
			throw InvalidArgumentException("out of bounds");
	copyFromImpl(src, srcOffsetX, srcOffsetY, srcWidth, srcHeight, srcMipLevel, srcArrayIndex, 
		destOffsetX, destOffsetY, destMipLevel, destArrayIndex);
}

void Texture2D::read(Texture2DStreamPtr stream, uint32_t offsetX, uint32_t offsetY, uint32_t mipLevel, uint32_t arrayIndex)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(!stream->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("stream format mismatch");
	if((offsetX + stream->getWidth()) > getWidth(mipLevel)
		|| (offsetY + stream->getHeight()) > getHeight(mipLevel))
		throw InvalidArgumentException("out of bounds");
	readImpl(stream, offsetX, offsetY, mipLevel, arrayIndex);
}

void Texture2D::write(Texture2DStreamPtr stream, uint32_t offsetX, uint32_t offsetY, uint32_t mipLevel, uint32_t arrayIndex)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(!stream->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("stream format mismatch");
	if((offsetX + stream->getWidth()) > getWidth(mipLevel)
		|| (offsetY + stream->getHeight()) > getHeight(mipLevel))
		throw InvalidArgumentException("out of bounds");
	writeImpl(stream, offsetX, offsetY, mipLevel, arrayIndex);
}

LLGL_NAMESPACE_END;