#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture3DSlice::Texture3DSlice(Texture3DPtr parentTexture, uint32_t mipLevel):
	ContextChild(parentTexture->getParentContext()), _parentTexture(parentTexture), _mipLevel(mipLevel)
{

}

Texture3DSlice::~Texture3DSlice()
{

}
	
void Texture3DSlice::initialize() 
{
	Context::LockGuard lock(getParentContext()); 
	if((_mipLevel+1) > getParentTexture()->getNumMips())
		throw InvalidArgumentException("out of bounds");
	initializeImpl();
}

FormatPtr Texture3DSlice::getFormat() const
{
	return getParentTexture()->getFormat();
}

uint32_t Texture3DSlice::getWidth() const
{
	return getParentTexture()->getWidth(getMipLevel());
}

uint32_t Texture3DSlice::getHeight() const
{
	return getParentTexture()->getHeight(getMipLevel());
}

uint32_t Texture3DSlice::getDepth() const
{
	return getParentTexture()->getDepth(getMipLevel());
}

uint32_t Texture3DSlice::getMipLevel()  const
{
	return _mipLevel;
}

Texture3DPtr Texture3DSlice::getParentTexture() const
{
	return _parentTexture;
}

void Texture3DSlice::copyFrom(Texture3DSlicePtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ,
	uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ)
{
	Context::LockGuard lock(getParentContext()); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("format mismatch");
	if(srcWidth == 0 || srcHeight == 0 || srcDepth == 0) throw InvalidArgumentException("invalid dimensions");
	if((srcOffsetX + srcWidth) > src->getWidth() || (destOffsetX + srcWidth) > getWidth() 
	  	|| (srcOffsetY + srcHeight) > src->getHeight() || (destOffsetY + srcHeight) > getHeight()
	  	|| (srcOffsetZ + srcDepth) > src->getDepth() || (destOffsetZ + srcDepth) > getDepth())
			throw InvalidArgumentException("out of bounds");
	copyFromImpl(src, srcOffsetX, srcOffsetY, srcOffsetZ, srcWidth, srcHeight, srcDepth, destOffsetX, destOffsetY, destOffsetZ);
}

LLGL_NAMESPACE_END;