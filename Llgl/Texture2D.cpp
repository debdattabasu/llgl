#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture2D::Texture2D(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming)
	: Resource(parentContext, ResourceType::Texture2D, width, height,
		numMips? numMips : uint32_t(1 + floor(log(double(width)) /log(2.f))), arraySize, format, isStreaming)
{

}

Texture2D::~Texture2D()
{

}
	
void Texture2D::initialize() 
{
	Resource::initialize();

	switch(getFormat()->getUsage())
	{
	case FormatUsage::General:
		break;
	case FormatUsage::DepthTexture:
		break;
	default:
		throw InvalidArgumentException("format type unsupported by Texture2D");
	}
}

LLGL_NAMESPACE_END;