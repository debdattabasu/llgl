#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(BufferUnorderedAccessView) : public BufferView
{
public:
	friend class Buffer;
	virtual ~BufferUnorderedAccessView() override;
protected:
	BufferUnorderedAccessView(BufferPtr parentBuffer);
	void initialize();
	virtual void initializeImpl() = 0;
};

LLGL_NAMESPACE_END;