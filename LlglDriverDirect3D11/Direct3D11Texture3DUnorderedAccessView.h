#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture3DUnorderedAccessView) : public Texture3DUnorderedAccessView
{
public:
	Direct3D11Texture3DUnorderedAccessView(Texture3DPtr parentTexture, uint32_t mipLevel);
	~Direct3D11Texture3DUnorderedAccessView() override;
	void initializeDriver() override;
	ID3D11UnorderedAccessView* getDirect3D11UnorderedAccessView() const;

private:
	ID3D11UnorderedAccessView* _uav;
};

LLGL_NAMESPACE_END2;