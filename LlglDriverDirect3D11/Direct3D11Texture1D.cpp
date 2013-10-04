#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

Direct3D11Texture1D::Direct3D11Texture1D(ContextPtr parentContext, uint32_t width,  uint32_t numMips, FormatPtr format):
	Texture1D(parentContext, width, numMips, format), _tex1d(0)
{

}

Direct3D11Texture1D::~Direct3D11Texture1D()
{
	SAFE_RELEASE(_tex1d);
}

void Direct3D11Texture1D::initializeDriver()
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
}

Texture1DUnorderedAccessViewPtr Direct3D11Texture1D::getUnorderedAccessViewDriver(uint32_t mipLevel) 
{
	return Texture1DUnorderedAccessViewPtr(new Direct3D11Texture1DUnorderedAccessView(shared_from_this(), mipLevel));
}

Texture1DDataAccessViewPtr Direct3D11Texture1D::getDataAccessViewDriver(uint32_t offset, uint32_t width, uint32_t mipLevel, uint32_t arrayIndex) 
{
	return Texture1DDataAccessViewPtr(new Direct3D11Texture1DDataAccessView(shared_from_this(), offset, width, mipLevel, arrayIndex));
}

Texture1DShaderResourceViewPtr Direct3D11Texture1D::getShaderResourceViewDriver()
{
	return Texture1DShaderResourceViewPtr(new Direct3D11Texture1DShaderResourceView(shared_from_this()));
}

LLGL_NAMESPACE_END2;