#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(BufferShaderResourceView) : public BufferView
{
public:
	friend class Buffer;
	virtual ~BufferShaderResourceView() override;
protected:
	BufferShaderResourceView(BufferPtr parentBuffer);
	virtual void initializeImpl() = 0;
private:
	void initialize();
};

LLGL_NAMESPACE_END;