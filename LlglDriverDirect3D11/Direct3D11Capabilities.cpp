#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);



Direct3D11Capabilities::Direct3D11Capabilities(ContextPtr parentContext) : Capabilities(parentContext)
{
	_featureLevel = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_featureLevel;
}

Direct3D11Capabilities::~Direct3D11Capabilities() 
{

}

bool Direct3D11Capabilities::supportsRawBuffer() 
{
	auto ret = false;
	switch (_featureLevel)
	{
	case D3D_FEATURE_LEVEL_11_1:
		ret = true;
		break;
	case D3D_FEATURE_LEVEL_11_0:
		ret = true;
		break;
	}
	return ret;
}

bool Direct3D11Capabilities::supportsShaderResourceBuffer() 
{
	auto ret = false;
	switch (_featureLevel)
	{
	case D3D_FEATURE_LEVEL_11_1:
		ret = true;
		break;
	case D3D_FEATURE_LEVEL_11_0:
		ret = true;
		break;
	case D3D_FEATURE_LEVEL_10_1:
		ret = true;
		break;
	case D3D_FEATURE_LEVEL_10_0:
		ret = true;
		break;
	}
	return ret;
}

uint32_t Direct3D11Capabilities::numUnorderedAccessSlots() 
{
	uint32_t ret = 0;
	switch (_featureLevel)
	{
	case D3D_FEATURE_LEVEL_11_1:
		ret = 64;
		break;
	case D3D_FEATURE_LEVEL_11_0:
		ret = 8;
		break;
	}
	return ret;
}

LLGL_NAMESPACE_END2;