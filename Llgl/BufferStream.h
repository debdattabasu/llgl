#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(BufferStream) : public ContextChild
{
public:
	LLGL_CLASS(MapDesc)
	{
	public:
		char* data;
	};
	friend class Context;
	virtual ~BufferStream() override;
	uint32_t getWidth() const;
	FormatPtr getFormat() const;
	bool isMapped() const;
	MapDesc map();
	void unmap();
	void copyFrom(BufferPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset);
	void copyFrom(BufferStreamPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset);
protected:
	BufferStream(ContextPtr parentContext, uint32_t width, FormatPtr format);
	void initialize();
	virtual void initializeImpl() = 0;
	virtual MapDesc mapImpl() = 0;
	virtual void unmapImpl() = 0;
	virtual void copyFromImpl(BufferPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset) = 0;
	virtual void copyFromImpl(BufferStreamPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset) = 0;
private:
	FormatPtr _format;
	bool _isMapped;
	uint32_t _width;
};

LLGL_NAMESPACE_END;