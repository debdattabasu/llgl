#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

Direct3D11Texture3D::Direct3D11Texture3D(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t depth, uint32_t numMips, FormatPtr format):
	Texture3D(parentContext, width, height, depth, numMips, format), _tex3d(0), _srv(0)
{

}

Direct3D11Texture3D::~Direct3D11Texture3D()
{
	SAFE_RELEASE(_tex3d);
	SAFE_RELEASE(_srv);
}

void Direct3D11Texture3D::initializeDriver()
{
	auto caps = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getCapabilities();
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmtTypeless = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTypeless();
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTyped();
	HRESULT hr = S_OK;
	D3D11_TEXTURE3D_DESC td; 
	ZeroMemory(&td, sizeof(td));
	td.Width = getWidth();
	td.Height = getHeight();
	td.Depth = getDepth();
	td.MipLevels = getNumMips();
	td.Format = dxgiFmtTypeless;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	if(caps->numUnorderedAccessSlots()) td.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
	hr = dev->CreateTexture3D(&td, NULL, &_tex3d);
	CHECK_HRESULT(hr);
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd ;
	ZeroMemory(&srvd, sizeof(srvd));
	srvd.Format = dxgiFmtTyped;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
	srvd.Texture3D.MostDetailedMip = 0;
	srvd.Texture3D.MipLevels = -1;
	hr = dev->CreateShaderResourceView(_tex3d, &srvd, &_srv);
	CHECK_HRESULT(hr);
}

Texture3DSlicePtr Direct3D11Texture3D::getSliceDriver(uint32_t mipLevel)
{
	return Texture3DSlicePtr(new Direct3D11Texture3DSlice(shared_from_this(), mipLevel));
}

LLGL_NAMESPACE_END2;