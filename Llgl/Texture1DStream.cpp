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
	if(_width == 0) throw InvalidArgumentException("dimensions invalid");

	switch(getFormat()->getUsage())
	{
	case FormatUsage::General:
		break;
	default:
		throw InvalidArgumentException("format type unsupported by Texture1DStream");
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

void* Texture1DStream::map()
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(_isMapped) throw InvalidOperationException("texture already mapped");
	auto ret = mapImpl();
	_isMapped = 1;
	return ret; 
}

void Texture1DStream::unmap()
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(!_isMapped) throw InvalidOperationException("texture already unmapped");
	unmapImpl();
	_isMapped = 0;
}

LLGL_NAMESPACE_END;