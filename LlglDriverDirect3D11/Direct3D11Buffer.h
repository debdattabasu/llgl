#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Buffer) : public Buffer
{
public:
	Direct3D11Buffer(ContextPtr parentContext, uint32_t width, FormatPtr format, bool isStreaming);
	~Direct3D11Buffer() override;

	void* mapImpl(uint32_t mipLevel, uint32_t arrayIndex, MapType type) override;
	void unmapImpl(uint32_t mipLevel, uint32_t arrayIndex) override;
	void copyFromImpl(ResourcePtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ, 
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
		uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ, 
		uint32_t destMipLevel, uint32_t destArrayIndex) override;


	void initialize() override;
	void initializeStreaming();
	void initializeRaw();
	void initializeVertexIndex();

	ID3D11Buffer* _buf;
	ID3D11ShaderResourceView* _srv;
	ID3D11UnorderedAccessView* _uav;
};

LLGL_NAMESPACE_END2;