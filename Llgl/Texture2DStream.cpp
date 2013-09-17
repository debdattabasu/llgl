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
	if(_width == 0 || _height == 0) throw InvalidArgumentException("dimensions invalid");
	switch(getFormat()->getUsage())
	{
	case FormatUsage::General:
		break;
	case FormatUsage::DepthTexture:
		break;
	default:
		throw InvalidArgumentException("format type unsupported by Texture2DStream");
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

void* Texture2DStream::map()
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(_isMapped) throw InvalidOperationException("Texture2DStream already mapped");
	auto ret = mapImpl();
	_isMapped = 1;
	return ret;
}

void Texture2DStream::unmap()
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(!_isMapped) throw InvalidOperationException("Texture2DStream already unmapped");
	unmapImpl();
	_isMapped= 0;
}

LLGL_NAMESPACE_END;