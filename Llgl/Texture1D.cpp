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
	if(_width == 0 || _arraySize == 0) throw InvalidArgumentException("invalid dimensions");
	auto maxNumMips = uint32_t(1 + floor(log(double(_width)) /log(2.f)));
	_numMips =  _numMips? _numMips: maxNumMips;
	if(_numMips > maxNumMips) throw InvalidArgumentException("invalid dimensions");
	switch(getFormat()->getUsage())
	{
	case FormatUsage::General:
		break;
	default:
		throw InvalidArgumentException("format type unsupported by texture1d");
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

void Texture1D::copyFrom(Texture1DPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
	uint32_t destOffset, uint32_t destMipLevel, uint32_t destArrayIndex)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("format mismatch");
	if(srcWidth == 0) throw InvalidArgumentException("invalid dimensions");
	if((srcMipLevel + 1) > src->getNumMips() || (srcArrayIndex + 1) > src->getArraySize() 
	   	|| (destMipLevel + 1) > getNumMips() || (destArrayIndex + 1) > getArraySize())
			throw InvalidArgumentException("out of bounds");
	if((srcOffset + srcWidth) > src->getWidth(srcMipLevel) || (destOffset + srcWidth) > getWidth(destMipLevel))
		throw InvalidArgumentException("out of bounds");	   	
	copyFromImpl(src, srcOffset, srcWidth, srcMipLevel, srcArrayIndex, 
		destOffset, destMipLevel, destArrayIndex);
}

void Texture1D::copyFrom(Texture1DStreamPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset, uint32_t destMipLevel, uint32_t destArrayIndex)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("format mismatch");
	if(srcWidth == 0) throw InvalidArgumentException("invalid dimensions");
	if((destMipLevel + 1) > getNumMips() || (destArrayIndex + 1) > getArraySize())
			throw InvalidArgumentException("out of bounds");
	if((srcOffset + srcWidth) > src->getWidth() || (destOffset + srcWidth) > getWidth(destMipLevel))
		throw InvalidArgumentException("out of bounds");	   	
	copyFromImpl(src, srcOffset, srcWidth, destOffset, destMipLevel, destArrayIndex);
}

LLGL_NAMESPACE_END;