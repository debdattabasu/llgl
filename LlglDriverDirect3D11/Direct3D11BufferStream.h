#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11BufferStream) : public BufferStream
{
public:
	Direct3D11BufferStream(ContextPtr parentContext, uint32_t width, FormatPtr format);
	~Direct3D11BufferStream() override;
	MapDesc mapImpl() override;
	void unmapImpl() override;
	void initializeImpl() override;
	void readDataImpl(BufferPtr src, uint32_t offset) override;
	void writeDataImpl(BufferPtr dest, uint32_t offset) override;
	
	ID3D11Buffer* _buf;
};

LLGL_NAMESPACE_END2;