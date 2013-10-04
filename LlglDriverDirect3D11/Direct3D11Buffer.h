#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Buffer) : public Buffer
{
public:
	Direct3D11Buffer(ContextPtr parentContext, uint32_t width, FormatPtr format);
	~Direct3D11Buffer() override;
	void initializeDriver() override;
	void initializeRaw();
	void initializeVertexIndex();
	
	BufferDataAccessViewPtr getDataAccessViewDriver(uint32_t offset, uint32_t width) override;
	BufferShaderResourceViewPtr getShaderResourceViewDriver() override;
	BufferUnorderedAccessViewPtr getUnorderedAccessViewDriver() override;
	BufferVertexArrayViewPtr getVertexArrayViewDriver() override;
	BufferIndexArrayViewPtr getIndexArrayViewDriver() override;

	ID3D11Buffer* _buf;
};

LLGL_NAMESPACE_END2;