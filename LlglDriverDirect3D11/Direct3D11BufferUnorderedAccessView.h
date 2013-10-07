#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11BufferUnorderedAccessView) : public BufferUnorderedAccessView
{
public:
	Direct3D11BufferUnorderedAccessView(BufferPtr parentBuffer);
	~Direct3D11BufferUnorderedAccessView() override;
	void initializeDriver() override;

	void initializeStructured();
	void initializeFormatted();

	ID3D11UnorderedAccessView* getDirect3D11UnorderedAccessView() const;
private:
	ID3D11UnorderedAccessView* _uav;
};

LLGL_NAMESPACE_END2;