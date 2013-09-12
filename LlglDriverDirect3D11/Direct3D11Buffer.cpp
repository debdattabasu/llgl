#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

Direct3D11Buffer::Direct3D11Buffer(ContextPtr parentContext, uint32_t width, FormatPtr format, bool isStreaming):
	Buffer(parentContext, width, format, isStreaming), _buf(0), _srv(0), _uav(0)
{

}

Direct3D11Buffer::~Direct3D11Buffer()
{
	SAFE_RELEASE(_buf);
	SAFE_RELEASE(_srv);
	SAFE_RELEASE(_uav);
}

void Direct3D11Buffer::initializeStreaming()
{
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto elementSize = getFormat()->getSize();
	auto numElements = getWidth();

	HRESULT hr = S_OK;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = numElements * elementSize;
	bd.Usage = D3D11_USAGE_STAGING;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
	hr = dev->CreateBuffer(&bd, NULL, &_buf);
	CHECK_HRESULT(hr);
}

void Direct3D11Buffer::initializeRaw()
{
	auto caps = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getCapabilities();
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmt = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormat();
	auto elementSize = getFormat()->getSize();
	auto numElements = getWidth();
	HRESULT hr = S_OK;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = numElements * elementSize;
	bd.Usage = D3D11_USAGE_DEFAULT;
	if(caps->supportsShaderResourceBuffer()) 
		bd.BindFlags |= D3D11_BIND_SHADER_RESOURCE;

	if(caps->numUnorderedAccessSlots())
		bd.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;

	bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS; 

	hr = dev->CreateBuffer(&bd, NULL, &_buf);
	CHECK_HRESULT(hr);

	if(caps->supportsShaderResourceBuffer()) 
	{

		D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
		ZeroMemory(&srvd, sizeof(srvd));
		srvd.Format = dxgiFmt;
		srvd.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
		srvd.BufferEx.FirstElement = 0;
		srvd.BufferEx.NumElements = numElements;
		srvd.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;

		hr = dev->CreateShaderResourceView(_buf, &srvd, &_srv);
		CHECK_HRESULT(hr);
	}

	if(caps->numUnorderedAccessSlots())
	{
		D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
		ZeroMemory(&uavd, sizeof(uavd));
		uavd.Format = dxgiFmt;
		uavd.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		uavd.Buffer.FirstElement = 0;
		uavd.Buffer.NumElements =  numElements;
		uavd.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
		hr = dev->CreateUnorderedAccessView(_buf, &uavd, &_uav);
		CHECK_HRESULT(hr);
	}
}

void Direct3D11Buffer::initializeVertexIndex()
{
	auto caps = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getCapabilities();
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;

	auto dxgiFmt = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormat();
	auto elementSize = getFormat()->getSize();
	auto numElements = getWidth();
	HRESULT hr = S_OK;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = numElements * elementSize;
	bd.Usage = D3D11_USAGE_DEFAULT;

	switch(getFormat()->getUsage())
	{
	case FormatUsage::General:
		bd.BindFlags |= D3D11_BIND_VERTEX_BUFFER;
		break;
	case FormatUsage::IndexBuffer:
		bd.BindFlags |= D3D11_BIND_INDEX_BUFFER;
		break;
	}
	if(caps->supportsShaderResourceBuffer()) 
		bd.BindFlags |= D3D11_BIND_SHADER_RESOURCE;

	if(caps->numUnorderedAccessSlots())
		bd.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;

	hr = dev->CreateBuffer(&bd, NULL, &_buf);
	CHECK_HRESULT(hr);

	if(caps->supportsShaderResourceBuffer()) 
	{

		D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
		ZeroMemory(&srvd, sizeof(srvd));
		srvd.Format = dxgiFmt;
		srvd.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		srvd.Buffer.FirstElement = 0;
		srvd.Buffer.ElementWidth = elementSize;
		srvd.Buffer.ElementOffset = 0;
		srvd.Buffer.NumElements = numElements;

		hr = dev->CreateShaderResourceView(_buf, &srvd, &_srv);
		CHECK_HRESULT(hr);
	}

	if(caps->numUnorderedAccessSlots())
	{
		D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
		ZeroMemory(&uavd, sizeof(uavd));
		uavd.Format = dxgiFmt;
		uavd.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		uavd.Buffer.FirstElement = 0;
		uavd.Buffer.NumElements =  numElements;
		hr = dev->CreateUnorderedAccessView(_buf, &uavd, &_uav);
		CHECK_HRESULT(hr);
	}
}

void Direct3D11Buffer::initialize()
{
	Buffer::initialize();
	if (isStreaming()) initializeStreaming();
	else if (getFormat()->getUsage() == FormatUsage::RawBuffer) initializeRaw();
	else initializeVertexIndex();
}

void* Direct3D11Buffer::mapImpl(uint32_t mipLevel, uint32_t arrayIndex, MapType type) 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	auto d3dMapType = (type == MapType::Read)? D3D11_MAP_READ: D3D11_MAP_WRITE;
	HRESULT hr = S_OK;
	D3D11_MAPPED_SUBRESOURCE rs;
	rs.RowPitch = 0;
	rs.pData = 0;
	uint32_t subRes = getNumMips() * arrayIndex + mipLevel;
	hr = ctx->Map(_buf, subRes, d3dMapType, 0, &rs);
	CHECK_HRESULT(hr);
	return rs.pData;
}

void Direct3D11Buffer::unmapImpl(uint32_t mipLevel, uint32_t arrayIndex) 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	uint32_t subRes = getNumMips() * arrayIndex + mipLevel;
	ctx->Unmap(_buf, subRes);
}

void Direct3D11Buffer::copyFromImpl(ResourcePtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ, 
	uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
	uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ, 
	uint32_t destMipLevel, uint32_t destArrayIndex) 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Buffer>(src)->_buf; 
	ID3D11Resource* destRes = _buf;
	uint32_t srcSubRes = src->getNumMips() * srcArrayIndex + srcMipLevel;
	uint32_t destSubRes = getNumMips()  * destArrayIndex + destMipLevel;

	D3D11_BOX bx;
	auto elementSize = src->getFormat()->getSize();
	bx.left = srcOffsetX * elementSize; 
	bx.right = (srcOffsetX + srcWidth) * elementSize;
	bx.top = 0;
	bx.bottom = 1;
	bx.front = 0;
	bx.back = 1;
	ctx->CopySubresourceRegion(destRes, destSubRes, destOffsetX , destOffsetY, destOffsetZ, srcRes, srcSubRes, &bx);
}


LLGL_NAMESPACE_END2;