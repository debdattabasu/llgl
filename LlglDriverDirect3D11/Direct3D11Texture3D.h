#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture3D) : public Texture3D
{
public:
	Direct3D11Texture3D(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t depth, uint32_t numMips, FormatPtr format);
	~Direct3D11Texture3D() override;
	void initializeImpl() override;
	void copyFromImpl(Texture3DPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t srcMipLevel, 
		uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ, uint32_t destMipLevel) override;
	void readImpl(Texture3DStreamPtr stream, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ, uint32_t mipLevel) override;
	void writeImpl(Texture3DStreamPtr stream, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ, uint32_t mipLevel) override;

	ID3D11Texture3D* _tex3d;
	ID3D11ShaderResourceView* _srv;
	std::vector<ID3D11UnorderedAccessView*> _uavs;
};

LLGL_NAMESPACE_END2;