#include "Library.h"

LLGL_NAMESPACE(Llgl);

BufferDataAccessView::BufferDataAccessView(BufferPtr parentBuffer, uint32_t offset, uint32_t width) :
	BufferView(parentBuffer), _offset(offset), _width(width)
{

}

BufferDataAccessView::~BufferDataAccessView()
{

}

uint32_t BufferDataAccessView::getWidth() const
{
	return _width;
}

uint32_t BufferDataAccessView::getOffset() const
{
	return _offset;
}

void BufferDataAccessView::getData(void* data)
{
	if(data == 0) throw InvalidArgumentException("argument null");

	Context::LockGuard lock(getParentContext()); 
	getDataDriver(data);
}

void BufferDataAccessView::setData(void* data)
{
	if(data == 0) throw InvalidArgumentException("argument null");
	
	Context::LockGuard lock(getParentContext()); 
	setDataDriver(data);
}

void BufferDataAccessView::initialize()
{
	if(getWidth() == 0) throw InvalidArgumentException("invalid dimensions");
	if((getOffset() + getWidth()) > getParentResource()->getWidth()) 
		throw InvalidArgumentException("out of bounds");

	Context::LockGuard lock(getParentContext()); 
	initializeDriver();
}

void BufferDataAccessView::copyFrom(BufferDataAccessViewPtr src)
{
	if (!src->getParentResource()->getFormat()->equals(getParentResource()->getFormat()))
		throw InvalidArgumentException("format mismatch");
	if (!src->getWidth() == getWidth())
		throw InvalidArgumentException("dimension mismatch");	

  	Context::LockGuard lock(getParentContext());
	copyFromDriver(src);
}

LLGL_NAMESPACE_END;