#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture3DUnorderedAccessView::Texture3DUnorderedAccessView(Texture3DPtr parentTexture, uint32_t mipLevel) :
	Texture3DView(parentTexture), _mipLevel(mipLevel)
{

}

Texture3DUnorderedAccessView::~Texture3DUnorderedAccessView()
{

}

uint32_t Texture3DUnorderedAccessView::getMipLevel() const
{
	return _mipLevel;
}

void Texture3DUnorderedAccessView::initialize()
{
	if(_mipLevel +1 > getParentResource()->getNumMips())
		throw InvalidArgumentException("out of bounds");

	if(!getParentContext()->getCapabilities()->numUnorderedAccessSlots()) 
		throw UnsupportedFeatureException("unordered access views unsupported");
	if(getParentResource()->getFormat()->getUsage() == FormatUsage::DepthTexture)
		throw InvalidOperationException("unordered access views unsupported by depth textures");
	Context::LockGuard lock(getParentContext()); 
	initializeDriver();
}

LLGL_NAMESPACE_END;