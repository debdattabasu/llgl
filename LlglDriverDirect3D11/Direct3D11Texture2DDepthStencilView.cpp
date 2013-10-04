#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);


Direct3D11Texture2DDepthStencilView::Direct3D11Texture2DDepthStencilView(Texture2DPtr parentTexture, uint32_t mipLevel, uint32_t arrayIndex) :
	Texture2DDepthStencilView(parentTexture, mipLevel, arrayIndex), _dsv(0)
{

}

Direct3D11Texture2DDepthStencilView::~Direct3D11Texture2DDepthStencilView()
{
	SAFE_RELEASE(_dsv);
}

void Direct3D11Texture2DDepthStencilView::initializeDriver()
{
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmtDepthTyped = std::dynamic_pointer_cast<Direct3D11Format>(getParentResource()->getFormat())->getDxgiFormatDepthTyped();
	auto tex2d = std::dynamic_pointer_cast<Direct3D11Texture2D>(getParentResource())->_tex2d;

	HRESULT hr = S_OK;
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = dxgiFmtDepthTyped;
	dsvd.ViewDimension= D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Texture2D.MipSlice = getMipLevel();
	hr = dev->CreateDepthStencilView(tex2d, &dsvd, &_dsv);
	CHECK_HRESULT(hr);
}

LLGL_NAMESPACE_END2;