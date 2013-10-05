#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);


Direct3D11Texture3DShaderResourceView::Direct3D11Texture3DShaderResourceView(Texture3DPtr parentTexture) :
	Texture3DShaderResourceView(parentTexture), _srv(0)
{

}

Direct3D11Texture3DShaderResourceView::~Direct3D11Texture3DShaderResourceView()
{
	SAFE_RELEASE(_srv);
}

void Direct3D11Texture3DShaderResourceView::initializeDriver()
{
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getParentResource()->getFormat())->getDxgiFormatTyped();
	auto tex3d = std::dynamic_pointer_cast<Direct3D11Texture3D>(getParentResource())->_tex3d;

	HRESULT hr = S_OK;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd ;
	ZeroMemory(&srvd, sizeof(srvd));
	srvd.Format = dxgiFmtTyped;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
	srvd.Texture3D.MostDetailedMip = 0;
	srvd.Texture3D.MipLevels = -1;
	hr = dev->CreateShaderResourceView(tex3d, &srvd, &_srv);
	CHECK_HRESULT(hr);
}

LLGL_NAMESPACE_END2;