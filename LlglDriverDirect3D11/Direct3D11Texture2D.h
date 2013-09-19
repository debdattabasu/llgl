#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture2D) : public Texture2D
{
public:
	Direct3D11Texture2D(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t numMips, FormatPtr format);
	~Direct3D11Texture2D() override;
	void initializeImpl() override;
	Texture2DSlicePtr getSliceImpl(uint32_t mipLevel) override;

	ID3D11Texture2D* _tex2d;
	ID3D11ShaderResourceView* _srv;
};

LLGL_NAMESPACE_END2;