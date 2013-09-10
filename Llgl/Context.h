#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Context) : public std::enable_shared_from_this<Context>
{
public:
	virtual ~Context();
	virtual CapabilitiesPtr getCapabilities() = 0;
	BufferPtr createBuffer(uint32_t width, FormatPtr format, bool isStreaming = false);
	FormatPtr createFormat(FormatType type, uint32_t vectorSize = 1);
protected:
	Context();
	virtual BufferPtr createBufferImpl(uint32_t width, FormatPtr format, bool isStreaming) = 0;
	virtual FormatPtr createFormatImpl(FormatType type, uint32_t vectorSize) = 0;
private:
	std::mutex _mutex;
};

LLGL_NAMESPACE_END;