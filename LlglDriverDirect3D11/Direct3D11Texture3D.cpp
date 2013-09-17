#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

Direct3D11Texture3D::Direct3D11Texture3D(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t depth, uint32_t numMips, FormatPtr format):
	Texture3D(parentContext, width, height, depth, numMips, format), _tex3d(0), _srv(0), _uavs(0)
{

}

Direct3D11Texture3D::~Direct3D11Texture3D()
{
	SAFE_RELEASE(_tex3d);
	SAFE_RELEASE(_srv);
	for(auto i: _uavs)
	{
		SAFE_RELEASE(i);
	}
}

void Direct3D11Texture3D::initializeImpl()
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

	D3D11_TEXTURE3D_DESC td; 
	ZeroMemory(&td, sizeof(td));
	td.Width = getWidth();
	td.Height = getHeight();
	td.Depth = getDepth();
	td.MipLevels = getNumMips();
	td.Format = dxgiFmtTypeless;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	if(caps->numUnorderedAccessSlots()) td.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
	hr = dev->CreateTexture3D(&td, NULL, &_tex3d);
	CHECK_HRESULT(hr);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvd ;
	ZeroMemory(&srvd, sizeof(srvd));
	srvd.Format = dxgiFmtTyped;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
	srvd.Texture3D.MostDetailedMip = 0;
	srvd.Texture3D.MipLevels = -1;
	hr = dev->CreateShaderResourceView(_tex3d, &srvd, &_srv);
	CHECK_HRESULT(hr);

	for(uint32_t mipLevel = 0; mipLevel < getNumMips(); mipLevel ++)
	{
		D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
		uavd.Format = dxgiFmtTyped;
		uavd.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE3D;
		uavd.Texture3D.MipSlice = mipLevel;
		uavd.Texture3D.FirstWSlice = 0;
		uavd.Texture3D.WSize = getDepth(mipLevel);
		hr = dev->CreateUnorderedAccessView(_tex3d, &uavd, &_uavs[mipLevel]);
		CHECK_HRESULT(hr);
	}
}

void Direct3D11Texture3D::copyFromImpl(Texture3DPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t srcMipLevel, 
		uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ, uint32_t destMipLevel) 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Texture3D>(src)->_tex3d; 
	ID3D11Resource* destRes = _tex3d;
	uint32_t srcSubRes = srcMipLevel;
	uint32_t destSubRes = destMipLevel;

	D3D11_BOX bx;
	bx.left = srcOffsetX ; 
	bx.right = srcOffsetX + srcWidth;
	bx.top = srcOffsetY;
	bx.bottom = srcOffsetY + srcHeight;
	bx.front = srcOffsetZ;
	bx.back = srcOffsetZ + srcDepth;
	ctx->CopySubresourceRegion(destRes, destSubRes, destOffsetX , destOffsetY, destOffsetZ, srcRes, srcSubRes, &bx);
}

void Direct3D11Texture3D::readImpl(Texture3DStreamPtr stream, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ, uint32_t mipLevel) 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = _tex3d;
	ID3D11Resource* destRes = std::dynamic_pointer_cast<Direct3D11Texture3DStream>(stream)->_tex3d; 
	uint32_t srcSubRes = mipLevel;
	D3D11_BOX bx;
	bx.left = offsetX; 
	bx.right = offsetX + stream->getWidth();
	bx.top = offsetY;
	bx.bottom = offsetY + stream->getHeight();
	bx.front = offsetZ;
	bx.back = offsetZ + stream->getDepth();
	ctx->CopySubresourceRegion(destRes, 0, 0, 0, 0, srcRes, srcSubRes, &bx);
}

void Direct3D11Texture3D::writeImpl(Texture3DStreamPtr stream, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ, uint32_t mipLevel) 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Texture3DStream>(stream)->_tex3d; 
	ID3D11Resource* destRes = _tex3d;
	uint32_t destSubRes = mipLevel;
	D3D11_BOX bx;
	bx.left = 0; 
	bx.right = stream->getWidth();
	bx.top = 0;
	bx.bottom = stream->getHeight();
	bx.front = 0;
	bx.back = stream->getDepth();
	ctx->CopySubresourceRegion(destRes, destSubRes, offsetX, offsetY, offsetZ, srcRes, 0, &bx);
}

LLGL_NAMESPACE_END2;