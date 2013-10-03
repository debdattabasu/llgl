#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture2DSlice::Texture2DSlice(Texture2DPtr parentTexture, uint32_t mipLevel):
	ContextChild(parentTexture->getParentContext()), _parentTexture(parentTexture), _mipLevel(mipLevel)
{

}

Texture2DSlice::~Texture2DSlice()
{

}
	
void Texture2DSlice::initialize() 
{
	Context::LockGuard lock(getParentContext()); 
	if((_mipLevel+1) > getParentTexture()->getNumMips())
		throw InvalidArgumentException("out of bounds");
	initializeImpl();
}

FormatPtr Texture2DSlice::getFormat() const
{
	return getParentTexture()->getFormat();
}

uint32_t Texture2DSlice::getWidth() const
{
	return getParentTexture()->getWidth(getMipLevel());
}

uint32_t Texture2DSlice::getHeight() const
{
	return getParentTexture()->getHeight(getMipLevel());
}

uint32_t Texture2DSlice::getMipLevel()  const
{
	return _mipLevel;
}

Texture2DPtr Texture2DSlice::getParentTexture() const
{
	return _parentTexture;
}

void Texture2DSlice::copyFrom(Texture2DSlicePtr src, uint32_t srcOffsetX, uint32_t srcOffsetY,
	uint32_t srcWidth, uint32_t srcHeight, uint32_t destOffsetX, uint32_t destOffsetY)
{
	Context::LockGuard lock(getParentContext()); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("format mismatch");
	if(srcWidth == 0 || srcHeight == 0) throw InvalidArgumentException("invalid dimensions");
	if((srcOffsetX + srcWidth) > src->getWidth() || (destOffsetX + srcWidth) > getWidth() 
	  	|| (srcOffsetY + srcHeight) > src->getHeight() || (destOffsetY + srcHeight) > getHeight())
			throw InvalidArgumentException("out of bounds");
	copyFromImpl(src, srcOffsetX, srcOffsetY, srcWidth, srcHeight, destOffsetX, destOffsetY);
}

LLGL_NAMESPACE_END;