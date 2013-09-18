#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture3D) : public ContextChild
{
public:
	friend class Context;
	virtual ~Texture3D() override;
	FormatPtr getFormat() const;
	uint32_t getWidth(uint32_t mipLevel = 0) const;
	uint32_t getHeight(uint32_t mipLevel = 0) const;
	uint32_t getDepth(uint32_t mipLevel = 0) const;
	uint32_t getNumMips()  const;
	void copyFrom(Texture3DPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t srcMipLevel, 
		uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ, uint32_t destMipLevel);
	void copyFrom(Texture3DStreamPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ, 
		uint32_t destMipLevel);
protected:
	Texture3D(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t depth, uint32_t numMips, FormatPtr format);
	void initialize();
	virtual void initializeImpl() = 0;
	virtual void copyFromImpl(Texture3DPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t srcMipLevel, 
		uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ, uint32_t destMipLevel) = 0;
	virtual void copyFromImpl(Texture3DStreamPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ, 
		uint32_t destMipLevel) = 0;
private:
	FormatPtr _format;
	uint32_t _width;
	uint32_t _height;
	uint32_t _depth;
	uint32_t _numMips;
};

LLGL_NAMESPACE_END;