#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture2DDepthStencilView::Texture2DDepthStencilView(Texture2DPtr parentTexture, uint32_t mipLevel, uint32_t arrayIndex) :
	Texture2DView(parentTexture), _mipLevel(mipLevel), _arrayIndex(arrayIndex)
{

}

Texture2DDepthStencilView::~Texture2DDepthStencilView()
{

}

uint32_t Texture2DDepthStencilView::getMipLevel() const
{
	return _mipLevel;	
}

uint32_t Texture2DDepthStencilView::getArrayIndex() const
{
	return _arrayIndex;
}

void Texture2DDepthStencilView::initialize()
{
	if(getMipLevel() + 1 > getParentResource()->getNumMips() 
		|| getArrayIndex() + 1 > getParentResource()->getArraySize())
		throw InvalidArgumentException("out of bounds");
	if(getParentResource()->getFormat()->getUsage() != FormatUsage::DepthTexture)
		throw InvalidOperationException("depth stencil views unsupported by non-depth textures");
	Context::LockGuard lock(getParentContext()); 
	initializeDriver();
}

LLGL_NAMESPACE_END;