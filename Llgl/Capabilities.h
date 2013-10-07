#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Capabilities) : public ContextChild
{
public:
	virtual ~Capabilities();
	virtual bool supportsStructuredBuffer() = 0;
	virtual bool supportsShaderResourceBuffer() = 0;
	virtual uint32_t numUnorderedAccessSlots() = 0;
protected:
	Capabilities(ContextPtr parentContext);
};

LLGL_NAMESPACE_END;