#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11BufferShaderResourceView) : public BufferShaderResourceView
{
public:
	Direct3D11BufferShaderResourceView(BufferPtr parentBuffer);
	~Direct3D11BufferShaderResourceView() override;
	void initializeImpl() override;

	void initializeRaw();
	void initializeFormatted();

private:
	ID3D11ShaderResourceView* _srv;
};

LLGL_NAMESPACE_END2;