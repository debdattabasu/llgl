#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);


Direct3D11Texture1DDataAccessView::Direct3D11Texture1DDataAccessView(Texture1DPtr parentTexture, uint32_t offset, uint32_t width, 
	uint32_t mipLevel, uint32_t arrayIndex) :
	Texture1DDataAccessView(parentTexture, offset, width, mipLevel, arrayIndex), _tex1d(0)
{

}

Direct3D11Texture1DDataAccessView::~Direct3D11Texture1DDataAccessView()
{
	SAFE_RELEASE(_tex1d);
}

ID3D11Texture1D* Direct3D11Texture1DDataAccessView::getDirect3D11StagingTexture1D()
{
	if(!_tex1d)
	{
		auto caps = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getCapabilities();
		auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
		auto dxgiFmtTypeless = std::dynamic_pointer_cast<Direct3D11Format>(getParentResource()->getFormat())->getDxgiFormatTypeless();
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
	return _tex1d;

}

void Direct3D11Texture1DDataAccessView::initializeDriver()
{

}

void Direct3D11Texture1DDataAccessView::copyFromDriver(Texture1DDataAccessViewPtr src)
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Texture1D>(src->getParentResource())->_tex1d;
	uint32_t srcSubRes = src->getMipLevel();
	uint32_t srcOffset = src->getOffset();
	uint32_t srcWidth = src->getWidth();
	ID3D11Resource* destRes = std::dynamic_pointer_cast<Direct3D11Texture1D>(getParentResource())->_tex1d;
	uint32_t destOffset = getOffset();
	uint32_t destSubRes = getMipLevel();

	D3D11_BOX bx;
	bx.left = srcOffset; 
	bx.right = srcOffset + srcWidth;
	bx.top = 0;
	bx.bottom = 1;
	bx.front = 0;
	bx.back = 1;
	ctx->CopySubresourceRegion(destRes, destSubRes, destOffset, 0, 0, srcRes, srcSubRes, &bx);

}

void Direct3D11Texture1DDataAccessView::getDataDriver(void* data)
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Texture1D>(getParentResource())->_tex1d;
	uint32_t srcSubRes = getMipLevel();  
	ID3D11Resource* destRes = getDirect3D11StagingTexture1D();

	D3D11_BOX bx;
	bx.left = getOffset(); 
	bx.right = getOffset() + getWidth();
	bx.top = 0;
	bx.bottom = 1;
	bx.front = 0;
	bx.back = 1;
	ctx->CopySubresourceRegion(destRes, 0, 0, 0, 0, srcRes, srcSubRes, &bx);

	HRESULT hr;
	D3D11_MAPPED_SUBRESOURCE rs;
	rs.RowPitch = 0;
	rs.pData = 0;
	hr = ctx->Map(destRes, 0, D3D11_MAP_WRITE, 0, &rs);
	CHECK_HRESULT(hr);

	uint32_t elementSize = getParentResource()->getFormat()->getSize();
	memcpy(data, rs.pData, getWidth() * elementSize);

	ctx->Unmap(destRes, 0);
}

void Direct3D11Texture1DDataAccessView::setDataDriver(void* data)
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = getDirect3D11StagingTexture1D();
	

	HRESULT hr;
	D3D11_MAPPED_SUBRESOURCE rs;
	rs.RowPitch = 0;
	rs.pData = 0;
	hr = ctx->Map(srcRes, 0, D3D11_MAP_WRITE, 0, &rs);
	CHECK_HRESULT(hr);

	uint32_t elementSize = getParentResource()->getFormat()->getSize();
	memcpy(rs.pData, data, getWidth() * elementSize);

	ctx->Unmap(srcRes, 0);

	ID3D11Resource* destRes = std::dynamic_pointer_cast<Direct3D11Texture1D>(getParentResource())->_tex1d;
	uint32_t destSubRes = getMipLevel();

	D3D11_BOX bx;
	bx.left = 0; 
	bx.right = getWidth();
	bx.top = 0;
	bx.bottom = 1;
	bx.front = 0;
	bx.back = 1;
	ctx->CopySubresourceRegion(destRes, destSubRes, getOffset(), 0, 0, srcRes, 0, &bx);

}

LLGL_NAMESPACE_END2;