#include "Library.h"

LLGL_NAMESPACE(Llgl);

BufferShaderResourceView::BufferShaderResourceView(BufferPtr parentBuffer) :
	BufferView(parentBuffer)
{

}

BufferShaderResourceView::~BufferShaderResourceView()
{

}

void BufferShaderResourceView::initialize()
{
	if(!getParentContext()->getCapabilities()->supportsShaderResourceBuffer()) 
		throw UnsupportedFeatureException("shader resource views for buffers unsupported");

	Context::LockGuard lock(getParentContext()); 
	initializeDriver();
}

LLGL_NAMESPACE_END;