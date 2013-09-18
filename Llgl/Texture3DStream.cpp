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
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(_width == 0 || _height == 0 || _depth == 0) throw InvalidArgumentException("dimensions invalid");
	switch(getFormat()->getUsage())
	{
	case FormatUsage::General:
		break;
	default:
		throw InvalidArgumentException("format type unsupported by Texture3DStream");
	}
	initializeImpl();
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
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(_isMapped) throw InvalidOperationException("Texture3DStream already mapped");
	auto ret = mapImpl();
	_isMapped = 1;
	return ret;
}

void Texture3DStream::unmap()
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(!_isMapped) throw InvalidOperationException("Texture3DStream already unmapped");
	unmapImpl();
	_isMapped = 0;
}

LLGL_NAMESPACE_END;