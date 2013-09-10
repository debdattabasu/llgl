#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Capabilities)
{
public:
	virtual bool supportsRawBuffer() = 0;
	virtual bool supportsShaderResourceBuffer() = 0;
	virtual uint32_t numUnorderedAccessSlots() = 0; 

protected:
	Capabilities();
	~Capabilities();
};

LLGL_NAMESPACE_END;