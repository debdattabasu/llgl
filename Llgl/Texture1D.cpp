#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture1D::Texture1D(ContextPtr parentContext, uint32_t width, uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming): 
	ContextChild(parentContext), _width(width), _numMips(numMips? numMips : uint32_t(1 + floor(log(double(width)) /log(2.f)))), 
	_arraySize(arraySize), _format(format), _isStreaming(isStreaming)
{

}

Texture1D::~Texture1D()
{

}
	
void Texture1D::initialize() 
{
	if(_width == 0 || _numMips ==0 || _arraySize == 0) throw InvalidArgumentException("dimensions invalid");
	_isMapped.resize(_numMips * _arraySize);
	for(auto i : _isMapped) i = 0;

	switch(getFormat()->getUsage())
	{
	case FormatUsage::General:
		break;

	default:
		throw InvalidArgumentException("format type unsupported by Texture1D");
	}
}

FormatPtr Texture1D::getFormat() const
{
	return _format;
}

bool Texture1D::isStreaming() const
{
	return _isStreaming;
}

bool Texture1D::isMapped(uint32_t mipLevel, uint32_t arrayIndex) const
{
	return _isMapped[getNumMips() * arrayIndex + mipLevel];
}

void Texture1D::setMapped(uint32_t mipLevel, uint32_t arrayIndex, bool value)
{
	_isMapped[_numMips * arrayIndex + mipLevel] = value;
}

uint32_t Texture1D::getWidth() const
{
	return _width;
}

uint32_t Texture1D::getNumMips()  const
{
	return _numMips;
}

uint32_t Texture1D::getArraySize() const
{
	return _arraySize;
}

void* Texture1D::map(uint32_t mipLevel, uint32_t arrayIndex, MapType type)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(!_isStreaming) throw InvalidOperationException("can not map non-streaming texture");
	if((mipLevel + 1) > getNumMips() || (arrayIndex + 1) > getArraySize())
		throw InvalidArgumentException("out of bounds");
	if(isMapped(mipLevel, arrayIndex)) throw InvalidOperationException("texture already mapped");
	auto ret = mapImpl(mipLevel, arrayIndex, type);
	setMapped(mipLevel, arrayIndex, 1);
	return ret; 
}

void Texture1D::unmap(uint32_t mipLevel, uint32_t arrayIndex)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(!isMapped(mipLevel, arrayIndex)) throw InvalidOperationException("texture already unmapped");
	unmapImpl(mipLevel, arrayIndex);
	setMapped(mipLevel, arrayIndex, 0);
}

void Texture1D::copyFrom(Texture1DPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
	uint32_t destOffset, uint32_t destMipLevel, uint32_t destArrayIndex)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("resource format mismatch");

	if((srcOffset + srcWidth) > src->getWidth() || (destOffset + srcWidth) > getWidth() 
	   	|| (srcMipLevel + 1) > src->getNumMips() || (srcArrayIndex + 1) > src->getArraySize() 
	   	|| (destMipLevel + 1) > getNumMips() || (destArrayIndex + 1) > getArraySize())
			throw InvalidArgumentException("out of bounds");

	copyFromImpl(src, srcOffset, srcWidth, srcMipLevel, srcArrayIndex, 
		destOffset, destMipLevel, destArrayIndex);
}


LLGL_NAMESPACE_END;