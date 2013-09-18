#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

Direct3D11Texture1DStream::Direct3D11Texture1DStream(ContextPtr parentContext, uint32_t width, FormatPtr format):
	Texture1DStream(parentContext, width, format), _tex1d(0)
{

}

Direct3D11Texture1DStream::~Direct3D11Texture1DStream()
{
	SAFE_RELEASE(_tex1d);
}

void Direct3D11Texture1DStream::initializeImpl()
{
	auto caps = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getCapabilities();
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmtTypeless = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTypeless();
	HRESULT hr = S_OK;
	D3D11_TEXTURE1D_DESC td; 
	ZeroMemory(&td, sizeof(td));
	td.Width = getWidth();
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = dxgiFmtTypeless;
	td.Usage = D3D11_USAGE_STAGING;
	td.CPUAccessFlags = D3D11_CPU_ACCESS_READ|D3D11_CPU_ACCESS_WRITE;
	hr = dev->CreateTexture1D(&td, NULL, &_tex1d);
	CHECK_HRESULT(hr);
}

Texture1DStream::MapDesc Direct3D11Texture1DStream::mapImpl() 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	HRESULT hr = S_OK;
	D3D11_MAPPED_SUBRESOURCE rs;
	rs.RowPitch = 0;
	rs.pData = 0;
	hr = ctx->Map(_tex1d, 0, D3D11_MAP_READ_WRITE, 0, &rs);
	CHECK_HRESULT(hr);
	Texture1DStream::MapDesc ret = {(char*) rs.pData};
	return ret;
}

void Direct3D11Texture1DStream::unmapImpl() 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ctx->Unmap(_tex1d, 0);
}

void Direct3D11Texture1DStream::copyFromImpl(Texture1DPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t srcMipLevel, uint32_t srcArrayIndex, 
	uint32_t destOffset)
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Texture1D>(src)->_tex1d; 
	ID3D11Resource* destRes = _tex1d;
	uint32_t srcSubRes = src->getNumMips() * srcArrayIndex + srcMipLevel;
	uint32_t destSubRes = 0;
	D3D11_BOX bx;
	bx.left = srcOffset; 
	bx.right = srcOffset + srcWidth;
	bx.top = 0;
	bx.bottom = 1;
	bx.front = 0;
	bx.back = 1;
	ctx->CopySubresourceRegion(destRes, destSubRes, destOffset , 0, 0, srcRes, srcSubRes, &bx);
}

void Direct3D11Texture1DStream::copyFromImpl(Texture1DStreamPtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset)
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Texture1DStream>(src)->_tex1d; 
	ID3D11Resource* destRes = _tex1d;
	uint32_t srcSubRes = 0;
	uint32_t destSubRes = 0;
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