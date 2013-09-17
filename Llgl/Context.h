#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Context) : public std::enable_shared_from_this<Context>
{
public:
	friend class Buffer;
	friend class BufferStream;
	friend class Texture1D;
	friend class Texture1DStream;
	friend class Texture2D;
	friend class Texture2DStream;
	friend class Texture3D;
	friend class Texture3DStream;
	friend class Format;
	virtual ~Context();
	virtual CapabilitiesPtr getCapabilities() = 0;
	BufferPtr createBuffer(uint32_t width, FormatPtr format);
	BufferStreamPtr createBufferStream(uint32_t width, FormatPtr format);
	Texture1DPtr createTexture1D(uint32_t width, uint32_t numMips, uint32_t arraySize, FormatPtr format);
	Texture1DStreamPtr createTexture1DStream(uint32_t width, FormatPtr format);
	Texture2DPtr createTexture2D(uint32_t width, uint32_t height, uint32_t numMips, uint32_t arraySize, FormatPtr format);
	Texture2DStreamPtr createTexture2DStream(uint32_t width, uint32_t height, FormatPtr format);
	Texture3DPtr createTexture3D(uint32_t width, uint32_t height, uint32_t depth, uint32_t numMips, FormatPtr format);
	Texture3DStreamPtr createTexture3DStream(uint32_t width, uint32_t height, uint32_t depth, FormatPtr format);
	FormatPtr createFormat(FormatType type, uint32_t vectorSize = 1);
protected:
	Context();
	virtual BufferPtr createBufferImpl(uint32_t width, FormatPtr format) = 0;
	virtual BufferStreamPtr createBufferStreamImpl(uint32_t width, FormatPtr format) = 0;
	virtual Texture1DPtr createTexture1DImpl(uint32_t width, uint32_t numMips, uint32_t arraySize, FormatPtr format) = 0;
	virtual Texture1DStreamPtr createTexture1DStreamImpl(uint32_t width, FormatPtr format) = 0;
	virtual Texture2DPtr createTexture2DImpl(uint32_t width, uint32_t height, uint32_t numMips, uint32_t arraySize, FormatPtr format) = 0;
	virtual Texture2DStreamPtr createTexture2DStreamImpl(uint32_t width, uint32_t height, FormatPtr format) = 0;
	virtual Texture3DPtr createTexture3DImpl(uint32_t width, uint32_t height, uint32_t depth, uint32_t numMips, FormatPtr format) = 0;
	virtual Texture3DStreamPtr createTexture3DStreamImpl(uint32_t width, uint32_t height, uint32_t depth, FormatPtr format) = 0;
	virtual FormatPtr createFormatImpl(FormatType type, uint32_t vectorSize) = 0;
private:
	std::mutex _mutex;
};

LLGL_NAMESPACE_END;