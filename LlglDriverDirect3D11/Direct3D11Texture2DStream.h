#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture2DStream) : public Texture2DStream
{
public:
	Direct3D11Texture2DStream(ContextPtr parentContext, uint32_t width, uint32_t height, FormatPtr format);
	~Direct3D11Texture2DStream() override;
	void initializeDriver() override;
	MapDesc mapDriver() override;
	void unmapDriver() override;
	void readFromDriver(Texture2DSlicePtr src, uint32_t offsetX, uint32_t offsetY) override;
	void writeToDriver(Texture2DSlicePtr dest, uint32_t offsetX, uint32_t offsetY) override;
	
	ID3D11Texture2D* _tex2d;
};

LLGL_NAMESPACE_END2;