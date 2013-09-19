#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

Direct3D11Texture1D::Direct3D11Texture1D(ContextPtr parentContext, uint32_t width,  uint32_t numMips, FormatPtr format):
	Texture1D(parentContext, width, numMips, format), _tex1d(0), _srv(0)
{

}

Direct3D11Texture1D::~Direct3D11Texture1D()
{
	SAFE_RELEASE(_tex1d);
	SAFE_RELEASE(_srv);
}

void Direct3D11Texture1D::initializeImpl()
{
	auto caps = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getCapabilities();
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmtTypeless = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTypeless();
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTyped();
	HRESULT hr = S_OK;
	D3D11_TEXTURE1D_DESC td; 
	ZeroMemory(&td, sizeof(td));
	td.Width = getWidth();;
	td.MipLevels = getNumMips();
	td.ArraySize = 1;
	td.Format = dxgiFmtTypeless;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	if(caps->numUnorderedAccessSlots())
		td.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
	hr =dev->CreateTexture1D(&td, NULL, &_tex1d);
	CHECK_HRESULT(hr);
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd ;
	ZeroMemory(&srvd, sizeof(srvd));
	srvd.Format = dxgiFmtTyped;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;
	srvd.Texture1D.MostDetailedMip = 0;
	srvd.Texture1D.MipLevels = -1;
	hr = dev->CreateShaderResourceView(_tex1d, &srvd, &_srv);
	CHECK_HRESULT(hr);
}

Texture1DSlicePtr Direct3D11Texture1D::getSliceImpl(uint32_t mipLevel)
{
	return Texture1DSlicePtr(new Direct3D11Texture1DSlice(shared_from_this(), mipLevel));
}

LLGL_NAMESPACE_END2;