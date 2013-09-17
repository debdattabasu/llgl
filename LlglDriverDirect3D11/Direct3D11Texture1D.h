#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture1D) : public Texture1D
{
public:
	Direct3D11Texture1D(ContextPtr parentContext, uint32_t width, uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming);
	~Direct3D11Texture1D() override;
	void initializeImpl() override;
	void initializeStreaming();
	void initializeDefault();

	void* mapImpl(uint32_t mipLevel, uint32_t arrayIndex, MapType type) override;
	void unmapImpl(uint32_t mipLevel, uint32_t arrayIndex) override;
	void copyFromImpl(Texture1DPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
		uint32_t destOffset, uint32_t destMipLevel, uint32_t destArrayIndex) override;

	ID3D11Texture1D* _tex1d;
	ID3D11ShaderResourceView* _srv;
	std::vector<ID3D11UnorderedAccessView*> _uavs;
};

LLGL_NAMESPACE_END2;