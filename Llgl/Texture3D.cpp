#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture3D::Texture3D(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t depth, uint32_t numMips, FormatPtr format):
	ContextChild(parentContext), _width(width), _height(height), _depth(depth), _numMips(numMips), _format(format)
{

}

Texture3D::~Texture3D()
{

}
	
void Texture3D::initialize() 
{
	Context::LockGuard lock(getParentContext()); 
	if(_width == 0 || _height == 0 || _depth == 0) throw InvalidArgumentException("invalid dimensions");
	auto maxNumMips = uint32_t(1 + floor(log(double(max(max(_width, _height), _depth))) /log(2.f)));
	_numMips =  _numMips? _numMips: maxNumMips;
	if(_numMips > maxNumMips) throw InvalidArgumentException("invalid dimensions");
	switch(getFormat()->getUsage())
	{
	case FormatUsage::General:
		break;
	default:
		throw InvalidArgumentException("format type unsupported by texture3d");
	}
	initializeImpl();
}

FormatPtr Texture3D::getFormat() const
{
	return _format;
}

uint32_t Texture3D::getWidth(uint32_t mipLevel) const
{
	if((mipLevel + 1) > getNumMips()) throw InvalidArgumentException("out of bounds");
	return uint32_t(max(1, floor(_width / pow(2 , mipLevel))));
}

uint32_t Texture3D::getHeight(uint32_t mipLevel) const
{
	if((mipLevel+1) > getNumMips()) throw InvalidArgumentException("out of bounds");
	return uint32_t(max(1, floor(_height / pow(2 , mipLevel))));
}

uint32_t Texture3D::getDepth(uint32_t mipLevel) const
{
	if((mipLevel+1) > getNumMips()) throw InvalidArgumentException("out of bounds");
	return uint32_t(max(1, floor(_depth / pow(2 , mipLevel))));
}

uint32_t Texture3D::getNumMips()  const
{
	return _numMips;
}

Texture3DSlicePtr Texture3D::getSlice(uint32_t mipLevel)
{
	auto ret = getSliceImpl(mipLevel);
	ret->initialize();
	return ret;
}

LLGL_NAMESPACE_END;