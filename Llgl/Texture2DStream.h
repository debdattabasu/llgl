#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture2DStream) : public ContextChild
{
public:
	friend class Context;
	LLGL_CLASS(MapDesc)
	{
	public:
		char* data;
		uint32_t rowPitch;
	};
	virtual ~Texture2DStream() override;
	FormatPtr getFormat() const;
	bool isMapped() const;
	uint32_t getWidth() const;
	uint32_t getHeight() const;
	MapDesc map();
	void unmap();
	void copyFrom(Texture2DPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
		uint32_t destOffsetX, uint32_t destOffsetY);
	void copyFrom(Texture2DStreamPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcWidth, uint32_t srcHeight, 
		uint32_t destOffsetX, uint32_t destOffsetY);
protected:
	Texture2DStream(ContextPtr parentContext, uint32_t width, uint32_t height, FormatPtr format);
	void initialize();
	virtual void initializeImpl() = 0;
	virtual MapDesc mapImpl() = 0;
	virtual void unmapImpl() = 0;
	virtual void copyFromImpl(Texture2DPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
		uint32_t destOffsetX, uint32_t destOffsetY) = 0;
	virtual void copyFromImpl(Texture2DStreamPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcWidth, uint32_t srcHeight, 
		uint32_t destOffsetX, uint32_t destOffsetY) = 0;
private:
	FormatPtr _format;
	bool _isMapped;
	uint32_t _width;
	uint32_t _height;
};

LLGL_NAMESPACE_END;