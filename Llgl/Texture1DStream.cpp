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

void Texture1DStream::readFrom(Texture1DSlicePtr src, uint32_t offset)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("format mismatch");
	if((offset + getWidth()) > src->getWidth())
		throw InvalidArgumentException("out of bounds");	   	
	readFromImpl(src, offset);
}

void Texture1DStream::writeTo(Texture1DSlicePtr dest, uint32_t offset)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if (!dest->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("format mismatch");
	if((offset + getWidth()) > dest->getWidth())
		throw InvalidArgumentException("out of bounds");	   	
	writeToImpl(dest, offset);
}

LLGL_NAMESPACE_END;