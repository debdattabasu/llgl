#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture1D) : public Texture1D
{
public:
	Direct3D11Texture1D(ContextPtr parentContext, uint32_t width, uint32_t numMips, FormatPtr format);
	~Direct3D11Texture1D() override;
	void initializeImpl() override;
	Texture1DSlicePtr getSliceImpl(uint32_t mipLevel) override;

	ID3D11Texture1D* _tex1d;
	ID3D11ShaderResourceView* _srv;
};

LLGL_NAMESPACE_END2;