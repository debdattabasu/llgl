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
	return std::shared_ptr<Direct3D11Capabilities>(new Direct3D11Capabilities(shared_from_this())); 
}

BufferPtr Direct3D11Context::createBufferImpl(uint32_t width, FormatPtr format, bool isStreaming)
{
	auto ret =  std::shared_ptr<Direct3D11Buffer>(new Direct3D11Buffer(shared_from_this(), width, format, isStreaming));
	ret->initialize();
	return ret;
}

Texture1DPtr Direct3D11Context::createTexture1DImpl(uint32_t width, uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming)
{
	auto ret =  std::shared_ptr<Direct3D11Texture1D>(new Direct3D11Texture1D(shared_from_this(), width, numMips, arraySize, format, isStreaming));
	ret->initialize();
	return ret;
}

Texture2DPtr Direct3D11Context::createTexture2DImpl(uint32_t width, uint32_t height, uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming)
{
	auto ret =  std::shared_ptr<Direct3D11Texture2D>(new Direct3D11Texture2D(shared_from_this(), width, height, numMips, arraySize, format, isStreaming));
	ret->initialize();
	return ret;
}

FormatPtr Direct3D11Context::createFormatImpl(FormatType type, uint32_t vectorSize)
{
	auto ret =  std::shared_ptr<Direct3D11Format>(new Direct3D11Format(shared_from_this(), type, vectorSize));
	ret->initialize();
	return ret;
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
		D3D11_SDK_VERSION, &_dev,  &_featureLevel, &_ctx );
	CHECK_HRESULT(hr);
}

LLGL_NAMESPACE_END2;