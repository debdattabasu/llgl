#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture3DSlice) : public Texture3DSlice
{
public:
	Direct3D11Texture3DSlice(Texture3DPtr parentTexture, uint32_t mipLevel);
	~Direct3D11Texture3DSlice() override;
	void initializeDriver() override;
	void copyFromDriver(Texture3DSlicePtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ) override;

	ID3D11UnorderedAccessView* _uav;

};

LLGL_NAMESPACE_END2;