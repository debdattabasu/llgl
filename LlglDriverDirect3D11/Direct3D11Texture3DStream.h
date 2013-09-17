#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture3DStream) : public Texture3DStream
{
public:
	Direct3D11Texture3DStream(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t depth, FormatPtr format);
	~Direct3D11Texture3DStream() override;
	void initializeImpl() override;

	void* mapImpl() override;
	void unmapImpl() override;

	ID3D11Texture3D* _tex3d;
};

LLGL_NAMESPACE_END2;