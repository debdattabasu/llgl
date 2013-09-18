#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

Direct3D11Texture2DStream::Direct3D11Texture2DStream(ContextPtr parentContext, uint32_t width, uint32_t height, FormatPtr format):
	Texture2DStream(parentContext, width, height, format), _tex2d(0)
{

}

Direct3D11Texture2DStream::~Direct3D11Texture2DStream()
{
	SAFE_RELEASE(_tex2d);
}

void Direct3D11Texture2DStream::initializeImpl()
{
	auto caps = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getCapabilities();
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmtTypeless = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTypeless();
	HRESULT hr = S_OK;
	D3D11_TEXTURE2D_DESC td; 
	ZeroMemory(&td, sizeof(td));
	td.Width = getWidth();
	td.Height = getHeight();
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = dxgiFmtTypeless;
	td.SampleDesc.Count = 1;
	td.Usage = D3D11_USAGE_STAGING;
	td.CPUAccessFlags = D3D11_CPU_ACCESS_READ|D3D11_CPU_ACCESS_WRITE;
	hr = dev->CreateTexture2D(&td, NULL, &_tex2d);
	CHECK_HRESULT(hr);
}

Texture2DStream::MapDesc Direct3D11Texture2DStream::mapImpl() 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	HRESULT hr = S_OK;
	D3D11_MAPPED_SUBRESOURCE rs;
	rs.RowPitch = 0;
	rs.pData = 0;
	hr = ctx->Map(_tex2d, 0, D3D11_MAP_READ_WRITE, 0, &rs);
	CHECK_HRESULT(hr);
	Texture2DStream::MapDesc ret = {(char*)rs.pData, rs.RowPitch};
	return ret;
}

void Direct3D11Texture2DStream::unmapImpl() 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ctx->Unmap(_tex2d, 0);
}

void Direct3D11Texture2DStream::copyFromImpl(Texture2DPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY,
	uint32_t srcWidth, uint32_t srcHeight, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
	uint32_t destOffsetX, uint32_t destOffsetY) 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Texture2D>(src)->_tex2d; 
	ID3D11Resource* destRes = _tex2d;
	uint32_t srcSubRes = src->getNumMips() * srcArrayIndex + srcMipLevel;
	uint32_t destSubRes = 0;
	D3D11_BOX bx;
	bx.left = srcOffsetX; 
	bx.right = srcOffsetX + srcWidth;
	bx.top = srcOffsetY;
	bx.bottom = srcOffsetY + srcHeight;
	bx.front = 0;
	bx.back = 1;
	ctx->CopySubresourceRegion(destRes, destSubRes, destOffsetX , destOffsetY, 0, srcRes, srcSubRes, &bx);
}

void Direct3D11Texture2DStream::copyFromImpl(Texture2DStreamPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcWidth, uint32_t srcHeight, 
		uint32_t destOffsetX, uint32_t destOffsetY)
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Texture2DStream>(src)->_tex2d; 
	ID3D11Resource* destRes = _tex2d;
	uint32_t srcSubRes = 0;
	uint32_t destSubRes = 0;
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