#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture2DRenderTargetView) : public Texture2DRenderTargetView
{
public:
	Direct3D11Texture2DRenderTargetView(Texture2DPtr parentTexture, uint32_t mipLevel, uint32_t arrayIndex);
	~Direct3D11Texture2DRenderTargetView() override;
	void initializeDriver() override;

private:
	ID3D11RenderTargetView* _rtv;
};

LLGL_NAMESPACE_END2;