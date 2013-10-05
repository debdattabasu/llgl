#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);


Direct3D11Texture2DDataAccessView::Direct3D11Texture2DDataAccessView(Texture2DPtr parentTexture, uint32_t offsetX, uint32_t offsetY, 
		uint32_t width, uint32_t height, uint32_t mipLevel, uint32_t arrayIndex) :
	Texture2DDataAccessView(parentTexture, offsetX, offsetY, width, height, mipLevel, arrayIndex), _tex2d(0)
{

}

Direct3D11Texture2DDataAccessView::~Direct3D11Texture2DDataAccessView()
{
	SAFE_RELEASE(_tex2d);
}

ID3D11Texture2D* Direct3D11Texture2DDataAccessView::getDirect3D11StagingTexture2D()
{
	if(!_tex2d)
	{
		auto caps = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getCapabilities();
		auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getDirect3D11Device();
		auto dxgiFmtTypeless = std::dynamic_pointer_cast<Direct3D11Format>(getParentResource()->getFormat())->getDxgiFormatTypeless();
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
	return _tex2d;

}

void Direct3D11Texture2DDataAccessView::initializeDriver()
{

}

void Direct3D11Texture2DDataAccessView::copyFromDriver(Texture2DDataAccessViewPtr src)
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getDirect3D11DeviceContext();
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Texture2D>(src->getParentResource())->getDirect3D11Texture2D();
	uint32_t srcSubRes = src->getMipLevel();
	uint32_t srcOffsetX = src->getOffsetX();
	uint32_t srcOffsetY = src->getOffsetY();
	uint32_t srcWidth = src->getWidth();
	uint32_t srcHeight = src->getHeight();
	ID3D11Resource* destRes = std::dynamic_pointer_cast<Direct3D11Texture2D>(getParentResource())->getDirect3D11Texture2D();
	uint32_t destOffsetX = getOffsetX();
	uint32_t destOffsetY = getOffsetY();
	uint32_t destSubRes = getMipLevel();

	D3D11_BOX bx;
	bx.left = srcOffsetX; 
	bx.right = srcOffsetX + srcWidth;
	bx.top = srcOffsetY;
	bx.bottom = srcOffsetY + srcHeight;
	bx.front = 0;
	bx.back = 1;
	ctx->CopySubresourceRegion(destRes, destSubRes, destOffsetX, destOffsetY, 0, srcRes, srcSubRes, &bx);

}

void Direct3D11Texture2DDataAccessView::getDataDriver(void* data)
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getDirect3D11DeviceContext();
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Texture2D>(getParentResource())->getDirect3D11Texture2D();
	uint32_t srcSubRes = getMipLevel();  
	ID3D11Resource* destRes = getDirect3D11StagingTexture2D();

	D3D11_BOX bx;
	bx.left = getOffsetX(); 
	bx.right = getOffsetX() + getWidth();
	bx.top = getOffsetY();
	bx.bottom = getOffsetY() + getHeight();
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

	char* pCharData = (char*) rs.pData;
	for(uint32_t i = 0; i < getHeight(); i++)
	{
		memcpy(data, pCharData, getWidth() * elementSize);
		pCharData += rs.RowPitch;
	}

	ctx->Unmap(destRes, 0);
}

void Direct3D11Texture2DDataAccessView::setDataDriver(void* data)
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getDirect3D11DeviceContext();
	ID3D11Resource* srcRes = getDirect3D11StagingTexture2D();
	
	HRESULT hr;
	D3D11_MAPPED_SUBRESOURCE rs;
	rs.RowPitch = 0;
	rs.pData = 0;
	hr = ctx->Map(srcRes, 0, D3D11_MAP_WRITE, 0, &rs);
	CHECK_HRESULT(hr);

	uint32_t elementSize = getParentResource()->getFormat()->getSize();

	char* pCharData = (char*) rs.pData;
	for(uint32_t i = 0; i < getHeight(); i++)
	{	
		memcpy(pCharData, data, getWidth() * elementSize);
		pCharData += rs.RowPitch;
	}

	ctx->Unmap(srcRes, 0);

	ID3D11Resource* destRes = std::dynamic_pointer_cast<Direct3D11Texture2D>(getParentResource())->getDirect3D11Texture2D();
	uint32_t destSubRes = getMipLevel();

	D3D11_BOX bx;
	bx.left = 0; 
	bx.right = getWidth();
	bx.top = 0;
	bx.bottom = getHeight();
	bx.front = 0;
	bx.back = 1;
	ctx->CopySubresourceRegion(destRes, destSubRes, getOffsetX(), getOffsetY(), 0, srcRes, 0, &bx);

}

LLGL_NAMESPACE_END2;