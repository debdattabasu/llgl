#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture2DSlice) : public Texture2DSlice
{
public:
	Direct3D11Texture2DSlice(Texture2DPtr parentTexture, uint32_t mipLevel);
	~Direct3D11Texture2DSlice() override;
	void initializeImpl() override;
	void copyFromImpl(Texture2DSlicePtr src, uint32_t srcOffsetX, uint32_t srcOffsetY,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t destOffsetX, uint32_t destOffsetY) override;

	ID3D11UnorderedAccessView* _uav;
	ID3D11DepthStencilView* _dsv;
	ID3D11RenderTargetView* _rtv;

};

LLGL_NAMESPACE_END2;