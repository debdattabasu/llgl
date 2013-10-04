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
	Context::LockGuard lock(getParentContext()); 
	if(!getParentContext()->getCapabilities()->numUnorderedAccessSlots()) 
		throw UnsupportedFeatureException("shader resource views for buffers unsupported");
	initializeImpl();
}

LLGL_NAMESPACE_END;