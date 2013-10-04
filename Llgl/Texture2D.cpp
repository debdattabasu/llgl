#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture2D::Texture2D(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t numMips, FormatPtr format):
	Texture(parentContext, 2, numMips? numMips: uint32_t(1 + floor(log(double(max(width, height))) /log(2.f))), 1, format), 
	_width(width), _height(height)
{

}

Texture2D::~Texture2D()
{

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
	
void Texture2D::initialize() 
{
	Texture::initialize();
	if(_width == 0 || _height == 0) throw InvalidArgumentException("invalid dimensions");

	auto maxNumMips = uint32_t(1 + floor(log(double(max(_width, _height))) /log(2.f)));
	if(getNumMips() > maxNumMips) throw InvalidArgumentException("invalid dimensions");

	switch(getFormat()->getUsage())
	{
	case FormatUsage::General:
		break;
	case FormatUsage::DepthTexture:
		break;
	default:
		throw InvalidArgumentException("format type unsupported by texture2d");
	}

	Context::LockGuard lock(getParentContext()); 
	initializeDriver();
}

Texture2DShaderResourceViewPtr Texture2D::getShaderResourceView()
{
	auto ret = getShaderResourceViewDriver();
	ret->initialize();
	return ret;
}

Texture2DUnorderedAccessViewPtr Texture2D::getUnorderedAccessView(uint32_t mipLevel)
{
	auto ret = getUnorderedAccessViewDriver(mipLevel);
	ret->initialize();
	return ret;
}

Texture2DRenderTargetViewPtr Texture2D::getRenderTargetView(uint32_t mipLevel, uint32_t arrayIndex)
{
	auto ret = getRenderTargetViewDriver(mipLevel, arrayIndex);
	ret->initialize();
	return ret;
}

Texture2DDepthStencilViewPtr Texture2D::getDepthStencilView(uint32_t mipLevel, uint32_t arrayIndex)
{
	auto ret = getDepthStencilViewDriver(mipLevel, arrayIndex);
	ret->initialize();
	return ret;
}

Texture2DDataAccessViewPtr Texture2D::getDataAccessView(uint32_t offsetX, uint32_t offsetY, 
	uint32_t width, uint32_t height, uint32_t mipLevel, uint32_t arrayIndex)
{
	auto ret = getDataAccessViewDriver(offsetX, offsetY, width, height, mipLevel, arrayIndex);
	ret->initialize();
	return ret;
}
LLGL_NAMESPACE_END;