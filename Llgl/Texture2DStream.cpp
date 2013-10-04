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
	Context::LockGuard lock(getParentContext()); 
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
	initializeDriver();
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
	Context::LockGuard lock(getParentContext()); 
	if(_isMapped) throw InvalidOperationException("already mapped");
	auto ret = mapDriver();
	_isMapped = 1;
	return ret;
}

void Texture2DStream::unmap()
{
	Context::LockGuard lock(getParentContext()); 
	if(!_isMapped) throw InvalidOperationException("already unmapped");
	unmapDriver();
	_isMapped= 0;
}

void Texture2DStream::readFrom(Texture2DSlicePtr src, uint32_t offsetX, uint32_t offsetY)
{
	Context::LockGuard lock(getParentContext()); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("format mismatch");
	if((offsetX + getWidth()) > src->getWidth() || (offsetY + getHeight()) > src->getHeight())
			throw InvalidArgumentException("out of bounds");
	readFromDriver(src, offsetX, offsetY);

}

void Texture2DStream::writeTo(Texture2DSlicePtr dest, uint32_t offsetX, uint32_t offsetY)
{
	Context::LockGuard lock(getParentContext()); 
	if (!dest->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("format mismatch");
	if((offsetX + getWidth()) > dest->getWidth() || (offsetY + getHeight()) > dest->getHeight())
			throw InvalidArgumentException("out of bounds");
	writeToDriver(dest, offsetX, offsetY);
}

LLGL_NAMESPACE_END;