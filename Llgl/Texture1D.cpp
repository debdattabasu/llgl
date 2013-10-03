#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture1D::Texture1D(ContextPtr parentContext, uint32_t width, uint32_t numMips, FormatPtr format): 
	ContextChild(parentContext), _width(width), _numMips(numMips), _format(format)
{

}

Texture1D::~Texture1D()
{

}
	
void Texture1D::initialize() 
{
	Context::LockGuard lock(getParentContext()); 
	if(_width == 0) throw InvalidArgumentException("invalid dimensions");
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

Texture1DSlicePtr Texture1D::getSlice(uint32_t mipLevel)
{
	auto ret = getSliceImpl(mipLevel);
	ret->initialize();
	return ret;
}

LLGL_NAMESPACE_END;