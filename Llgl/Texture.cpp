#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture::Texture(ContextPtr parentContext, uint32_t numDimensions, uint32_t numMips, uint32_t arraySize, FormatPtr format) : 
	Resource(parentContext, numDimensions, format), _numMips(numMips), _arraySize(arraySize)
{

}

Texture::~Texture()
{

}

void Texture::initialize()
{
	Resource::initialize();
	if(getArraySize() == 0) 
		throw InvalidArgumentException("invalid dimensions");
}
	
uint32_t Texture::getNumMips()  const
{
	return _numMips;
}

uint32_t Texture::getArraySize() const
{
	return _arraySize;
}

LLGL_NAMESPACE_END;