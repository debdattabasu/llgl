#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture3DDataAccessView::Texture3DDataAccessView(Texture3DPtr parentTexture, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ,
	uint32_t width, uint32_t height, uint32_t depth, uint32_t mipLevel) :
	Texture3DView(parentTexture), _offsetX(offsetX), _offsetY(offsetY), _offsetZ(offsetZ), 
	_width(width), _height(height), _depth(depth), _mipLevel(mipLevel)
{

}

Texture3DDataAccessView::~Texture3DDataAccessView()
{

}

uint32_t Texture3DDataAccessView::getOffsetX() const
{
	return _offsetX;
}

uint32_t Texture3DDataAccessView::getOffsetY() const
{
	return _offsetY;
}

uint32_t Texture3DDataAccessView::getOffsetZ() const
{
	return _offsetZ;
}

uint32_t Texture3DDataAccessView::getWidth() const
{
	return _width;
}

uint32_t Texture3DDataAccessView::getHeight() const
{
	return _height;
}

uint32_t Texture3DDataAccessView::getDepth() const
{
	return _depth;
}

uint32_t Texture3DDataAccessView::getMipLevel() const
{
	return _mipLevel;
}

void Texture3DDataAccessView::getData(void* data)
{
	if(data == 0) throw InvalidArgumentException("argument null");

	Context::LockGuard lock(getParentContext()); 
	getDataDriver(data);
}

void Texture3DDataAccessView::setData(void* data)
{
	if(data == 0) throw InvalidArgumentException("argument null");
	
	Context::LockGuard lock(getParentContext()); 
	setDataDriver(data);
}

void Texture3DDataAccessView::initialize()
{
	if(getMipLevel() + 1 > getParentResource()->getNumMips())
		throw InvalidArgumentException("out of bounds");

	if(getWidth() == 0 || getHeight() == 0 || getDepth() == 0) throw InvalidArgumentException("invalid dimensions");
	if((getOffsetX() + getWidth()) > getParentResource()->getWidth(getMipLevel())
		|| (getOffsetY() + getHeight()) > getParentResource()->getHeight(getMipLevel())
		|| (getOffsetZ() + getDepth()) > getParentResource()->getDepth(getMipLevel())) 
		throw InvalidArgumentException("out of bounds");

	Context::LockGuard lock(getParentContext()); 
	initializeDriver();
}

void Texture3DDataAccessView::copyFrom(Texture3DDataAccessViewPtr src)
{
	if (!src->getParentResource()->getFormat()->equals(getParentResource()->getFormat()))
		throw InvalidArgumentException("format mismatch");
	if (src->getWidth() != getWidth() || src->getHeight() != getHeight() || src->getDepth() != getDepth())
		throw InvalidArgumentException("dimension mismatch");	

  	Context::LockGuard lock(getParentContext());
	copyFromDriver(src);
}

LLGL_NAMESPACE_END;