#include "Library.h"

LLGL_NAMESPACE(Llgl);

BufferView::BufferView(BufferPtr parentBuffer) : ResourceView(parentBuffer)
{

}

BufferView::~BufferView()
{

}

BufferPtr BufferView::getParentResource() const
{
	return std::dynamic_pointer_cast<Buffer>(ResourceView::getParentResource());
}

LLGL_NAMESPACE_END;