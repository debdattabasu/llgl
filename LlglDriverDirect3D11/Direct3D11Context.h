#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Context) : public Context
{
public:
	Direct3D11Context();
	~Direct3D11Context() override;
	CapabilitiesPtr getCapabilities() override;
	BufferPtr createBufferImpl(uint32_t width, FormatPtr format, bool isStreaming) override;
	FormatPtr createFormatImpl(FormatType type, uint32_t vectorSize) override;
	void initialize();
	void* mapResourceImpl(ResourcePtr resource, MapType type) override;
	void unmapResourceImpl(ResourcePtr resource) override;
	void copyBufferImpl(BufferPtr srcBuffer, uint32_t srcWidth, uint32_t srcOffset, BufferPtr destBuffer, uint32_t destOffset) override;

	void copyResourceImpl(ResourcePtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ, 
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
		ResourcePtr dest, uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ, 
		uint32_t destMipLevel, uint32_t destArrayIndex) override;

	ID3D11Device* _dev;
	ID3D11DeviceContext* _ctx;
	D3D_FEATURE_LEVEL _featureLevel;
};

LLGL_NAMESPACE_END2;