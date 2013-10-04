#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(BufferVertexArrayView) : public BufferView
{
public:
	friend class Buffer;
	virtual ~BufferVertexArrayView() override;
protected:
	BufferVertexArrayView(BufferPtr parentBuffer);
	virtual void initializeImpl() = 0;
private:
	void initialize();
};

LLGL_NAMESPACE_END;