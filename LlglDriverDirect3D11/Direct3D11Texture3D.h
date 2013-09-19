#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture3D) : public Texture3D
{
public:
	Direct3D11Texture3D(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t depth, uint32_t numMips, FormatPtr format);
	~Direct3D11Texture3D() override;
	void initializeImpl() override;
	Texture3DSlicePtr getSliceImpl(uint32_t mipLevel) override;

	ID3D11Texture3D* _tex3d;
	ID3D11ShaderResourceView* _srv;
};

LLGL_NAMESPACE_END2;