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
	void readFrom(Texture3DSlicePtr src, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ);
	void writeTo(Texture3DSlicePtr dest, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ);
protected:
	Texture3DStream(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t depth, FormatPtr format);
	void initialize();
	virtual void initializeImpl() = 0;
	virtual MapDesc mapImpl() = 0;
	virtual void unmapImpl() = 0;
	virtual void readFromImpl(Texture3DSlicePtr src, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ) = 0;
	virtual void writeToImpl(Texture3DSlicePtr dest, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ) = 0;
private:
	bool _isMapped;
	uint32_t _width;
	uint32_t _height;
	uint32_t _depth;
	FormatPtr _format;
};

LLGL_NAMESPACE_END;