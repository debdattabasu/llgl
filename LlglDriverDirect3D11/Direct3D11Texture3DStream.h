#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture3DStream) : public Texture3DStream
{
public:
	Direct3D11Texture3DStream(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t depth, FormatPtr format);
	~Direct3D11Texture3DStream() override;
	void initializeImpl() override;
	MapDesc mapImpl() override;
	void unmapImpl() override;
	void copyFromImpl(Texture3DPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t srcMipLevel, 
		uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ) override;
	void copyFromImpl(Texture3DStreamPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ) override;

	ID3D11Texture3D* _tex3d;
};

LLGL_NAMESPACE_END2;