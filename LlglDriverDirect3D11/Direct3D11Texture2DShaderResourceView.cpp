#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);


Direct3D11Texture2DShaderResourceView::Direct3D11Texture2DShaderResourceView(Texture2DPtr parentTexture) :
	Texture2DShaderResourceView(parentTexture), _srv(0)
{

}

Direct3D11Texture2DShaderResourceView::~Direct3D11Texture2DShaderResourceView()
{
	SAFE_RELEASE(_srv);
}

void Direct3D11Texture2DShaderResourceView::initializeDriver()
{
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getParentResource()->getFormat())->getDxgiFormatTyped();
	auto tex2d = std::dynamic_pointer_cast<Direct3D11Texture2D>(getParentResource())->_tex2d;

	HRESULT hr = S_OK;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&srvd, sizeof(srvd));
	srvd.Format = dxgiFmtTyped;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MostDetailedMip = 0;
	srvd.Texture2D.MipLevels = -1;

	hr = dev->CreateShaderResourceView(tex2d, &srvd, &_srv);
	CHECK_HRESULT(hr);
}

LLGL_NAMESPACE_END2;