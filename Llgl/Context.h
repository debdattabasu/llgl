#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_ENUM(MapType)
{
	Read,
	Write
};

LLGL_CLASS(Context) : public std::enable_shared_from_this<Context>
{
public:
	friend class Resource;
	friend class Buffer;
	friend class Texture1D;
	friend class Texture2D;
	virtual ~Context();
	virtual CapabilitiesPtr getCapabilities() = 0;
	BufferPtr createBuffer(uint32_t width, FormatPtr format, bool isStreaming = false);
	Texture1DPtr createTexture1D(uint32_t width, uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming = false);
	Texture2DPtr createTexture2D(uint32_t width, uint32_t height, uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming = false);
	FormatPtr createFormat(FormatType type, uint32_t vectorSize = 1);

protected:
	Context();
	virtual BufferPtr createBufferImpl(uint32_t width, FormatPtr format, bool isStreaming) = 0;
	virtual Texture1DPtr createTexture1DImpl(uint32_t width, uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming) = 0;
	virtual Texture2DPtr createTexture2DImpl(uint32_t width, uint32_t height, uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming) = 0;
	virtual FormatPtr createFormatImpl(FormatType type, uint32_t vectorSize) = 0;
private:
	void checkChild(ContextChildPtr child);
	std::mutex _mutex;
};

LLGL_NAMESPACE_END;