#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11BufferIndexArrayView) : public BufferIndexArrayView
{
public:
	Direct3D11BufferIndexArrayView(BufferPtr parentBuffer);
	~Direct3D11BufferIndexArrayView() override;
	void initializeImpl() override;

};

LLGL_NAMESPACE_END2;