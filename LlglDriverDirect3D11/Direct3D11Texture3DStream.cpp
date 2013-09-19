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

void Direct3D11Texture3DStream::readFromImpl(Texture3DSlicePtr src, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ)
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Texture3D>(src->getParentTexture())->_tex3d; 
	ID3D11Resource* destRes = _tex3d; 
	uint32_t srcSubRes = src->getMipLevel();
	uint32_t destSubRes = 0;
	D3D11_BOX bx;
	bx.left = offsetX; 
	bx.right = offsetX + getWidth();
	bx.top = offsetY;
	bx.bottom = offsetY + getHeight();
	bx.front = offsetZ;
	bx.back = offsetZ + getDepth();
	ctx->CopySubresourceRegion(destRes, destSubRes, 0, 0, 0, srcRes, srcSubRes, &bx);
}

void Direct3D11Texture3DStream::writeToImpl(Texture3DSlicePtr dest, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ)
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = _tex3d; 
	ID3D11Resource* destRes = std::dynamic_pointer_cast<Direct3D11Texture3D>(dest->getParentTexture())->_tex3d; 
	uint32_t srcSubRes = 0;
	uint32_t destSubRes = dest->getMipLevel();
	D3D11_BOX bx;
	bx.left = 0; 
	bx.right = getWidth();
	bx.top = 0;
	bx.bottom = getHeight();
	bx.front = 0;
	bx.back = getDepth();
	ctx->CopySubresourceRegion(destRes, destSubRes, offsetX, offsetY, offsetZ, srcRes, srcSubRes, &bx);
}

LLGL_NAMESPACE_END2;