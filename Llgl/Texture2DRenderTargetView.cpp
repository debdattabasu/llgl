#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture2DRenderTargetView::Texture2DRenderTargetView(Texture2DPtr parentTexture, uint32_t mipLevel, uint32_t arrayIndex) :
	Texture2DView(parentTexture), _mipLevel(mipLevel), _arrayIndex(arrayIndex)
{

}

Texture2DRenderTargetView::~Texture2DRenderTargetView()
{

}

uint32_t Texture2DRenderTargetView::getMipLevel() const
{
	return _mipLevel;	
}

uint32_t Texture2DRenderTargetView::getArrayIndex() const
{
	return _arrayIndex;
}

void Texture2DRenderTargetView::initialize()
{
	if(getMipLevel() + 1 > getParentResource()->getNumMips() 
		|| getArrayIndex() + 1 > getParentResource()->getArraySize())
		throw InvalidArgumentException("out of bounds");
	if(getParentResource()->getFormat()->getUsage() == FormatUsage::DepthTexture)
		throw InvalidOperationException("render target views unsupported by depth textures");
	Context::LockGuard lock(getParentContext()); 
	initializeDriver();
}

LLGL_NAMESPACE_END;