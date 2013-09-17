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
	bool isStreaming() const;
	bool isMapped() const;

	
	void* map(MapType type);
	void unmap();
	void copyFrom(BufferPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset);

protected:
	Buffer(ContextPtr parentContext, uint32_t width, FormatPtr format, bool isStreaming);
	virtual void initializeImpl() = 0;
	void initialize();
	virtual void* mapImpl(MapType type) = 0;
	virtual void unmapImpl() = 0;
	virtual void copyFromImpl(BufferPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset) = 0;
private:
	FormatPtr _format;
	bool _isStreaming;
	bool _isMapped;
	uint32_t _width;
};

LLGL_NAMESPACE_END;