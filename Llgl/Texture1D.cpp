#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture1D::Texture1D(ContextPtr parentContext, uint32_t width, uint32_t numMips, FormatPtr format): 
	Texture(parentContext, 1, numMips? numMips: uint32_t(1 + floor(log(double(width)) /log(2.f))), 1, format), 
	_width(width)
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

Texture1DDataAccessViewPtr Texture1D::getDataAccessView(uint32_t offset, uint32_t width, uint32_t mipLevel, uint32_t arrayIndex)
{
	auto ret = getDataAccessViewDriver(offset, width, mipLevel, arrayIndex);
	ret->initialize();
	return ret;
}

void Texture1D::initialize() 
{
	Texture::initialize();
	if(_width == 0) throw InvalidArgumentException("invalid dimensions");
	
	auto maxNumMips = uint32_t(1 + floor(log(double(_width)) /log(2.f)));
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

Texture1DSlicePtr Texture1D::getSlice(uint32_t mipLevel)
{
	auto ret = getSliceDriver(mipLevel);
	ret->initialize();
	return ret;
}

LLGL_NAMESPACE_END;