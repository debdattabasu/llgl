#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture3D::Texture3D(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t depth, uint32_t numMips, FormatPtr format, bool isStreaming):
	ContextChild(parentContext), _width(width), _height(height), _depth(depth), _numMips(numMips), _format(format), _isStreaming(isStreaming)
{

}

Texture3D::~Texture3D()
{

}
	
void Texture3D::initialize() 
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(_width == 0 || _height == 0 || _depth == 0) throw InvalidArgumentException("dimensions invalid");
	auto maxNumMips = uint32_t(1 + floor(log(double(max(max(_width, _height), _depth))) /log(2.f)));
	_numMips =  _numMips? _numMips: maxNumMips;
	if(_numMips > maxNumMips) throw InvalidArgumentException("dimensions invalid");

	_isMapped.resize(_numMips);
	for(auto i : _isMapped) i = 0;

	switch(getFormat()->getUsage())
	{
	case FormatUsage::General:
		break;
	default:
		throw InvalidArgumentException("format type unsupported by Texture3D");
	}
	initializeImpl();
}

FormatPtr Texture3D::getFormat() const
{
	return _format;
}

bool Texture3D::isStreaming() const
{
	return _isStreaming;
}

bool Texture3D::isMapped(uint32_t mipLevel) const
{
	if((mipLevel + 1) > getNumMips()) throw InvalidArgumentException("out of bounds");
	return _isMapped[mipLevel];
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

void* Texture3D::map(uint32_t mipLevel, MapType type)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(!_isStreaming) throw InvalidOperationException("can not map non-streaming texture");
	if(isMapped(mipLevel)) throw InvalidOperationException("resource already mapped");
	auto ret = mapImpl(mipLevel, type);
	_isMapped[mipLevel] = 1;
	return ret;
}

void Texture3D::unmap(uint32_t mipLevel)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(!isMapped(mipLevel)) throw InvalidOperationException("resource already unmapped");
	unmapImpl(mipLevel);
	_isMapped[mipLevel] = 0;
}

void Texture3D::copyFrom(Texture3DPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ,
	uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t srcMipLevel, 
	uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ, uint32_t destMipLevel)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("resource format mismatch");

	if(srcWidth == 0 || srcHeight == 0 || srcDepth == 0) throw InvalidArgumentException("invalid dimensions");

	if((srcMipLevel + 1) > src->getNumMips() || (destMipLevel + 1) > getNumMips())
	   	throw InvalidArgumentException("out of bounds");

	if((srcOffsetX + srcWidth) > src->getWidth(srcMipLevel) || (destOffsetX + srcWidth) > getWidth(destMipLevel) 
	  	|| (srcOffsetY + srcHeight) > src->getHeight(srcMipLevel) || (destOffsetY + srcHeight) > getHeight(destMipLevel)
	  	|| (srcOffsetZ + srcDepth) > src->getDepth(srcMipLevel) || (destOffsetZ + srcDepth) > getDepth(destMipLevel))
			throw InvalidArgumentException("out of bounds");

	copyFromImpl(src, srcOffsetX, srcOffsetY, srcOffsetZ, srcWidth, srcHeight, srcDepth, srcMipLevel, 
		destOffsetX, destOffsetY, destOffsetZ, destMipLevel);

}

LLGL_NAMESPACE_END;