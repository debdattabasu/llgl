#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Capabilities) : public Capabilities
{
public:
	Direct3D11Capabilities(ContextPtr parentContext);
	~Direct3D11Capabilities() override;
	bool supportsStructuredBuffer() override;
	bool supportsShaderResourceBuffer() override;
	uint32_t numUnorderedAccessSlots() override;
	
	D3D_FEATURE_LEVEL _featureLevel;
};

LLGL_NAMESPACE_END2;