#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture1D) : public ContextChild
{
public:
	friend class Context;
	virtual ~Texture1D() override;
	FormatPtr getFormat() const;
	uint32_t getWidth(uint32_t mipLevel = 0) const;
	uint32_t getNumMips()  const;
	uint32_t getArraySize() const;
	void copyFrom(Texture1DPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
		uint32_t destOffset, uint32_t destMipLevel, uint32_t destArrayIndex);
	void copyFrom(Texture1DStreamPtr src, uint32_t srcOffset, uint32_t srcWidth,
		uint32_t destOffset, uint32_t destMipLevel, uint32_t destArrayIndex);
protected:
	Texture1D(ContextPtr parentContext, uint32_t width, uint32_t numMips, uint32_t arraySize, FormatPtr format);
	void initialize();
	virtual void initializeImpl() = 0;
	virtual void copyFromImpl(Texture1DPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
		uint32_t destOffset, uint32_t destMipLevel, uint32_t destArrayIndex) =0;	
	virtual void copyFromImpl(Texture1DStreamPtr src, uint32_t srcOffset, uint32_t srcWidth,
		uint32_t destOffset, uint32_t destMipLevel, uint32_t destArrayIndex) = 0;
private:
	FormatPtr _format;
	uint32_t _width;
	uint32_t _numMips;
	uint32_t _arraySize;
};

LLGL_NAMESPACE_END;