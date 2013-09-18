#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture3DStream) : public ContextChild
{
public:
	friend class Context;
	LLGL_CLASS(MapDesc)
	{
	public:
		char* data;
		uint32_t rowPitch;
		uint32_t depthPitch;
	};
	virtual ~Texture3DStream() override;
	FormatPtr getFormat() const;
	uint32_t getWidth() const;
	uint32_t getHeight() const;
	uint32_t getDepth() const;
	bool isMapped() const;
	MapDesc map();
	void unmap();
	void copyFrom(Texture3DPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t srcMipLevel, 
		uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ);
	void copyFrom(Texture3DStreamPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ);
protected:
	Texture3DStream(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t depth, FormatPtr format);
	void initialize();
	virtual void initializeImpl() = 0;
	virtual MapDesc mapImpl() = 0;
	virtual void unmapImpl() = 0;
	virtual void copyFromImpl(Texture3DPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t srcMipLevel, 
		uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ) = 0;
	virtual void copyFromImpl(Texture3DStreamPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ) = 0;
private:
	bool _isMapped;
	uint32_t _width;
	uint32_t _height;
	uint32_t _depth;
	FormatPtr _format;
};

LLGL_NAMESPACE_END;