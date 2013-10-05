#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture2D) : public Texture2D
{
public:
	Direct3D11Texture2D(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t numMips, FormatPtr format);
	~Direct3D11Texture2D() override;
	void initializeDriver() override;
	Texture2DShaderResourceViewPtr getShaderResourceViewDriver() override;
	Texture2DUnorderedAccessViewPtr getUnorderedAccessViewDriver(uint32_t mipLevel) override;
	Texture2DRenderTargetViewPtr getRenderTargetViewDriver(uint32_t mipLevel, uint32_t arrayIndex) override;
	Texture2DDepthStencilViewPtr getDepthStencilViewDriver(uint32_t mipLevel, uint32_t arrayIndex) override;
	Texture2DDataAccessViewPtr getDataAccessViewDriver(uint32_t offsetX, uint32_t offsetY, 
		uint32_t width, uint32_t height, uint32_t mipLevel, uint32_t arrayIndex) override;

	ID3D11Texture2D* _tex2d;
};

LLGL_NAMESPACE_END2;