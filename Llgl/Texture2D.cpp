#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture2D::Texture2D(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t numMips, FormatPtr format):
	ContextChild(parentContext), _width(width), _height(height), _numMips(numMips), _format(format)
{

}

Texture2D::~Texture2D()
{

}
	
void Texture2D::initialize() 
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(_width == 0 || _height == 0 ) throw InvalidArgumentException("invalid dimensions");
	auto maxNumMips = uint32_t(1 + floor(log(double(max(_width, _height))) /log(2.f)));
	_numMips =  _numMips? _numMips: maxNumMips;
	if(_numMips > maxNumMips) throw InvalidArgumentException("invalid dimensions");
	switch(getFormat()->getUsage())
	{
	case FormatUsage::General:
		break;
	case FormatUsage::DepthTexture:
		break;
	default:
		throw InvalidArgumentException("format type unsupported by texture2d");
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

Texture2DSlicePtr Texture2D::getSlice(uint32_t mipLevel)
{
	auto ret = getSliceImpl(mipLevel);
	ret->initialize();
	return ret;
}

LLGL_NAMESPACE_END;