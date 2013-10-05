#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);


Direct3D11Texture2DRenderTargetView::Direct3D11Texture2DRenderTargetView(Texture2DPtr parentTexture, uint32_t mipLevel, uint32_t arrayIndex) :
	Texture2DRenderTargetView(parentTexture, mipLevel, arrayIndex), _rtv(0)
{

}

Direct3D11Texture2DRenderTargetView::~Direct3D11Texture2DRenderTargetView()
{
	SAFE_RELEASE(_rtv);
}

ID3D11RenderTargetView* Direct3D11Texture2DRenderTargetView::getDirect3D11RenderTargetView() const
{
	return _rtv;
}

void Direct3D11Texture2DRenderTargetView::initializeDriver()
{
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getDirect3D11Device();
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getParentResource()->getFormat())->getDxgiFormatTyped();
	auto tex2d = std::dynamic_pointer_cast<Direct3D11Texture2D>(getParentResource())->getDirect3D11Texture2D();

	HRESULT hr = S_OK;
	D3D11_RENDER_TARGET_VIEW_DESC rtvd ;
		ZeroMemory(&rtvd, sizeof(rtvd));
	rtvd.Format = dxgiFmtTyped;

	uint32_t arraySize = getParentResource()->getArraySize();
	if(arraySize == 1)
	{
		rtvd.ViewDimension= D3D11_RTV_DIMENSION_TEXTURE2D;
		rtvd.Texture2D.MipSlice = getMipLevel();
	}
	else
	{
		rtvd.ViewDimension= D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
		rtvd.Texture2DArray.MipSlice = getMipLevel();
		rtvd.Texture2DArray.FirstArraySlice = 0;
		rtvd.Texture2DArray.ArraySize = arraySize;
	}

	hr = dev->CreateRenderTargetView(tex2d, &rtvd, &_rtv);
	CHECK_HRESULT(hr);
}

LLGL_NAMESPACE_END2;