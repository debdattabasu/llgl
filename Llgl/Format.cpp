#include "Library.h"

LLGL_NAMESPACE(Llgl);

Format::Format(ContextPtr parentContext, FormatType type, uint32_t vectorSize):
	ContextChild(parentContext), _type(type), _vectorSize(vectorSize)
{

}

Format::~Format()
{
	
}

FormatType Format::getType()
{
	return _type;
}

FormatUsage Format::getUsage()
{
	FormatUsage ret = FormatUsage::General;
	switch(_type)
	{
	case FormatType::Raw:
		ret = FormatUsage::RawBuffer; 
		break;
	case FormatType::Index16:
		ret = FormatUsage::IndexBuffer; 
		break;
	case FormatType::Index32:
		ret = FormatUsage::IndexBuffer;
		break;	
	case FormatType::DepthUnorm24Stencil8:
		ret = FormatUsage::DepthTexture;
		break;	
	case FormatType::DepthFloat32Stencil24:
		ret = FormatUsage::DepthTexture;
		break;	
	case FormatType::DepthFloat32:
		ret = FormatUsage::DepthTexture;
		break;	
	case FormatType::DepthUnorm16:
		ret = FormatUsage::DepthTexture;
		break;	
	}
	return ret;
}

uint32_t Format::getSize()
{
	uint32_t size  = 1;
	switch(_type)
	{
	case FormatType::Raw:
		size = 4; 
		break;

	case FormatType::Float:
		size = 4; 
		break;

	case FormatType::Half:
		size = 2; 
		break;

	case FormatType::Int32:
		size = 4; 
		break;

	case FormatType::Int16:
		size = 2; 
		break;

	case FormatType::Uint32:
		size = 4; 
		break;

	case FormatType::Uint16:
		size = 2; 
		break;

	case FormatType::Snorm16:
		size = 2; 
		break;

	case FormatType::Snorm8:
		size = 1; 
		break;

	case FormatType::Unorm16:
		size = 2; 
		break;

	case FormatType::Unorm8:
		size = 1; 
		break;

	case FormatType::Index16:
		size = 2; 
		break;

	case FormatType::Index32:
		size = 4; 
		break;	

	case FormatType::DepthUnorm24Stencil8:
		size = 4; 
		break;	

	case FormatType::DepthFloat32Stencil24:
		size = 8; 
		break;	

	case FormatType::DepthFloat32:
		size = 4; 
		break;	
		
	case FormatType::DepthUnorm16:
		size = 2; 
		break;	

	}
	size *= _vectorSize;
	return size;
}

uint32_t Format::getVectorSize()
{
	return _vectorSize;
}

bool Format::equals(FormatPtr other)
{
	if(_type == other->_type && _vectorSize == other->_vectorSize)
		return true;
	return false;
}

void Format::initialize()
{
	if(_vectorSize != 1 && _vectorSize != 2 && _vectorSize != 4) throw InvalidArgumentException("vector size must be 1, 2, or 4");
	if(getUsage() != FormatUsage::General && _vectorSize != 1) throw InvalidArgumentException("vector size for given format must be 1");
}

LLGL_NAMESPACE_END;