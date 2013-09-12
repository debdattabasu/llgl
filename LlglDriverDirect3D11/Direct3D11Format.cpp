#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);


Direct3D11Format::Direct3D11Format(ContextPtr parentContext, FormatType type, uint32_t vectorSize) : 
	Format(parentContext, type, vectorSize)
{

}

Direct3D11Format::~Direct3D11Format()
{

}

void Direct3D11Format::initialize()
{
	Format::initialize();
	switch(getType())
	{
	case FormatType::Raw:
		_dxgiFormat = DXGI_FORMAT_R32_TYPELESS;
		break;
	case FormatType::Float:
		switch(getVectorSize())
		{
		case 1:
			_dxgiFormat = DXGI_FORMAT_R32_FLOAT;
			break;
		case 2:
			_dxgiFormat = DXGI_FORMAT_R32G32_FLOAT;
			break;
		case 4:
			_dxgiFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
			break;
		}
		break;
	case FormatType::Half:
		switch(getVectorSize())
		{
		case 1:
			_dxgiFormat = DXGI_FORMAT_R16_FLOAT;
			break;
		case 2:
			_dxgiFormat = DXGI_FORMAT_R16G16_FLOAT;
			break;
		case 4:
			_dxgiFormat = DXGI_FORMAT_R16G16B16A16_FLOAT;
			break;
		}
		break;	
	case FormatType::Int32:
		switch(getVectorSize())
		{
		case 1:
			_dxgiFormat = DXGI_FORMAT_R32_SINT;
			break;
		case 2:
			_dxgiFormat = DXGI_FORMAT_R32G32_SINT;
			break;
		case 4:
			_dxgiFormat = DXGI_FORMAT_R32G32B32A32_SINT;
			break;
		}
		break;
	case FormatType::Int16:
		switch(getVectorSize())
		{
		case 1:
			_dxgiFormat = DXGI_FORMAT_R16_SINT;
			break;
		case 2:
			_dxgiFormat = DXGI_FORMAT_R16G16_SINT;
			break;
		case 4:
			_dxgiFormat = DXGI_FORMAT_R16G16B16A16_SINT;
			break;
		}
		break;	
	case FormatType::Uint32:
		switch(getVectorSize())
		{
		case 1:
			_dxgiFormat = DXGI_FORMAT_R32_UINT;
			break;
		case 2:
			_dxgiFormat = DXGI_FORMAT_R32G32_UINT;
			break;
		case 4:
			_dxgiFormat = DXGI_FORMAT_R32G32B32A32_UINT;
			break;
		}
		break;	
	case FormatType::Uint16:
		switch(getVectorSize())
		{
		case 1:
			_dxgiFormat = DXGI_FORMAT_R16_UINT;
			break;
		case 2:
			_dxgiFormat = DXGI_FORMAT_R16G16_UINT;
			break;
		case 4:
			_dxgiFormat = DXGI_FORMAT_R16G16B16A16_UINT;
			break;
		}
		break;

	case FormatType::Snorm16:
		switch(getVectorSize())
		{
		case 1:
			_dxgiFormat = DXGI_FORMAT_R16_SNORM;
			break;
		case 2:
			_dxgiFormat = DXGI_FORMAT_R16G16_SNORM;
			break;
		case 4:
			_dxgiFormat = DXGI_FORMAT_R16G16B16A16_SNORM;
			break;
		}
		break;	
	case FormatType::Snorm8:
		switch(getVectorSize())
		{
		case 1:
			_dxgiFormat = DXGI_FORMAT_R8_SNORM;
			break;
		case 2:
			_dxgiFormat = DXGI_FORMAT_R8G8_SNORM;
			break;
		case 4:
			_dxgiFormat = DXGI_FORMAT_R8G8B8A8_SNORM;
			break;
		}
		break;		
	case FormatType::Unorm16:
		switch(getVectorSize())
		{
		case 1:
			_dxgiFormat = DXGI_FORMAT_R16_UNORM;
			break;
		case 2:
			_dxgiFormat = DXGI_FORMAT_R16G16_UNORM;
			break;
		case 4:
			_dxgiFormat = DXGI_FORMAT_R16G16B16A16_UNORM;
			break;
		}
		break;	
	case FormatType::Unorm8:
		switch(getVectorSize())
		{
		case 1:
			_dxgiFormat = DXGI_FORMAT_R8_UNORM;
			break;
		case 2:
			_dxgiFormat = DXGI_FORMAT_R8G8_UNORM;
			break;
		case 4:
			_dxgiFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
			break;
		}
		break;	

	case FormatType::Index32:
		_dxgiFormat = DXGI_FORMAT_R32_UINT;
		break;	

	case FormatType::Index16:
		_dxgiFormat = DXGI_FORMAT_R16_UINT;
		break;
	}

}

DXGI_FORMAT Direct3D11Format::getDxgiFormat()
{
	return _dxgiFormat;
}

LLGL_NAMESPACE_END2;