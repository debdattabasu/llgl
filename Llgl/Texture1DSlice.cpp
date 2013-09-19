#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture1DSlice::Texture1DSlice(Texture1DPtr parentTexture, uint32_t mipLevel): 
	ContextChild(parentTexture->getParentContext()), _parentTexture(parentTexture), _mipLevel(mipLevel)
{

}

Texture1DSlice::~Texture1DSlice()
{

}
	
void Texture1DSlice::initialize() 
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if((_mipLevel + 1) > getParentTexture()->getNumMips()) 
		throw InvalidArgumentException("out of bounds");
	initializeImpl();
}

Texture1DPtr Texture1DSlice::getParentTexture() const
{
	return _parentTexture;
}

FormatPtr Texture1DSlice::getFormat() const
{
	return getParentTexture()->getFormat();
}

uint32_t Texture1DSlice::getMipLevel() const
{
	return _mipLevel;
}

uint32_t Texture1DSlice::getWidth() const
{
	return getParentTexture()->getWidth(getMipLevel());
}

void Texture1DSlice::copyFrom(Texture1DSlicePtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("format mismatch");
	if(srcWidth == 0) throw InvalidArgumentException("invalid dimensions");
	if((srcOffset + srcWidth) > src->getWidth() || (destOffset + srcWidth) > getWidth())
		throw InvalidArgumentException("out of bounds");	   	
	copyFromImpl(src, srcOffset, srcWidth, destOffset);
}

LLGL_NAMESPACE_END;