#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture1DStream::Texture1DStream(ContextPtr parentContext, uint32_t width, FormatPtr format): 
	ContextChild(parentContext), _width(width), _format(format), _isMapped(0)
{

}

Texture1DStream::~Texture1DStream()
{

}
	
void Texture1DStream::initialize() 
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(_width == 0) throw InvalidArgumentException("invalid dimensions");
	switch(getFormat()->getUsage())
	{
	case FormatUsage::General:
		break;
	default:
		throw InvalidArgumentException("format type unsupported by texture1d stream");
	}
	initializeImpl();
}

FormatPtr Texture1DStream::getFormat() const
{
	return _format;
}

bool Texture1DStream::isMapped() const
{
	return _isMapped;
}

uint32_t Texture1DStream::getWidth() const
{
	return _width;
}

Texture1DStream::MapDesc Texture1DStream::map()
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(_isMapped) throw InvalidOperationException("already mapped");
	auto ret = mapImpl();
	_isMapped = 1;
	return ret; 
}

void Texture1DStream::unmap()
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(!_isMapped) throw InvalidOperationException("already unmapped");
	unmapImpl();
	_isMapped = 0;
}

void Texture1DStream::copyFrom(Texture1DPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
		uint32_t destOffset)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("format mismatch");
	if(srcWidth == 0) throw InvalidArgumentException("invalid dimensions");
	if((srcMipLevel + 1) > src->getNumMips() || (srcArrayIndex + 1) > src->getArraySize())
			throw InvalidArgumentException("out of bounds");
	if((srcOffset + srcWidth) > src->getWidth(srcMipLevel) || (destOffset + srcWidth) > getWidth())
		throw InvalidArgumentException("out of bounds");	   	
	copyFromImpl(src, srcOffset, srcWidth, srcMipLevel, srcArrayIndex, 
		destOffset);
}

void Texture1DStream::copyFrom(Texture1DStreamPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("format mismatch");
	if(srcWidth == 0) throw InvalidArgumentException("invalid dimensions");
	if((srcOffset + srcWidth) > src->getWidth() || (destOffset + srcWidth) > getWidth())
		throw InvalidArgumentException("out of bounds");	   	
	copyFromImpl(src, srcOffset, srcWidth, destOffset);
}

LLGL_NAMESPACE_END;