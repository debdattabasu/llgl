#include "Library.h"

LLGL_NAMESPACE(Llgl);

BufferUnorderedAccessView::BufferUnorderedAccessView(BufferPtr parentBuffer) :
	BufferView(parentBuffer)
{

}

BufferUnorderedAccessView::~BufferUnorderedAccessView()
{

}

void BufferUnorderedAccessView::initialize()
{
	if(!getParentContext()->getCapabilities()->numUnorderedAccessSlots()) 
		throw UnsupportedFeatureException("shader resource views for buffers unsupported");

	Context::LockGuard lock(getParentContext()); 
	initializeDriver();
}

LLGL_NAMESPACE_END;