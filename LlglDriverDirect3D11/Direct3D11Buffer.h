#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Buffer) : public Buffer
{
public:
	Direct3D11Buffer(ContextPtr parentContext, uint32_t width, FormatPtr format, bool isStreaming);
	~Direct3D11Buffer() override;

	void* mapImpl(MapType type) override;
	void unmapImpl() override;
	void copyFromImpl(BufferPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset) override;


	void initializeImpl() override;
	void initializeStreaming();
	void initializeRaw();
	void initializeVertexIndex();

	ID3D11Buffer* _buf;
	ID3D11ShaderResourceView* _srv;
	ID3D11UnorderedAccessView* _uav;
};

LLGL_NAMESPACE_END2;