#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(BufferView) : public ResourceView
{
public:
	virtual ~BufferView() override;
	BufferPtr getParentResource() const;
protected:
	BufferView(BufferPtr parentBuffer);
};

LLGL_NAMESPACE_END;