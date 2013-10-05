#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture1DUnorderedAccessView::Texture1DUnorderedAccessView(Texture1DPtr parentTexture, uint32_t mipLevel) :
	Texture1DView(parentTexture), _mipLevel(mipLevel)
{

}

Texture1DUnorderedAccessView::~Texture1DUnorderedAccessView()
{

}

uint32_t Texture1DUnorderedAccessView::getMipLevel() const
{
	return _mipLevel;
}

void Texture1DUnorderedAccessView::initialize()
{
	if(!getParentContext()->getCapabilities()->numUnorderedAccessSlots()) 
		throw UnsupportedFeatureException("unordered access views unsupported");
	if(getMipLevel() + 1 > getParentResource()->getNumMips())
		throw InvalidArgumentException("out of bounds");
	Context::LockGuard lock(getParentContext()); 
	initializeDriver();
}

LLGL_NAMESPACE_END;