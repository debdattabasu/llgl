#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(BufferView) : public ContextChild
{
public:
	virtual ~BufferView() override;
	BufferPtr getParentBuffer() const;
	FormatPtr getFormat() const;
protected:
	BufferView(BufferPtr parentBuffer);
private:
	BufferPtr _parentBuffer;
};

LLGL_NAMESPACE_END;