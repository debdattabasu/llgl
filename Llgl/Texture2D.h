#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture2D) : public ContextChild
{
public:
	virtual ~Texture2D() override;
	FormatPtr getFormat() const;
	bool isStreaming() const;
	bool isMapped(uint32_t mipLevel, uint32_t arrayIndex) const;
	uint32_t getWidth() const;
	uint32_t getHeight() const;
	uint32_t getNumMips()  const;
	uint32_t getArraySize() const;

	void* map(uint32_t mipLevel, uint32_t arrayIndex, MapType type);
	void unmap(uint32_t mipLevel, uint32_t arrayIndex);
	void copyFrom(Texture2DPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
		uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destMipLevel, uint32_t destArrayIndex);

protected:
	Texture2D(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming);
	virtual void initialize();

	virtual void* mapImpl(uint32_t mipLevel, uint32_t arrayIndex, MapType type) = 0;
	virtual void unmapImpl(uint32_t mipLevel, uint32_t arrayIndex) = 0;
	virtual void copyFromImpl(Texture2DPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
		uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destMipLevel, uint32_t destArrayIndex) = 0;

private:
	FormatPtr _format;
	bool _isStreaming;
	void setMapped(uint32_t mipLevel, uint32_t arrayIndex, bool value);
	std::vector<bool> _isMapped;
	uint32_t _width;
	uint32_t _height;
	uint32_t _numMips;
	uint32_t _arraySize;
};

LLGL_NAMESPACE_END;