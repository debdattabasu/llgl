#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Buffer) : public Resource
{
public:
	virtual ~Buffer() override;
protected:
	Buffer(ContextPtr parentContext, uint32_t width, FormatPtr format, bool isStreaming = false);
	virtual void initialize() override;
};


LLGL_NAMESPACE_END;