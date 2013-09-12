#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture1D) : public Resource
{
public:
	virtual ~Texture1D() override;
protected:
	Texture1D(ContextPtr parentContext, uint32_t width, uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming);
	virtual void initialize() override;
};

LLGL_NAMESPACE_END;