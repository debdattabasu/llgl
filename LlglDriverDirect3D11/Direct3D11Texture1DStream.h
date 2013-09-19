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
	void readDataImpl(Texture1DSlicePtr src, uint32_t offset) override;
	void writeDataImpl(Texture1DSlicePtr dest, uint32_t offset) override;

	ID3D11Texture1D* _tex1d;
};

LLGL_NAMESPACE_END2;