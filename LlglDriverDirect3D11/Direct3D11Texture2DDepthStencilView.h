#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture2DDepthStencilView) : public Texture2DDepthStencilView
{
public:
	Direct3D11Texture2DDepthStencilView(Texture2DPtr parentTexture, uint32_t mipLevel, uint32_t arrayIndex);
	~Direct3D11Texture2DDepthStencilView() override;
	void initializeDriver() override;

	ID3D11DepthStencilView* getDirect3D11DepthStencilView() const;

private:
	ID3D11DepthStencilView* _dsv;
};

LLGL_NAMESPACE_END2;