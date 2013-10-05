#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture3DShaderResourceView) : public Texture3DShaderResourceView
{
public:
	Direct3D11Texture3DShaderResourceView(Texture3DPtr parentTexture);
	~Direct3D11Texture3DShaderResourceView() override;
	void initializeDriver() override;

private:
	ID3D11ShaderResourceView* _srv;
};

LLGL_NAMESPACE_END2;