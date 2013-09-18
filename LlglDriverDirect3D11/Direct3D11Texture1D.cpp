#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

Direct3D11Texture1D::Direct3D11Texture1D(ContextPtr parentContext, uint32_t width,  uint32_t numMips, uint32_t arraySize, FormatPtr format):
	Texture1D(parentContext, width, numMips, arraySize, format), _tex1d(0), _srv(0), _uavs(0)
{

}

Direct3D11Texture1D::~Direct3D11Texture1D()
{
	SAFE_RELEASE(_tex1d);
	SAFE_RELEASE(_srv);
	for(auto uav: _uavs)
	{
		SAFE_RELEASE(uav);
	}
}

void Direct3D11Texture1D::initializeImpl()
{
	_uavs.resize(getNumMips());
	for(auto i : _uavs)
	{
		i = 0;
	}
	auto caps = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getCapabilities();
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmtTypeless = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTypeless();
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTyped();
	HRESULT hr = S_OK;
	D3D11_TEXTURE1D_DESC td; 
	ZeroMemory(&td, sizeof(td));
	td.Width = getWidth();;
	td.MipLevels = getNumMips();
	td.ArraySize = getArraySize();
	td.Format = dxgiFmtTypeless;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	if(caps->numUnorderedAccessSlots())
		td.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
	hr =dev->CreateTexture1D(&td, NULL, &_tex1d);
	CHECK_HRESULT(hr);
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd ;
	ZeroMemory(&srvd, sizeof(srvd));
	srvd.Format = dxgiFmtTyped;
	if(getArraySize() ==1)
	{
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;
		srvd.Texture1D.MostDetailedMip = 0;
		srvd.Texture1D.MipLevels = -1;
	}
	else
	{
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1DARRAY ;
		srvd.Texture1DArray.MostDetailedMip = 0;
		srvd.Texture1DArray.MipLevels = -1;
		srvd.Texture1DArray.ArraySize = getArraySize();
		srvd.Texture1DArray.FirstArraySlice = 0;
	}
	hr = dev->CreateShaderResourceView(_tex1d, &srvd, &_srv);
	CHECK_HRESULT(hr);
	if(caps->numUnorderedAccessSlots())
	{
		for(uint32_t mipLevel = 0; mipLevel < getNumMips(); mipLevel ++)
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
			ZeroMemory(&uavd, sizeof(uavd));
			uavd.Format =dxgiFmtTyped;
			if(getArraySize() ==1)
			{
				uavd.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE1D;
				uavd.Texture1D.MipSlice = mipLevel;
			}
			else
			{
				uavd.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE1DARRAY;
				uavd.Texture1DArray.MipSlice = mipLevel;
				uavd.Texture1DArray.ArraySize = getArraySize();
				uavd.Texture1DArray.FirstArraySlice = 0;
			}
			hr = dev->CreateUnorderedAccessView(_tex1d, &uavd, &_uavs[mipLevel]);
			CHECK_HRESULT(hr);
		}
	}
}

void Direct3D11Texture1D::copyFromImpl(Texture1DPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
		uint32_t destOffset, uint32_t destMipLevel, uint32_t destArrayIndex) 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Texture1D>(src)->_tex1d; 
	ID3D11Resource* destRes = _tex1d;
	uint32_t srcSubRes = src->getNumMips() * srcArrayIndex + srcMipLevel;
	uint32_t destSubRes = getNumMips()  * destArrayIndex + destMipLevel;
	D3D11_BOX bx;
	bx.left = srcOffset; 
	bx.right = srcOffset + srcWidth;
	bx.top = 0;
	bx.bottom = 1;
	bx.front = 0;
	bx.back = 1;
	ctx->CopySubresourceRegion(destRes, destSubRes, destOffset , 0, 0, srcRes, srcSubRes, &bx);
}

void Direct3D11Texture1D::copyFromImpl(Texture1DStreamPtr src, uint32_t srcOffset, uint32_t srcWidth,
		uint32_t destOffset, uint32_t destMipLevel, uint32_t destArrayIndex) 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Texture1DStream>(src)->_tex1d; 
	ID3D11Resource* destRes = _tex1d;
	uint32_t srcSubRes = 0;
	uint32_t destSubRes = getNumMips()  * destArrayIndex + destMipLevel;
	D3D11_BOX bx;
	bx.left = srcOffset; 
	bx.right = srcOffset + srcWidth;
	bx.top = 0;
	bx.bottom = 1;
	bx.front = 0;
	bx.back = 1;
	ctx->CopySubresourceRegion(destRes, destSubRes, destOffset , 0, 0, srcRes, srcSubRes, &bx);
}

LLGL_NAMESPACE_END2;