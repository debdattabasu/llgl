#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture2DShaderResourceView) : public Texture2DShaderResourceView
{
public:
	Direct3D11Texture2DShaderResourceView(Texture2DPtr parentTexture);
	~Direct3D11Texture2DShaderResourceView() override;
	void initializeDriver() override;

private:
	ID3D11ShaderResourceView* _srv;
};

LLGL_NAMESPACE_END2;