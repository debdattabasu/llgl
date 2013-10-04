#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture1DShaderResourceView) : public Texture1DShaderResourceView
{
public:
	Direct3D11Texture1DShaderResourceView(Texture1DPtr parentTexture);
	~Direct3D11Texture1DShaderResourceView() override;
	void initializeDriver() override;

private:
	ID3D11ShaderResourceView* _srv;
};

LLGL_NAMESPACE_END2;