#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

Direct3D11Buffer::Direct3D11Buffer(ContextPtr parentContext, uint32_t width, FormatPtr format):
	Buffer(parentContext, width, format), _buf(0)
{

}

Direct3D11Buffer::~Direct3D11Buffer()
{
	SAFE_RELEASE(_buf);
}

void Direct3D11Buffer::initializeRaw()
{
	auto caps = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getCapabilities();
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getDirect3D11Device();
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTyped();
	auto elementSize = getFormat()->getSize();
	auto numElements = getWidth();
	HRESULT hr = S_OK;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = numElements * elementSize;
	bd.Usage = D3D11_USAGE_DEFAULT;
	if(caps->supportsShaderResourceBuffer()) 
		bd.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
	if(caps->numUnorderedAccessSlots())
		bd.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
	bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS; 
	hr = dev->CreateBuffer(&bd, NULL, &_buf);
	CHECK_HRESULT(hr);
}

void Direct3D11Buffer::initializeVertexIndex()
{
	auto caps = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getCapabilities();
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getDirect3D11Device();

	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTyped();
	auto elementSize = getFormat()->getSize();
	auto numElements = getWidth();
	HRESULT hr = S_OK;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = numElements * elementSize;
	bd.Usage = D3D11_USAGE_DEFAULT;
	switch(getFormat()->getUsage())
	{
	case FormatUsage::General:
		bd.BindFlags |= D3D11_BIND_VERTEX_BUFFER;
		break;
	case FormatUsage::IndexBuffer:
		bd.BindFlags |= D3D11_BIND_INDEX_BUFFER;
		break;
	}
	if(caps->supportsShaderResourceBuffer()) 
		bd.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
	if(caps->numUnorderedAccessSlots())
		bd.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
	hr = dev->CreateBuffer(&bd, NULL, &_buf);
	CHECK_HRESULT(hr);
}

ID3D11Buffer* Direct3D11Buffer::getDirect3D11Buffer() const
{
	return _buf;
}

void Direct3D11Buffer::initializeDriver()
{
	if (getFormat()->getUsage() == FormatUsage::RawBuffer) initializeRaw();
	else initializeVertexIndex();
}

BufferDataAccessViewPtr Direct3D11Buffer::getDataAccessViewDriver(uint32_t offset, uint32_t width)
{
	return BufferDataAccessViewPtr(new Direct3D11BufferDataAccessView(shared_from_this(), offset, width));
}

BufferShaderResourceViewPtr Direct3D11Buffer::getShaderResourceViewDriver()
{
	return BufferShaderResourceViewPtr(new Direct3D11BufferShaderResourceView(shared_from_this()));
}

BufferUnorderedAccessViewPtr Direct3D11Buffer::getUnorderedAccessViewDriver()
{
	return BufferUnorderedAccessViewPtr(new Direct3D11BufferUnorderedAccessView(shared_from_this()));
}

BufferVertexArrayViewPtr Direct3D11Buffer::getVertexArrayViewDriver()
{
	return BufferVertexArrayViewPtr(new Direct3D11BufferVertexArrayView(shared_from_this()));
}

BufferIndexArrayViewPtr Direct3D11Buffer::getIndexArrayViewDriver()
{
	return BufferIndexArrayViewPtr(new Direct3D11BufferIndexArrayView(shared_from_this()));
}

LLGL_NAMESPACE_END2;