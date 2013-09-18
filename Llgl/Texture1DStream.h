#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture1DStream) : public ContextChild
{
public:
	friend class Context;
	LLGL_CLASS(MapDesc)
	{
	public:
		char* data;
	};
	virtual ~Texture1DStream() override;
	FormatPtr getFormat() const;
	bool isMapped() const;
	uint32_t getWidth() const;
	MapDesc map();
	void unmap();
	void copyFrom(Texture1DPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
		uint32_t destOffset);
	void copyFrom(Texture1DStreamPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset);
protected:
	Texture1DStream(ContextPtr parentContext, uint32_t width, FormatPtr format);
	void initialize();
	virtual void initializeImpl() = 0;
	virtual MapDesc mapImpl() =0;
	virtual void unmapImpl() =0;
	virtual void copyFromImpl(Texture1DPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
		uint32_t destOffset) = 0;
	virtual void copyFromImpl(Texture1DStreamPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset) = 0;
private:
	FormatPtr _format;
	bool _isMapped;
	uint32_t _width;
	uint32_t _numMips;
	uint32_t _arraySize;
};

LLGL_NAMESPACE_END;