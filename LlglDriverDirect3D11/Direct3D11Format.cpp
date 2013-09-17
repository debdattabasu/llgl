#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);


Direct3D11Format::Direct3D11Format(ContextPtr parentContext, FormatType type, uint32_t vectorSize) : 
	Format(parentContext, type, vectorSize)
{

}

Direct3D11Format::~Direct3D11Format()
{

}

void Direct3D11Format::initializeImpl()
{
	switch(getType())
	{
	case FormatType::Raw:
		_dxgiFormatTypeless = DXGI_FORMAT_R32_TYPELESS;
		_dxgiFormatTyped = DXGI_FORMAT_UNKNOWN;
		_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
		break;
	case FormatType::Float:
		switch(getVectorSize())
		{
		case 1:
			_dxgiFormatTyped = DXGI_FORMAT_R32_FLOAT;
			_dxgiFormatTypeless = DXGI_FORMAT_R32_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		case 2:
			_dxgiFormatTyped = DXGI_FORMAT_R32G32_FLOAT;
			_dxgiFormatTypeless = DXGI_FORMAT_R32G32_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		case 4:
			_dxgiFormatTyped = DXGI_FORMAT_R32G32B32A32_FLOAT;
			_dxgiFormatTypeless = DXGI_FORMAT_R32G32B32A32_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		}
		break;
	case FormatType::Half:
		switch(getVectorSize())
		{
		case 1:
			_dxgiFormatTyped = DXGI_FORMAT_R16_FLOAT;
			_dxgiFormatTypeless = DXGI_FORMAT_R16_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		case 2:
			_dxgiFormatTyped = DXGI_FORMAT_R16G16_FLOAT;
			_dxgiFormatTypeless = DXGI_FORMAT_R16G16_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		case 4:
			_dxgiFormatTyped = DXGI_FORMAT_R16G16B16A16_FLOAT;
			_dxgiFormatTypeless = DXGI_FORMAT_R16G16B16A16_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		}
		break;	
	case FormatType::Int32:
		switch(getVectorSize())
		{
		case 1:
			_dxgiFormatTyped = DXGI_FORMAT_R32_SINT;
			_dxgiFormatTypeless = DXGI_FORMAT_R32_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		case 2:
			_dxgiFormatTyped = DXGI_FORMAT_R32G32_SINT;
			_dxgiFormatTypeless = DXGI_FORMAT_R32G32_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		case 4:
			_dxgiFormatTyped = DXGI_FORMAT_R32G32B32A32_SINT;
			_dxgiFormatTypeless = DXGI_FORMAT_R32G32B32A32_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		}
		break;
	case FormatType::Int16:
		switch(getVectorSize())
		{
		case 1:
			_dxgiFormatTyped = DXGI_FORMAT_R16_SINT;
			_dxgiFormatTypeless = DXGI_FORMAT_R16_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		case 2:
			_dxgiFormatTyped = DXGI_FORMAT_R16G16_SINT;
			_dxgiFormatTypeless = DXGI_FORMAT_R16G16_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		case 4:
			_dxgiFormatTyped = DXGI_FORMAT_R16G16B16A16_SINT;
			_dxgiFormatTypeless = DXGI_FORMAT_R16G16B16A16_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		}
		break;	
	case FormatType::Uint32:
		switch(getVectorSize())
		{
		case 1:
			_dxgiFormatTyped = DXGI_FORMAT_R32_UINT;
			_dxgiFormatTypeless = DXGI_FORMAT_R32_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		case 2:
			_dxgiFormatTyped = DXGI_FORMAT_R32G32_UINT;
			_dxgiFormatTypeless = DXGI_FORMAT_R32G32_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		case 4:
			_dxgiFormatTyped = DXGI_FORMAT_R32G32B32A32_UINT;
			_dxgiFormatTypeless = DXGI_FORMAT_R32G32B32A32_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		}
		break;	
	case FormatType::Uint16:
		switch(getVectorSize())
		{
		case 1:
			_dxgiFormatTyped = DXGI_FORMAT_R16_UINT;
			_dxgiFormatTypeless = DXGI_FORMAT_R16_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		case 2:
			_dxgiFormatTyped = DXGI_FORMAT_R16G16_UINT;
			_dxgiFormatTypeless = DXGI_FORMAT_R16G16_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		case 4:
			_dxgiFormatTyped = DXGI_FORMAT_R16G16B16A16_UINT;
			_dxgiFormatTypeless = DXGI_FORMAT_R16G16B16A16_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		}
		break;

	case FormatType::Snorm16:
		switch(getVectorSize())
		{
		case 1:
			_dxgiFormatTyped = DXGI_FORMAT_R16_SNORM;
			_dxgiFormatTypeless = DXGI_FORMAT_R16_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		case 2:
			_dxgiFormatTyped = DXGI_FORMAT_R16G16_SNORM;
			_dxgiFormatTypeless = DXGI_FORMAT_R16G16_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		case 4:
			_dxgiFormatTyped = DXGI_FORMAT_R16G16B16A16_SNORM;
			_dxgiFormatTypeless = DXGI_FORMAT_R16G16B16A16_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		}
		break;	
	case FormatType::Snorm8:
		switch(getVectorSize())
		{
		case 1:
			_dxgiFormatTyped = DXGI_FORMAT_R8_SNORM;
			_dxgiFormatTypeless = DXGI_FORMAT_R8_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		case 2:
			_dxgiFormatTyped = DXGI_FORMAT_R8G8_SNORM;
			_dxgiFormatTypeless = DXGI_FORMAT_R8G8_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		case 4:
			_dxgiFormatTyped = DXGI_FORMAT_R8G8B8A8_SNORM;
			_dxgiFormatTypeless = DXGI_FORMAT_R8G8B8A8_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		}
		break;		
	case FormatType::Unorm16:
		switch(getVectorSize())
		{
		case 1:
			_dxgiFormatTyped = DXGI_FORMAT_R16_UNORM;
			_dxgiFormatTypeless = DXGI_FORMAT_R16_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		case 2:
			_dxgiFormatTyped = DXGI_FORMAT_R16G16_UNORM;
			_dxgiFormatTypeless = DXGI_FORMAT_R16G16_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		case 4:
			_dxgiFormatTyped = DXGI_FORMAT_R16G16B16A16_UNORM;
			_dxgiFormatTypeless = DXGI_FORMAT_R16G16B16A16_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		}
		break;	
	case FormatType::Unorm8:
		switch(getVectorSize())
		{
		case 1:
			_dxgiFormatTyped = DXGI_FORMAT_R8_UNORM;
			_dxgiFormatTypeless = DXGI_FORMAT_R8_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		case 2:
			_dxgiFormatTyped = DXGI_FORMAT_R8G8_UNORM;
			_dxgiFormatTypeless = DXGI_FORMAT_R8G8_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		case 4:
			_dxgiFormatTyped = DXGI_FORMAT_R8G8B8A8_UNORM;
			_dxgiFormatTypeless = DXGI_FORMAT_R8G8B8A8_TYPELESS;
			_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
			break;
		}
		break;	

	case FormatType::Index32:
		_dxgiFormatTyped = DXGI_FORMAT_R32_UINT;
		_dxgiFormatTypeless = DXGI_FORMAT_R32_TYPELESS;
		_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
		break;	

	case FormatType::Index16:
		_dxgiFormatTyped = DXGI_FORMAT_R16_UINT;
		_dxgiFormatTypeless = DXGI_FORMAT_R16_TYPELESS;
		_dxgiFormatDepthTyped = DXGI_FORMAT_UNKNOWN;
		break;

	case FormatType::DepthUnorm24StencilUint8: 
		_dxgiFormatTyped = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		_dxgiFormatTypeless = DXGI_FORMAT_R24G8_TYPELESS;
		_dxgiFormatDepthTyped = DXGI_FORMAT_D24_UNORM_S8_UINT;
		break;

	case FormatType::DepthFloat32StencilUint8:
		_dxgiFormatTyped = DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
		_dxgiFormatTypeless = DXGI_FORMAT_R32G8X24_TYPELESS;
		_dxgiFormatDepthTyped = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
		break;

	case FormatType::DepthFloat32:
		_dxgiFormatTyped = DXGI_FORMAT_R32_FLOAT;
		_dxgiFormatTypeless = DXGI_FORMAT_R32_TYPELESS;
		_dxgiFormatDepthTyped = DXGI_FORMAT_D32_FLOAT;
		break;
		
	case FormatType::DepthUnorm16:
		_dxgiFormatTyped = DXGI_FORMAT_R16_UNORM;
		_dxgiFormatTypeless = DXGI_FORMAT_R16_TYPELESS;
		_dxgiFormatDepthTyped =  DXGI_FORMAT_D16_UNORM;
		break;
	}

}

DXGI_FORMAT Direct3D11Format::getDxgiFormatTyped()
{
	return _dxgiFormatTyped;
}

DXGI_FORMAT Direct3D11Format::getDxgiFormatTypeless()
{
	return _dxgiFormatTypeless;
}

DXGI_FORMAT Direct3D11Format::getDxgiFormatDepthTyped()
{
	return _dxgiFormatDepthTyped;
}

LLGL_NAMESPACE_END2;