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
	return std::make_shared<Direct3D11Capabilities>(shared_from_this()); 
}

BufferPtr Direct3D11Context::createBufferImpl(uint32_t width, FormatPtr format, bool isStreaming)
{
	auto ret =  std::make_shared<Direct3D11Buffer>(shared_from_this(), width, format, isStreaming);
	ret->initialize();
	return ret;

}

FormatPtr Direct3D11Context::createFormatImpl(FormatType type, uint32_t vectorSize)
{
	auto ret =  std::make_shared<Direct3D11Format>(shared_from_this(), type, vectorSize);
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

void* Direct3D11Context::mapResourceImpl(ResourcePtr resource, MapType type)
{
	if(auto buf = std::dynamic_pointer_cast<Direct3D11Buffer>(resource))
	{
		auto d3dMapType = (type == MapType::Read)? D3D11_MAP_READ: D3D11_MAP_WRITE;
		HRESULT hr = S_OK;
		D3D11_MAPPED_SUBRESOURCE rs;
		rs.RowPitch = 0;
		rs.pData = 0;
		hr = _ctx->Map(buf->_buf, 0, d3dMapType, 0, &rs);
		CHECK_HRESULT(hr);
		return rs.pData;
	}
	throw NotImplementedException();
}

void Direct3D11Context::unmapResourceImpl(ResourcePtr resource)
{
	if(auto buf = std::dynamic_pointer_cast<Direct3D11Buffer>(resource))
	{
		_ctx->Unmap(buf->_buf, 0);
		return;
	}

	throw NotImplementedException();
}

LLGL_NAMESPACE_END2;