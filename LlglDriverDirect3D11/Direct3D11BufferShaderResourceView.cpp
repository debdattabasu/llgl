#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);


Direct3D11BufferShaderResourceView::Direct3D11BufferShaderResourceView(BufferPtr parentBuffer) :
	BufferShaderResourceView(parentBuffer), _srv(0)
{

}

Direct3D11BufferShaderResourceView::~Direct3D11BufferShaderResourceView()
{
	SAFE_RELEASE(_srv);
}

ID3D11ShaderResourceView* Direct3D11BufferShaderResourceView::getDirect3D11ShaderResourceView() const
{
	return _srv;
}

void Direct3D11BufferShaderResourceView::initializeStructured()
{
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getDirect3D11Device();
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getParentResource()->getFormat())->getDxgiFormatTyped();
	auto numElements = getParentResource()->getWidth();
	auto elementSize = getParentResource()->getFormat()->getSize();
	auto buf = std::dynamic_pointer_cast<Direct3D11Buffer>(getParentResource())->getDirect3D11Buffer();

	HRESULT hr;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&srvd, sizeof(srvd));
	srvd.Format = dxgiFmtTyped;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	srvd.Buffer.ElementOffset = 0;
	srvd.Buffer.ElementWidth = elementSize;
	srvd.Buffer.FirstElement = 0;
	srvd.Buffer.NumElements = numElements;
	hr = dev->CreateShaderResourceView(buf, &srvd, &_srv);
	CHECK_HRESULT(hr);

}

void Direct3D11BufferShaderResourceView::initializeFormatted()
{
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getDirect3D11Device();
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getParentResource()->getFormat())->getDxgiFormatTyped();
	auto elementSize = getParentResource()->getFormat()->getSize();
	auto numElements = getParentResource()->getWidth();
	auto buf = std::dynamic_pointer_cast<Direct3D11Buffer>(getParentResource())->getDirect3D11Buffer();
	
	HRESULT hr;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&srvd, sizeof(srvd));
	srvd.Format = dxgiFmtTyped;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	srvd.Buffer.FirstElement = 0;
	srvd.Buffer.ElementWidth = elementSize;
	srvd.Buffer.ElementOffset = 0;
	srvd.Buffer.NumElements = numElements;
	hr = dev->CreateShaderResourceView(buf, &srvd, &_srv);
	CHECK_HRESULT(hr);
}

void Direct3D11BufferShaderResourceView::initializeDriver()
{
	if (getParentResource()->getFormat()->getUsage() == FormatUsage::StructuredBuffer) initializeStructured();
	else initializeFormatted();
}

LLGL_NAMESPACE_END2;