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
	virtual ~Context();
	virtual CapabilitiesPtr getCapabilities() = 0;
	BufferPtr createBuffer(uint32_t width, FormatPtr format, bool isStreaming = false);
	FormatPtr createFormat(FormatType type, uint32_t vectorSize = 1);
	void* mapResource(ResourcePtr resource, uint32_t mipLevel, uint32_t arrayIndex, MapType type);
	void unmapResource(ResourcePtr resource, uint32_t mipLevel, uint32_t arrayIndex);
	void copyResource(ResourcePtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ, 
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
		ResourcePtr dest, uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ, 
		uint32_t destMipLevel, uint32_t destArrayIndex);
protected:
	Context();
	void checkChild(ContextChildPtr child);
	virtual BufferPtr createBufferImpl(uint32_t width, FormatPtr format, bool isStreaming) = 0;
	virtual FormatPtr createFormatImpl(FormatType type, uint32_t vectorSize) = 0;
	virtual void* mapResourceImpl(ResourcePtr resource, uint32_t mipLevel, uint32_t arrayIndex, MapType type) = 0;
	virtual void unmapResourceImpl(ResourcePtr resource, uint32_t mipLevel, uint32_t arrayIndex) = 0;
	virtual void copyResourceImpl(ResourcePtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ, 
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
		ResourcePtr dest, uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ, 
		uint32_t destMipLevel, uint32_t destArrayIndex) = 0;
private:
	std::mutex _mutex;
};

LLGL_NAMESPACE_END;