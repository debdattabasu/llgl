#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11BufferVertexArrayView) : public BufferVertexArrayView
{
public:
	Direct3D11BufferVertexArrayView(BufferPtr parentBuffer);
	~Direct3D11BufferVertexArrayView() override;
	void initializeDriver() override;

};

LLGL_NAMESPACE_END2;