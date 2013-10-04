#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture2DUnorderedAccessView) : public Texture2DUnorderedAccessView
{
public:
	Direct3D11Texture2DUnorderedAccessView(Texture2DPtr parentTexture, uint32_t mipLevel);
	~Direct3D11Texture2DUnorderedAccessView() override;
	void initializeDriver() override;

private:
	ID3D11UnorderedAccessView* _uav;
};

LLGL_NAMESPACE_END2;