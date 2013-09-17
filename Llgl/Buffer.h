#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Buffer) : public ContextChild
{
public:
	friend class Context;
	virtual ~Buffer() override;
	uint32_t getWidth() const;
	FormatPtr getFormat() const;
	bool isMapped() const;
	void copyFrom(BufferPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset);
	void write(BufferStreamPtr stream, uint32_t offset);
	void read(BufferStreamPtr stream, uint32_t offset);
protected:
	Buffer(ContextPtr parentContext, uint32_t width, FormatPtr format);
	void initialize();
	virtual void initializeImpl() = 0;
	virtual void copyFromImpl(BufferPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset) = 0;
	virtual void writeImpl(BufferStreamPtr stream, uint32_t offset) = 0;
	virtual void readImpl(BufferStreamPtr stream, uint32_t offset) = 0;
private:
	FormatPtr _format;
	bool _isMapped;
	uint32_t _width;
};

LLGL_NAMESPACE_END;