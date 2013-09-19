#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture1DSlice) : public Texture1DSlice
{
public:
	Direct3D11Texture1DSlice(Texture1DPtr parentTexture, uint32_t mipLevel);
	~Direct3D11Texture1DSlice() override;
	void initializeImpl() override;
	void copyFromImpl(Texture1DSlicePtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset) override;

	ID3D11UnorderedAccessView* _uav;
};

LLGL_NAMESPACE_END2;