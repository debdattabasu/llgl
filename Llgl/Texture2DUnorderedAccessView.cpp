#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture2DUnorderedAccessView::Texture2DUnorderedAccessView(Texture2DPtr parentTexture, uint32_t mipLevel) :
	Texture2DView(parentTexture), _mipLevel(mipLevel)
{

}

Texture2DUnorderedAccessView::~Texture2DUnorderedAccessView()
{

}

uint32_t Texture2DUnorderedAccessView::getMipLevel() const
{
	return _mipLevel;
}

void Texture2DUnorderedAccessView::initialize()
{
	if(!getParentContext()->getCapabilities()->numUnorderedAccessSlots()) 
		throw UnsupportedFeatureException("unordered access views unsupported");
	if(getParentResource()->getFormat()->getUsage() == FormatUsage::DepthTexture)
		throw InvalidOperationException("unordered access views unsupported by depth textures");
	Context::LockGuard lock(getParentContext()); 
	initializeDriver();
}

LLGL_NAMESPACE_END;