#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

Direct3D11Context::Direct3D11Context() : Context(), _dev(0), _ctx(0)
{

}

Direct3D11Context::~Direct3D11Context()
{
	SAFE_RELEASE(_dev);
	SAFE_RELEASE(_ctx);
}

CapabilitiesPtr Direct3D11Context::getCapabilities()
{
	return CapabilitiesPtr(new Direct3D11Capabilities(shared_from_this())); 
}

BufferPtr Direct3D11Context::createBufferDriver(uint32_t width, FormatPtr format)
{
	return BufferPtr(new Direct3D11Buffer(shared_from_this(), width, format));
}


Texture1DPtr Direct3D11Context::createTexture1DDriver(uint32_t width, uint32_t numMips, uint32_t arraySize, FormatPtr format)
{
	return Texture1DPtr(new Direct3D11Texture1D(shared_from_this(), width, numMips, arraySize, format));
}

Texture2DPtr Direct3D11Context::createTexture2DDriver(uint32_t width, uint32_t height, uint32_t numMips, uint32_t arraySize, FormatPtr format)
{
	return Texture2DPtr(new Direct3D11Texture2D(shared_from_this(), width, height, numMips, arraySize, format));
}

FormatPtr Direct3D11Context::createFormatDriver(FormatType type, uint32_t vectorSize)
{
	return FormatPtr(new Direct3D11Format(shared_from_this(), type, vectorSize));
}

Texture3DPtr Direct3D11Context::createTexture3DDriver(uint32_t width, uint32_t height, uint32_t depth, uint32_t numMips, FormatPtr format)
{
	return Texture3DPtr(new Direct3D11Texture3D(shared_from_this(), width, height, depth, numMips, format));
}

ID3D11Device* Direct3D11Context::getDirect3D11Device() const
{
	return _dev;
}

ID3D11DeviceContext* Direct3D11Context::getDirect3D11DeviceContext() const
{
	return _ctx;
}

D3D_FEATURE_LEVEL Direct3D11Context::getDirect3D11FeatureLevel() const
{
	return _featureLevel;
}


void Direct3D11Context::initialize()
{
	HRESULT hr = S_OK;
	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);
	hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevels, numFeatureLevels, 
		D3D11_SDK_VERSION, &_dev,  &_featureLevel, &_ctx);
	CHECK_HRESULT(hr);
}

LLGL_NAMESPACE_END2;