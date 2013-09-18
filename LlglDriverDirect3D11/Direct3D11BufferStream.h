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
	void copyFromImpl(BufferPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset) override;
	void copyFromImpl(BufferStreamPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset) override;
	
	ID3D11Buffer* _buf;
};

LLGL_NAMESPACE_END2;