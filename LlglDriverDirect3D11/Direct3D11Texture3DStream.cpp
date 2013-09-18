#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

Direct3D11Texture3DStream::Direct3D11Texture3DStream(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t depth, FormatPtr format):
	Texture3DStream(parentContext, width, height, depth, format), _tex3d(0)
{

}

Direct3D11Texture3DStream::~Direct3D11Texture3DStream()
{
	SAFE_RELEASE(_tex3d);
}

void Direct3D11Texture3DStream::initializeImpl()
{
	auto caps = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getCapabilities();
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmtTypeless = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTypeless();
	HRESULT hr = S_OK;
	D3D11_TEXTURE3D_DESC td; 
	ZeroMemory(&td, sizeof(td));
	td.Width = getWidth();
	td.Height = getHeight();
	td.Depth = getDepth();
	td.MipLevels = 1;
	td.Format = dxgiFmtTypeless;
	td.Usage = D3D11_USAGE_STAGING ;
	td.CPUAccessFlags = D3D11_CPU_ACCESS_READ|D3D11_CPU_ACCESS_WRITE;
	hr = dev->CreateTexture3D(&td, NULL, &_tex3d);
	CHECK_HRESULT(hr);
}

Texture3DStream::MapDesc Direct3D11Texture3DStream::mapImpl() 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	HRESULT hr = S_OK;
	D3D11_MAPPED_SUBRESOURCE rs;
	rs.RowPitch = 0;
	rs.DepthPitch = 0;
	rs.pData = 0;
	hr = ctx->Map(_tex3d, 0, D3D11_MAP_READ_WRITE, 0, &rs);
	CHECK_HRESULT(hr);
	Texture3DStream::MapDesc ret = {(char*)rs.pData, rs.RowPitch, rs.DepthPitch};
	return ret;
}

void Direct3D11Texture3DStream::unmapImpl() 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ctx->Unmap(_tex3d, 0);
}

void Direct3D11Texture3DStream::copyFromImpl(Texture3DPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t srcMipLevel, 
		uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ) 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Texture3D>(src)->_tex3d; 
	ID3D11Resource* destRes = _tex3d;
	uint32_t srcSubRes = srcMipLevel;
	uint32_t destSubRes = 0;
	D3D11_BOX bx;
	bx.left = srcOffsetX ; 
	bx.right = srcOffsetX + srcWidth;
	bx.top = srcOffsetY;
	bx.bottom = srcOffsetY + srcHeight;
	bx.front = srcOffsetZ;
	bx.back = srcOffsetZ + srcDepth;
	ctx->CopySubresourceRegion(destRes, destSubRes, destOffsetX , destOffsetY, destOffsetZ, srcRes, srcSubRes, &bx);
}

void Direct3D11Texture3DStream::copyFromImpl(Texture3DStreamPtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ) 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Texture3DStream>(src)->_tex3d; 
	ID3D11Resource* destRes = _tex3d;
	uint32_t srcSubRes = 0;
	uint32_t destSubRes = 0;
	D3D11_BOX bx;
	bx.left = srcOffsetX ; 
	bx.right = srcOffsetX + srcWidth;
	bx.top = srcOffsetY;
	bx.bottom = srcOffsetY + srcHeight;
	bx.front = srcOffsetZ;
	bx.back = srcOffsetZ + srcDepth;
	ctx->CopySubresourceRegion(destRes, destSubRes, destOffsetX , destOffsetY, destOffsetZ, srcRes, srcSubRes, &bx);
}

LLGL_NAMESPACE_END2;