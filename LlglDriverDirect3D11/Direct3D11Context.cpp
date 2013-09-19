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

BufferPtr Direct3D11Context::createBufferImpl(uint32_t width, FormatPtr format)
{
	return BufferPtr(new Direct3D11Buffer(shared_from_this(), width, format));
}

BufferStreamPtr Direct3D11Context::createBufferStreamImpl(uint32_t width, FormatPtr format)
{
	return BufferStreamPtr(new Direct3D11BufferStream(shared_from_this(), width, format));
}

Texture1DPtr Direct3D11Context::createTexture1DImpl(uint32_t width, uint32_t numMips, FormatPtr format)
{
	return Texture1DPtr(new Direct3D11Texture1D(shared_from_this(), width, numMips, format));
}

Texture1DStreamPtr Direct3D11Context::createTexture1DStreamImpl(uint32_t width, FormatPtr format)
{
	return Texture1DStreamPtr(new Direct3D11Texture1DStream(shared_from_this(), width, format));
}

Texture2DPtr Direct3D11Context::createTexture2DImpl(uint32_t width, uint32_t height, uint32_t numMips, FormatPtr format)
{
	return Texture2DPtr(new Direct3D11Texture2D(shared_from_this(), width, height, numMips, format));
}

Texture2DStreamPtr Direct3D11Context::createTexture2DStreamImpl(uint32_t width, uint32_t height, FormatPtr format)
{
	return Texture2DStreamPtr(new Direct3D11Texture2DStream(shared_from_this(), width, height, format));
}

FormatPtr Direct3D11Context::createFormatImpl(FormatType type, uint32_t vectorSize)
{
	return FormatPtr(new Direct3D11Format(shared_from_this(), type, vectorSize));
}

Texture3DPtr Direct3D11Context::createTexture3DImpl(uint32_t width, uint32_t height, uint32_t depth, uint32_t numMips, FormatPtr format)
{
	return Texture3DPtr(new Direct3D11Texture3D(shared_from_this(), width, height, depth, numMips, format));
}

Texture3DStreamPtr Direct3D11Context::createTexture3DStreamImpl(uint32_t width, uint32_t height, uint32_t depth, FormatPtr format) 
{
	return Texture3DStreamPtr(new Direct3D11Texture3DStream(shared_from_this(), width, height, depth, format));
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