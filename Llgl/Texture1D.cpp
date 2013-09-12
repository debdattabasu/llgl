#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture1D::Texture1D(ContextPtr parentContext, uint32_t width, uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming)
	: Resource(parentContext, ResourceType::Texture1D, width, 
		numMips? numMips : uint32_t(1 + floor(log(double(width)) /log(2.f))), arraySize, format, isStreaming)
{

}

Texture1D::~Texture1D()
{

}
	
void Texture1D::initialize() 
{
	Resource::initialize();
	switch(getFormat()->getUsage())
	{
	case FormatUsage::General:
		break;

	default:
		throw InvalidArgumentException("format type unsupported by Texture1D");
	}
}

LLGL_NAMESPACE_END;