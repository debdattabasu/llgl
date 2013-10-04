#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture) : public Resource
{
public:
	virtual ~Texture() override;
	uint32_t getNumMips()  const;
	uint32_t getArraySize() const;
protected:
	Texture(ContextPtr parentContext, uint32_t numDimensions, uint32_t numMips, uint32_t arraySize, FormatPtr format);
	virtual void initialize() override;

private:
	uint32_t _numMips;
	uint32_t _arraySize;
};

LLGL_NAMESPACE_END;