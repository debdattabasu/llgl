#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11BufferDataAccessView) : public BufferDataAccessView
{
public:
	Direct3D11BufferDataAccessView(BufferPtr parentBuffer, uint32_t offset, uint32_t width);
	~Direct3D11BufferDataAccessView() override;
	void initializeImpl() override;
	void copyFromImpl(BufferDataAccessViewPtr src) override;
	void getDataImpl(void* data) override;
	void setDataImpl(void* data) override;

private:
	ID3D11Buffer* getDirect3D11StagingBuffer();
	ID3D11Buffer* _buf;
};

LLGL_NAMESPACE_END2;