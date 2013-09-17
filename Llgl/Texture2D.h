#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture2D) : public ContextChild
{
public:
	friend class Context;
	virtual ~Texture2D() override;
	FormatPtr getFormat() const;
	uint32_t getWidth(uint32_t mipLevel = 0) const;
	uint32_t getHeight(uint32_t mipLevel = 0) const;
	uint32_t getNumMips()  const;
	uint32_t getArraySize() const;
	void copyFrom(Texture2DPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
		uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destMipLevel, uint32_t destArrayIndex);
	
	void read(Texture2DStreamPtr stream, uint32_t offsetX, uint32_t offsetY, uint32_t mipLevel, uint32_t arrayIndex);
	void write(Texture2DStreamPtr stream, uint32_t offsetX, uint32_t offsetY, uint32_t mipLevel, uint32_t arrayIndex);

protected:
	Texture2D(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t numMips, uint32_t arraySize, FormatPtr format);
	void initialize();
	virtual void initializeImpl() = 0;
	virtual void copyFromImpl(Texture2DPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
		uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destMipLevel, uint32_t destArrayIndex) = 0;

	virtual void readImpl(Texture2DStreamPtr stream, uint32_t offsetX, uint32_t offsetY, uint32_t mipLevel, uint32_t arrayIndex) = 0;
	virtual void writeImpl(Texture2DStreamPtr stream, uint32_t offsetX, uint32_t offsetY, uint32_t mipLevel, uint32_t arrayIndex) = 0;

private:
	uint32_t _width;
	uint32_t _height;
	uint32_t _numMips;
	uint32_t _arraySize;
	FormatPtr _format;
};

LLGL_NAMESPACE_END;