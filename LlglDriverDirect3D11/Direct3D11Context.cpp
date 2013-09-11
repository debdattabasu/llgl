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

void Direct3D11Context::copyBufferImpl(BufferPtr srcBuffer, uint32_t srcWidth, uint32_t srcOffset, BufferPtr destBuffer, uint32_t destOffset)
{
	auto elementSize = destBuffer->getFormat()->getSize();
	auto srcBuf = std::dynamic_pointer_cast<Direct3D11Buffer>(srcBuffer)->_buf;
	auto destBuf = std::dynamic_pointer_cast<Direct3D11Buffer>(destBuffer)->_buf;

	D3D11_BOX bx;
	bx.left = srcOffset * elementSize; 
	bx.right = (srcOffset + srcWidth) * elementSize;
	bx.top = 0;
	bx.bottom = 1;
	bx.front = 0;
	bx.back = 1;
	_ctx->CopySubresourceRegion(destBuf, 0, destOffset , 0, 0, srcBuf, 0, &bx);
}

void Direct3D11Context::copyResourceImpl(ResourcePtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ, 
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
		ResourcePtr dest, uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ, 
		uint32_t destMipLevel, uint32_t destArrayIndex)
{
	ID3D11Resource* srcRes = 0; 
	ID3D11Resource* destRes = 0;
	uint32_t srcSubRes = src->getNumMips() * srcArrayIndex + srcMipLevel;
	uint32_t destSubRes = dest->getNumMips()  * destArrayIndex + destMipLevel;

	D3D11_BOX bx;
	switch(src->getType())
	{
	case ResourceType::Buffer:
	{
		auto elementSize = src->getFormat()->getSize();
		srcRes = std::dynamic_pointer_cast<Direct3D11Buffer>(src)->_buf;
		destRes = std::dynamic_pointer_cast<Direct3D11Buffer>(dest)->_buf;
		bx.left = srcOffsetX * elementSize; 
		bx.right = (srcOffsetX + srcWidth) * elementSize;
		bx.top = 0;
		bx.bottom = 1;
		bx.front = 0;
		bx.back = 1;
		break;
	}
	case ResourceType::Texture1D:

		break;
	case ResourceType::Texture2D:

		break;
	case ResourceType::Texture3D:

		break;
	}

	_ctx->CopySubresourceRegion(destRes, destSubRes, destOffsetX , destOffsetY, destOffsetZ, srcRes, srcSubRes, &bx);

}

LLGL_NAMESPACE_END2;