#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

Direct3D11Texture2D::Direct3D11Texture2D(ContextPtr parentContext, uint32_t width, uint32_t height,
	uint32_t numMips, uint32_t arraySize, FormatPtr format):
	Texture2D(parentContext, width, height, numMips, arraySize, format), _tex2d(0), _srv(0), _uavs(0), _rtvs(0), _dsvs(0)
{

}

Direct3D11Texture2D::~Direct3D11Texture2D()
{
	SAFE_RELEASE(_tex2d);
	SAFE_RELEASE(_srv);
	for(auto i: _uavs)
	{
		SAFE_RELEASE(i);
	}
	for(auto i: _dsvs)
	{
		SAFE_RELEASE(i);
	}
	for(auto i: _rtvs)
	{
		SAFE_RELEASE(i);
	}
}

void Direct3D11Texture2D::initializeImpl()
{
	_uavs.resize(getNumMips());
	for(auto i : _uavs)
	{
		i = 0;
	}
	_rtvs.resize(getNumMips() * getArraySize());
	for(auto i : _rtvs)
	{
		i = 0;
	}
	_dsvs.resize(getNumMips() * getArraySize());
	for(auto i : _dsvs)
	{
		i = 0;
	}
	auto caps = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getCapabilities();
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmtTypeless = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTypeless();
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTyped();
	auto dxgiFmtDepthTyped = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatDepthTyped();
	HRESULT hr = S_OK;
	D3D11_TEXTURE2D_DESC td; 
	ZeroMemory(&td, sizeof(td));
	td.Width = getWidth();
	td.Height = getHeight();
	td.MipLevels = getNumMips();
	td.ArraySize = getArraySize();
	td.Format = dxgiFmtTypeless;
	td.SampleDesc.Count = 1;
	td.Usage = D3D11_USAGE_DEFAULT;
	bool isDepth = getFormat()->getUsage() == FormatUsage::DepthTexture;
	td.BindFlags = (isDepth)? D3D11_BIND_DEPTH_STENCIL: D3D11_BIND_RENDER_TARGET;	
	td.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
	if(!isDepth && caps->numUnorderedAccessSlots())
		td.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
	hr = dev->CreateTexture2D(&td, NULL, &_tex2d);
	CHECK_HRESULT(hr);
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd ;
	ZeroMemory(&srvd, sizeof(srvd));
	srvd.Format = dxgiFmtTyped;
	if(getArraySize() ==1)
	{
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvd.Texture2D.MostDetailedMip = 0;
		srvd.Texture2D.MipLevels = -1;
	}
	else
	{
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
		srvd.Texture2DArray.MostDetailedMip = 0;
		srvd.Texture2DArray.MipLevels = -1;
		srvd.Texture2DArray.ArraySize = getArraySize();
		srvd.Texture2DArray.FirstArraySlice = 0;
	}
	hr = dev->CreateShaderResourceView(_tex2d, &srvd, &_srv);
	CHECK_HRESULT(hr);
	for(uint32_t mipLevel = 0; mipLevel < getNumMips(); mipLevel ++)
	{
		for(uint32_t arrayIndex = 0; arrayIndex < getArraySize(); arrayIndex ++)
		{
			uint32_t resId = getNumMips() * arrayIndex + mipLevel;
			if(isDepth)
			{
				D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
				ZeroMemory(&dsvd, sizeof(dsvd));
				dsvd.Format = dxgiFmtDepthTyped;
				if(getArraySize() ==1)
				{
					dsvd.ViewDimension= D3D11_DSV_DIMENSION_TEXTURE2D;
					dsvd.Texture2D.MipSlice = mipLevel;
				}
				else
				{
					dsvd.ViewDimension= D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
					dsvd.Texture2DArray.MipSlice = mipLevel;
					dsvd.Texture2DArray.ArraySize = 1;
					dsvd.Texture2DArray.FirstArraySlice = arrayIndex;
				}
				hr = dev->CreateDepthStencilView(_tex2d, &dsvd, &_dsvs[resId]);
				CHECK_HRESULT(hr);
			}
			else
			{
				D3D11_RENDER_TARGET_VIEW_DESC rtvd ;
				ZeroMemory(&rtvd, sizeof(rtvd));
				rtvd.Format = dxgiFmtTyped;
				if(getArraySize() ==1)
				{
					rtvd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
					rtvd.Texture2D.MipSlice = mipLevel;
				}
				else
				{
					rtvd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY ;
					rtvd.Texture2DArray.MipSlice = mipLevel;
					rtvd.Texture2DArray.ArraySize = 1;
					rtvd.Texture2DArray.FirstArraySlice = arrayIndex;
				}
				hr = dev->CreateRenderTargetView(_tex2d, &rtvd, &_rtvs[resId]);
				CHECK_HRESULT(hr);
			}
		}
		if(!isDepth)
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
			uavd.Format = dxgiFmtTyped;
			if(getArraySize() ==1)
			{
				uavd.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
				uavd.Texture2D.MipSlice = mipLevel;
			}
			else
			{
				uavd.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2DARRAY;
				uavd.Texture2DArray.MipSlice = mipLevel;
				uavd.Texture2DArray.ArraySize = getArraySize();
				uavd.Texture2DArray.FirstArraySlice = 0;
			}
			hr = dev->CreateUnorderedAccessView(_tex2d, &uavd, &_uavs[mipLevel]);
			CHECK_HRESULT(hr);
		}
	}
}

void Direct3D11Texture2D::copyFromImpl(Texture2DPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY,
	uint32_t srcWidth, uint32_t srcHeight, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
	uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destMipLevel, uint32_t destArrayIndex) 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Texture2D>(src)->_tex2d; 
	ID3D11Resource* destRes = _tex2d;
	uint32_t srcSubRes = src->getNumMips() * srcArrayIndex + srcMipLevel;
	uint32_t destSubRes = getNumMips()  * destArrayIndex + destMipLevel;
	D3D11_BOX bx;
	bx.left = srcOffsetX; 
	bx.right = srcOffsetX + srcWidth;
	bx.top = srcOffsetY;
	bx.bottom = srcOffsetY + srcHeight;
	bx.front = 0;
	bx.back = 1;
	ctx->CopySubresourceRegion(destRes, destSubRes, destOffsetX , destOffsetY, 0, srcRes, srcSubRes, &bx);
}

void Direct3D11Texture2D::copyFromImpl(Texture2DStreamPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcWidth, uint32_t srcHeight, 
		uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destMipLevel, uint32_t destArrayIndex)
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Texture2DStream>(src)->_tex2d; 
	ID3D11Resource* destRes = _tex2d;
	uint32_t srcSubRes = 0;
	uint32_t destSubRes = getNumMips()  * destArrayIndex + destMipLevel;
	D3D11_BOX bx;
	bx.left = srcOffsetX; 
	bx.right = srcOffsetX + srcWidth;
	bx.top = srcOffsetY;
	bx.bottom = srcOffsetY + srcHeight;
	bx.front = 0;
	bx.back = 1;
	ctx->CopySubresourceRegion(destRes, destSubRes, destOffsetX , destOffsetY, 0, srcRes, srcSubRes, &bx);
}

LLGL_NAMESPACE_END2;