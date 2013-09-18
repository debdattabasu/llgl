#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture1DStream) : public Texture1DStream
{
public:
	Direct3D11Texture1DStream(ContextPtr parentContext, uint32_t width, FormatPtr format);
	~Direct3D11Texture1DStream() override;
	void initializeImpl() override;
	MapDesc mapImpl() override;
	void unmapImpl() override;
	void copyFromImpl(Texture1DPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
		uint32_t destOffset) override;
	void copyFromImpl(Texture1DStreamPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset) override;

	ID3D11Texture1D* _tex1d;
};

LLGL_NAMESPACE_END2;