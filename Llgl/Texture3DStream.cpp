#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture3DStream::Texture3DStream(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t depth, FormatPtr format):
	ContextChild(parentContext), _width(width), _height(height), _depth(depth), _format(format), _isMapped(0)
{

}

Texture3DStream::~Texture3DStream()
{

}
	
void Texture3DStream::initialize() 
{
	Context::LockGuard lock(getParentContext()); 
	if(_width == 0 || _height == 0 || _depth == 0) throw InvalidArgumentException("invalid dimensions");
	switch(getFormat()->getUsage())
	{
	case FormatUsage::General:
		break;
	default:
		throw InvalidArgumentException("format type unsupported by texture3d stream");
	}
	initializeDriver();
}

FormatPtr Texture3DStream::getFormat() const
{
	return _format;
}

bool Texture3DStream::isMapped() const
{
	return _isMapped;
}

uint32_t Texture3DStream::getWidth() const
{
	return _width;
}

uint32_t Texture3DStream::getHeight() const
{
	return _height;
}

uint32_t Texture3DStream::getDepth() const
{
	return _depth;
}

Texture3DStream::MapDesc Texture3DStream::map()
{
	Context::LockGuard lock(getParentContext()); 
	if(_isMapped) throw InvalidOperationException("already mapped");
	auto ret = mapDriver();
	_isMapped = 1;
	return ret;
}

void Texture3DStream::unmap()
{
	Context::LockGuard lock(getParentContext()); 
	if(!_isMapped) throw InvalidOperationException("already unmapped");
	unmapDriver();
	_isMapped = 0;
}

void Texture3DStream::readFrom(Texture3DSlicePtr src, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ)
{
	Context::LockGuard lock(getParentContext()); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("format mismatch");
	if((offsetX + getWidth()) > src->getWidth() || (offsetY + getHeight()) > src->getHeight()
		|| (offsetZ + getDepth()) > src->getDepth())
			throw InvalidArgumentException("out of bounds");
	readFromDriver(src, offsetX, offsetY, offsetZ);
}

void Texture3DStream::writeTo(Texture3DSlicePtr dest, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ)
{
	Context::LockGuard lock(getParentContext()); 
	if (!dest->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("format mismatch");
	if((offsetX + getWidth()) > dest->getWidth() || (offsetY + getHeight()) > dest->getHeight()
		|| (offsetZ + getDepth()) > dest->getDepth())
			throw InvalidArgumentException("out of bounds");
	writeToDriver(dest, offsetX, offsetY, offsetZ);
}

LLGL_NAMESPACE_END;