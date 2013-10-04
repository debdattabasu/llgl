#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Resource) : public ContextChild
{
public:
	virtual ~Resource() override;
	FormatPtr getFormat() const;
	uint32_t getNumDimensions() const;
protected:
	Resource(ContextPtr parentContext, uint32_t numDimensions, FormatPtr format);
	virtual void initialize();
private:
	FormatPtr _format;
	uint32_t _numDimensions;
};

LLGL_NAMESPACE_END;