#include "Library.h"

LLGL_NAMESPACE(Llgl);

BufferIndexArrayView::BufferIndexArrayView(BufferPtr parentBuffer) :
	BufferView(parentBuffer)
{

}

BufferIndexArrayView::~BufferIndexArrayView()
{

}

void BufferIndexArrayView::initialize()
{
	if(getParentResource()->getFormat()->getUsage() != FormatUsage::IndexBuffer)
		throw InvalidArgumentException("index array views unsupported by format");

	Context::LockGuard lock(getParentContext()); 
	initializeDriver();
}

LLGL_NAMESPACE_END;