#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture2D) : public Texture2D
{
public:
	Direct3D11Texture2D(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming);
	~Direct3D11Texture2D() override;
	void initialize() override;
	void initializeStreaming();
	void initializeDefault();

	void* mapImpl(uint32_t mipLevel, uint32_t arrayIndex, MapType type) override;
	void unmapImpl(uint32_t mipLevel, uint32_t arrayIndex) override;
	void copyFromImpl(ResourcePtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ, 
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
		uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ, 
		uint32_t destMipLevel, uint32_t destArrayIndex) override;

	ID3D11Texture2D* _tex2d;
	ID3D11ShaderResourceView* _srv;
	std::vector<ID3D11UnorderedAccessView*> _uavs;
	std::vector<ID3D11DepthStencilView*> _dsvs;
	std::vector<ID3D11RenderTargetView*> _rtvs;
};

LLGL_NAMESPACE_END2;