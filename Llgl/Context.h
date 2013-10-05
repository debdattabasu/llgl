#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Context) : public std::enable_shared_from_this<Context>, public NonCopyable
{
public:
	LLGL_CLASS(LockGuard)
	{
	public:
		LockGuard(ContextPtr ctx);
		~LockGuard();
	private:
		ContextPtr _ctx;
	};
	virtual ~Context() override;
	virtual CapabilitiesPtr getCapabilities() = 0;

	BufferPtr createBuffer(uint32_t width, FormatPtr format);
	Texture1DPtr createTexture1D(uint32_t width, uint32_t numMips, uint32_t arraySize, FormatPtr format);
	Texture2DPtr createTexture2D(uint32_t width, uint32_t height, uint32_t numMips, uint32_t arraySize, FormatPtr format);
	Texture3DPtr createTexture3D(uint32_t width, uint32_t height, uint32_t depth, uint32_t numMips, FormatPtr format);
	FormatPtr createFormat(FormatType type, uint32_t vectorSize = 1);

protected:
	Context();
	virtual BufferPtr createBufferDriver(uint32_t width, FormatPtr format) = 0;
	virtual Texture1DPtr createTexture1DDriver(uint32_t width, uint32_t numMips, uint32_t arraySize, FormatPtr format) = 0;
	virtual Texture2DPtr createTexture2DDriver(uint32_t width, uint32_t height, uint32_t numMips, uint32_t arraySize, FormatPtr format) = 0;
	virtual Texture3DPtr createTexture3DDriver(uint32_t width, uint32_t height, uint32_t depth, uint32_t numMips, FormatPtr format) = 0;
	virtual FormatPtr createFormatDriver(FormatType type, uint32_t vectorSize) = 0;
private:
	std::mutex _mutex;
};

LLGL_NAMESPACE_END;