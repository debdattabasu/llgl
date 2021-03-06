#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);


Direct3D11BufferUnorderedAccessView::Direct3D11BufferUnorderedAccessView(BufferPtr parentBuffer) :
	BufferUnorderedAccessView(parentBuffer), _uav(0)
{

}

Direct3D11BufferUnorderedAccessView::~Direct3D11BufferUnorderedAccessView()
{
	SAFE_RELEASE(_uav);
}

ID3D11UnorderedAccessView* Direct3D11BufferUnorderedAccessView::getDirect3D11UnorderedAccessView() const
{
	return _uav;
}

void Direct3D11BufferUnorderedAccessView::initializeStructured()
{
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getDirect3D11Device();
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getParentResource()->getFormat())->getDxgiFormatTyped();
	auto numElements = getParentResource()->getWidth();
	auto buf = std::dynamic_pointer_cast<Direct3D11Buffer>(getParentResource())->getDirect3D11Buffer();
	
	HRESULT hr;
	D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
	ZeroMemory(&uavd, sizeof(uavd));
	uavd.Format = dxgiFmtTyped;
	uavd.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	uavd.Buffer.FirstElement = 0;
	uavd.Buffer.NumElements =  numElements;
	hr = dev->CreateUnorderedAccessView(buf, &uavd, &_uav);
	CHECK_HRESULT(hr);
}

void Direct3D11BufferUnorderedAccessView::initializeFormatted()
{
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getDirect3D11Device();
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getParentResource()->getFormat())->getDxgiFormatTyped();
	auto numElements = getParentResource()->getWidth();
	auto buf = std::dynamic_pointer_cast<Direct3D11Buffer>(getParentResource())->getDirect3D11Buffer();
	
	HRESULT hr;
	D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
	ZeroMemory(&uavd, sizeof(uavd));
	uavd.Format = dxgiFmtTyped;
	uavd.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	uavd.Buffer.FirstElement = 0;
	uavd.Buffer.NumElements =  numElements;
	hr = dev->CreateUnorderedAccessView(buf, &uavd, &_uav);
	CHECK_HRESULT(hr);
}

void Direct3D11BufferUnorderedAccessView::initializeDriver()
{
	if (getParentResource()->getFormat()->getUsage() == FormatUsage::StructuredBuffer) initializeStructured();
	else initializeFormatted();
}

LLGL_NAMESPACE_END2;