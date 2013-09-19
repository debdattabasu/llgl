#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture2DStream::Texture2DStream(ContextPtr parentContext, uint32_t width, uint32_t height, FormatPtr format):
	ContextChild(parentContext), _width(width), _height(height), _format(format), _isMapped(0)
{

}

Texture2DStream::~Texture2DStream()
{

}
	
void Texture2DStream::initialize() 
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(_width == 0 || _height == 0) throw InvalidArgumentException("invalid dimensions");
	switch(getFormat()->getUsage())
	{
	case FormatUsage::General:
		break;
	case FormatUsage::DepthTexture:
		break;
	default:
		throw InvalidArgumentException("format type unsupported by texture2d stream");
	}
	initializeImpl();
}

FormatPtr Texture2DStream::getFormat() const
{
	return _format;
}

bool Texture2DStream::isMapped() const
{
	return _isMapped;
}

uint32_t Texture2DStream::getWidth() const
{
	return _width;
}

uint32_t Texture2DStream::getHeight() const
{
	return _height;
}

Texture2DStream::MapDesc Texture2DStream::map()
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(_isMapped) throw InvalidOperationException("already mapped");
	auto ret = mapImpl();
	_isMapped = 1;
	return ret;
}

void Texture2DStream::unmap()
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(!_isMapped) throw InvalidOperationException("already unmapped");
	unmapImpl();
	_isMapped= 0;
}

void Texture2DStream::readFrom(Texture2DSlicePtr src, uint32_t offsetX, uint32_t offsetY)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("format mismatch");
	if((offsetX + getWidth()) > src->getWidth() || (offsetY + getHeight()) > src->getHeight())
			throw InvalidArgumentException("out of bounds");
	readFromImpl(src, offsetX, offsetY);

}

void Texture2DStream::writeTo(Texture2DSlicePtr dest, uint32_t offsetX, uint32_t offsetY)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if (!dest->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("format mismatch");
	if((offsetX + getWidth()) > dest->getWidth() || (offsetY + getHeight()) > dest->getHeight())
			throw InvalidArgumentException("out of bounds");
	writeToImpl(dest, offsetX, offsetY);
}

LLGL_NAMESPACE_END;