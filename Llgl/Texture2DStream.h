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
	void readFrom(Texture2DSlicePtr src, uint32_t offsetX, uint32_t offsetY);
	void writeTo(Texture2DSlicePtr dest, uint32_t offsetX, uint32_t offsetY);

protected:
	Texture2DStream(ContextPtr parentContext, uint32_t width, uint32_t height, FormatPtr format);
	void initialize();
	virtual void initializeImpl() = 0;
	virtual MapDesc mapImpl() = 0;
	virtual void unmapImpl() = 0;
	virtual void readFromImpl(Texture2DSlicePtr src, uint32_t offsetX, uint32_t offsetY) = 0;
	virtual void writeToImpl(Texture2DSlicePtr dest, uint32_t offsetX, uint32_t offsetY) = 0;

private:
	FormatPtr _format;
	bool _isMapped;
	uint32_t _width;
	uint32_t _height;
};

LLGL_NAMESPACE_END;