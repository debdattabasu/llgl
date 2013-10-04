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
	virtual void initializeDriver() = 0;
private:
	void initialize();
};

LLGL_NAMESPACE_END;