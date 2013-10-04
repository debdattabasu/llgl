#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Buffer) : public Buffer
{
public:
	Direct3D11Buffer(ContextPtr parentContext, uint32_t width, FormatPtr format);
	~Direct3D11Buffer() override;
	void copyFromImpl(BufferPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset) override;
	void initializeImpl() override;
	void initializeRaw();
	void initializeVertexIndex();
	BufferDataAccessViewPtr getDataAccessViewImpl(uint32_t offset, uint32_t width) override;
	BufferShaderResourceViewPtr getShaderResourceViewImpl() override;
	BufferUnorderedAccessViewPtr getUnorderedAccessViewImpl() override;
	BufferVertexArrayViewPtr getVertexArrayViewImpl() override;
	BufferIndexArrayViewPtr getIndexArrayViewImpl() override;

	ID3D11Buffer* _buf;
};

LLGL_NAMESPACE_END2;