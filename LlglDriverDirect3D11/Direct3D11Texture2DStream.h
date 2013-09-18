#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture2DStream) : public Texture2DStream
{
public:
	Direct3D11Texture2DStream(ContextPtr parentContext, uint32_t width, uint32_t height, FormatPtr format);
	~Direct3D11Texture2DStream() override;
	void initializeImpl() override;
	MapDesc mapImpl() override;
	void unmapImpl() override;
	void copyFromImpl(Texture2DPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
		uint32_t destOffsetX, uint32_t destOffsetY) override;
	void copyFromImpl(Texture2DStreamPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcWidth, uint32_t srcHeight, 
		uint32_t destOffsetX, uint32_t destOffsetY) override;
	
	ID3D11Texture2D* _tex2d;
};

LLGL_NAMESPACE_END2;