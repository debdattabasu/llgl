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
		throw UnsupportedFeatureException("unordered access views unsupported");

	Context::LockGuard lock(getParentContext()); 
	initializeDriver();
}

LLGL_NAMESPACE_END;