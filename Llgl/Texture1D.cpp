#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture1D::Texture1D(ContextPtr parentContext, uint32_t width, uint32_t numMips, FormatPtr format): 
	Resource(parentContext, 1, format), _width(width), _numMips(numMips), _arraySize(0)
{

}

Texture1D::~Texture1D()
{

}

uint32_t Texture1D::getWidth(uint32_t mipLevel) const
{
	if((mipLevel + 1) > getNumMips()) throw InvalidArgumentException("out of bounds");
	return uint32_t(max(1, floor(_width / pow(2 , mipLevel))));
}

uint32_t Texture1D::getNumMips() const
{
	return _numMips;
}

uint32_t Texture1D::getArraySize() const
{
	return _arraySize;
}

Texture1DDataAccessViewPtr Texture1D::getDataAccessView(uint32_t offset, uint32_t width, uint32_t mipLevel, uint32_t arrayIndex)
{
	auto ret = getDataAccessViewDriver(offset, width, mipLevel, arrayIndex);
	ret->initialize();
	return ret;
}

Texture1DShaderResourceViewPtr Texture1D::getShaderResourceView()
{
	auto ret = getShaderResourceViewDriver();
	ret->initialize();
	return ret;
}

Texture1DUnorderedAccessViewPtr Texture1D::getUnorderedAccessView(uint32_t mipLevel)
{
	auto ret = getUnorderedAccessViewDriver(mipLevel);
	ret->initialize();
	return ret;
}

void Texture1D::initialize() 
{
	Resource::initialize();
	if(_width == 0 || _arraySize == 0) throw InvalidArgumentException("invalid dimensions");
	
	auto maxNumMips = uint32_t(1 + floor(log(double(_width)) /log(2.f)));
	_numMips = _numMips? _numMips : maxNumMips;
	if(getNumMips() > maxNumMips) throw InvalidArgumentException("invalid dimensions");

	switch(getFormat()->getUsage())
	{
	case FormatUsage::General:
		break;
	default:
		throw InvalidArgumentException("format type unsupported by texture1d");
	}
	
	Context::LockGuard lock(getParentContext()); 
	initializeDriver();
}

LLGL_NAMESPACE_END;