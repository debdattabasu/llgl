#include "Library.h"

LLGL_NAMESPACE(Llgl);

Resource::Resource(ContextPtr parentContext, ResourceType resType, uint32_t width, 
	uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming) : 
	ContextChild(parentContext), _resourceType(resType), _numDims(1), _width(width), _height(1), _depth(1), 
	_numMips(numMips), _arraySize(arraySize), _isStreaming(isStreaming), _isMapped(0), _format(format)
{
	
}

Resource::Resource(ContextPtr parentContext, ResourceType resType, uint32_t width, uint32_t height, 
	uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming): 
	ContextChild(parentContext), _resourceType(resType), _numDims(2), _width(width), _height(height), _depth(1), 
	_numMips(numMips), _arraySize(arraySize), _isStreaming(isStreaming), _isMapped(0), _format(format)
{

}

Resource::Resource(ContextPtr parentContext, ResourceType resType, uint32_t width, uint32_t height, uint32_t depth, 
	uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming): 
	ContextChild(parentContext), _resourceType(resType), _numDims(3), _width(width), _height(height), _depth(depth), 
	_numMips(numMips), _arraySize(arraySize), _isStreaming(isStreaming), _isMapped(0), _format(format)
{

}

Resource::~Resource()
{
	
}

FormatPtr Resource::getFormat() const
{
	return _format;
}

bool Resource::isStreaming() const
{
	return _isStreaming;
}

bool Resource::isMapped(uint32_t mipLevel, uint32_t arrayIndex) const
{
	if(mipLevel < _numMips && arrayIndex < _arraySize)
		return _isMapped[_numMips * arrayIndex + mipLevel];

	throw InvalidArgumentException("out of bounds");
}

void Resource::setMapped(uint32_t mipLevel, uint32_t arrayIndex, bool value)
{
	_isMapped[_numMips * arrayIndex + mipLevel] = value;
}

uint32_t Resource::getWidth() const
{
	return _width;
}

uint32_t Resource::getHeight() const
{
	return _height;
}

uint32_t Resource::getDepth() const
{
	return _depth;
}

uint32_t Resource::getNumDimensions() const
{
	return _numDims;
}

ResourceType Resource::getType() const
{
	return _resourceType;
}

uint32_t Resource::getNumMips()  const
{
	return _numMips;
}

uint32_t Resource::getArraySize() const
{
	return _arraySize;
}

void Resource::initialize() 
{
	if(_width == 0 || _height == 0 || _depth == 0 || _numMips ==0 || _arraySize == 0 ) throw InvalidArgumentException("dimensions invalid");
	_isMapped.resize(_numMips * _arraySize);
}

void* Resource::map(uint32_t mipLevel, uint32_t arrayIndex, MapType type)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(!_isStreaming) throw InvalidOperationException("can not map non-streaming rsource");
	if((mipLevel + 1) > getNumMips() || (arrayIndex + 1) > getArraySize())
		throw InvalidArgumentException("out of bounds");
	if(isMapped(mipLevel, arrayIndex)) throw InvalidOperationException("resource already mapped");
	auto ret = mapImpl(mipLevel, arrayIndex, type);
	setMapped(mipLevel, arrayIndex, 1);
	return ret;
}

void Resource::unmap(uint32_t mipLevel, uint32_t arrayIndex)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if(!isMapped(mipLevel, arrayIndex)) throw InvalidOperationException("resource already unmapped");
	unmapImpl(mipLevel, arrayIndex);
	setMapped(mipLevel, arrayIndex, 0);
}

void Resource::copyFrom(ResourcePtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ, 
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
		uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ, 
		uint32_t destMipLevel, uint32_t destArrayIndex)
{
	std::lock_guard<std::mutex> lock(getParentContext()->_mutex); 
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("resource format mismatch");

	if (src->getType() != getType())
		throw InvalidArgumentException("resource type mismatch");

	if((srcOffsetX + srcWidth) > src->getWidth() || (destOffsetX + srcWidth) > getWidth() 
	  	|| (srcOffsetY + srcHeight) > src->getHeight() || (destOffsetY + srcHeight) > getHeight()
	   	|| (srcOffsetZ + srcDepth) > src->getDepth() || (destOffsetZ + srcDepth) > getDepth()
	   	|| (srcMipLevel + 1) > src->getNumMips() || (srcArrayIndex + 1) > src->getArraySize() 
	   	|| (destMipLevel + 1) > getNumMips() || (destArrayIndex + 1) > getArraySize())
			throw InvalidArgumentException("out of bounds");

	copyFromImpl(src, srcOffsetX, srcOffsetY, srcOffsetZ, srcWidth, srcHeight, srcDepth, srcMipLevel, srcArrayIndex, 
		destOffsetX, destOffsetY, destOffsetZ, destMipLevel, destArrayIndex);

}

LLGL_NAMESPACE_END;