#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Buffer) : public ContextChild, public std::enable_shared_from_this<Buffer>
{
public:
	friend class Context;
	virtual ~Buffer() override;
	uint32_t getWidth() const;
	FormatPtr getFormat() const;
	void copyFrom(BufferPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset);
	BufferDataAccessViewPtr getDataAccessView(uint32_t offset, uint32_t width);
protected:
	Buffer(ContextPtr parentContext, uint32_t width, FormatPtr format);
	void initialize();
	virtual void initializeImpl() = 0;
	virtual void copyFromImpl(BufferPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset) = 0;
	virtual BufferDataAccessViewPtr getDataAccessViewImpl(uint32_t offset, uint32_t width) = 0;
private:
	FormatPtr _format;
	uint32_t _width;
};

LLGL_NAMESPACE_END;