#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);


Direct3D11Texture1DShaderResourceView::Direct3D11Texture1DShaderResourceView(Texture1DPtr parentTexture) :
	Texture1DShaderResourceView(parentTexture), _srv(0)
{

}

Direct3D11Texture1DShaderResourceView::~Direct3D11Texture1DShaderResourceView()
{
	SAFE_RELEASE(_srv);
}

void Direct3D11Texture1DShaderResourceView::initializeDriver()
{
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getParentResource()->getFormat())->getDxgiFormatTyped();
	auto tex1d = std::dynamic_pointer_cast<Direct3D11Texture1D>(getParentResource())->_tex1d;

	HRESULT hr = S_OK;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd ;
	ZeroMemory(&srvd, sizeof(srvd));
	srvd.Format = dxgiFmtTyped;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;
	srvd.Texture1D.MostDetailedMip = 0;
	srvd.Texture1D.MipLevels = -1;
	hr = dev->CreateShaderResourceView(tex1d, &srvd, &_srv);
	CHECK_HRESULT(hr);
}

LLGL_NAMESPACE_END2;