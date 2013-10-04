#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(BufferIndexArrayView) : public BufferView
{
public:
	friend class Buffer;
	virtual ~BufferIndexArrayView() override;
protected:
	BufferIndexArrayView(BufferPtr parentBuffer);
	virtual void initializeImpl() = 0;
private:
	void initialize();
};

LLGL_NAMESPACE_END;