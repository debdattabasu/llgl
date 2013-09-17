#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture1D::Texture1D(ContextPtr parentContext, uint32_t width, uint32_t numMips, uint32_t arraySize, FormatPtr format): 
	ContextChild(parentContext), _width(width), _numMips(numMips), _arraySize(arraySize), _format(format)
{

}

Texture1D::~Texture1D()
{

}
	
void Texture1D::initialize() 
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(_width == 0 || _arraySize == 0) throw InvalidArgumentException("dimensions invalid");
	auto maxNumMips = uint32_t(1 + floor(log(double(_width)) /log(2.f)));
	_numMips =  _numMips? _numMips: maxNumMips;
	if(_numMips > maxNumMips) throw InvalidArgumentException("dimensions invalid");

	switch(getFormat()->getUsage())
	{
	case FormatUsage::General:
		break;
	default:
		throw InvalidArgumentException("format type unsupported by Texture1D");
	}
	initializeImpl();
}

FormatPtr Texture1D::getFormat() const
{
	return _format;
}

uint32_t Texture1D::getWidth(uint32_t mipLevel) const
{
	if((mipLevel+1) > getNumMips()) throw InvalidArgumentException("out of bounds");
	return uint32_t(max(1, floor(_width / pow(2 , mipLevel))));
}

uint32_t Texture1D::getNumMips()  const
{
	return _numMips;
}

uint32_t Texture1D::getArraySize() const
{
	return _arraySize;
}

void Texture1D::read(Texture1DStreamPtr stream, uint32_t offset, uint32_t mipLevel, uint32_t arrayIndex)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(!stream->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("stream format mismatch");

	if((offset + stream->getWidth()) > getWidth(mipLevel))
		throw InvalidArgumentException("out of bounds");

	readImpl(stream, offset, mipLevel, arrayIndex);
}

void Texture1D::write(Texture1DStreamPtr stream, uint32_t offset, uint32_t mipLevel, uint32_t arrayIndex)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(!stream->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("stream format mismatch");

	if((offset + stream->getWidth()) > getWidth(mipLevel))
		throw InvalidArgumentException("out of bounds");

	writeImpl(stream, offset, mipLevel, arrayIndex);
}

void Texture1D::copyFrom(Texture1DPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
	uint32_t destOffset, uint32_t destMipLevel, uint32_t destArrayIndex)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("resource format mismatch");

	if(srcWidth == 0) throw InvalidArgumentException("invalid dimensions");

	if((srcMipLevel + 1) > src->getNumMips() || (srcArrayIndex + 1) > src->getArraySize() 
	   	|| (destMipLevel + 1) > getNumMips() || (destArrayIndex + 1) > getArraySize())
			throw InvalidArgumentException("out of bounds");

	if((srcOffset + srcWidth) > src->getWidth(srcMipLevel) || (destOffset + srcWidth) > getWidth(destMipLevel))
		throw InvalidArgumentException("out of bounds");
	   	
	copyFromImpl(src, srcOffset, srcWidth, srcMipLevel, srcArrayIndex, 
		destOffset, destMipLevel, destArrayIndex);
}

LLGL_NAMESPACE_END;