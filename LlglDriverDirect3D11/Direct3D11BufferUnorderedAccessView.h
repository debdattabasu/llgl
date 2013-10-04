#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11BufferUnorderedAccessView) : public BufferUnorderedAccessView
{
public:
	Direct3D11BufferUnorderedAccessView(BufferPtr parentBuffer);
	~Direct3D11BufferUnorderedAccessView() override;
	void initializeImpl() override;

	void initializeRaw();
	void initializeFormatted();
private:
	ID3D11UnorderedAccessView* _uav;
};

LLGL_NAMESPACE_END2;