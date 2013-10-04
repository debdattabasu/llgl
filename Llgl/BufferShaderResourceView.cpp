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
	Context::LockGuard lock(getParentContext()); 
	if(!getParentContext()->getCapabilities()->supportsShaderResourceBuffer()) 
		throw UnsupportedFeatureException("shader resource views for buffers unsupported");
	initializeImpl();
}

LLGL_NAMESPACE_END;