#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Buffer) : public Buffer
{
public:
	~Direct3D11Buffer() override;

	void initialize() override;
	void initializeStreaming();
	void initializeRaw();
	void initializeVertexIndex();
	Direct3D11Buffer(ContextPtr parentContext, uint32_t width, FormatPtr format, bool isStreaming);

	ID3D11Buffer* _buf;
	ID3D11ShaderResourceView* _srv;
	ID3D11UnorderedAccessView* _uav;
};

LLGL_NAMESPACE_END2;