#include "Library.h"

LLGL_NAMESPACE(Llgl);

BufferVertexArrayView::BufferVertexArrayView(BufferPtr parentBuffer) :
	BufferView(parentBuffer)
{

}

BufferVertexArrayView::~BufferVertexArrayView()
{

}

void BufferVertexArrayView::initialize()
{
	if(getParentResource()->getFormat()->getUsage() != FormatUsage::General)
		throw InvalidArgumentException("vertex array views unsupported by format");

	Context::LockGuard lock(getParentContext()); 
	initializeDriver();
}

LLGL_NAMESPACE_END;