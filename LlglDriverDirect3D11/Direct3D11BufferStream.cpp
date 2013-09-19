#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

Direct3D11BufferStream::Direct3D11BufferStream(ContextPtr parentContext, uint32_t width, FormatPtr format):
	BufferStream(parentContext, width, format), _buf(0)
{

}

Direct3D11BufferStream::~Direct3D11BufferStream()
{
	SAFE_RELEASE(_buf);
}

void Direct3D11BufferStream::initializeImpl()
{
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto elementSize = getFormat()->getSize();
	auto numElements = getWidth();
	HRESULT hr = S_OK;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = numElements * elementSize;
	bd.Usage = D3D11_USAGE_STAGING;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
	hr = dev->CreateBuffer(&bd, NULL, &_buf);
	CHECK_HRESULT(hr);
}

BufferStream::MapDesc Direct3D11BufferStream::mapImpl() 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	HRESULT hr = S_OK;
	D3D11_MAPPED_SUBRESOURCE rs;
	rs.RowPitch = 0;
	rs.pData = 0;
	hr = ctx->Map(_buf, 0, D3D11_MAP_READ_WRITE, 0, &rs);
	CHECK_HRESULT(hr);
	BufferStream::MapDesc ret = {(char*)rs.pData};
	return ret;
}

void Direct3D11BufferStream::unmapImpl() 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ctx->Unmap(_buf, 0);
}

void Direct3D11BufferStream::readDataImpl(BufferPtr src, uint32_t offset) 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Buffer>(src)->_buf; 
	ID3D11Resource* destRes = _buf;
	D3D11_BOX bx;
	auto elementSize = getFormat()->getSize();
	bx.left = offset * elementSize; 
	bx.right = (offset + getWidth()) * elementSize;
	bx.top = 0;
	bx.bottom = 1;
	bx.front = 0;
	bx.back = 1;
	ctx->CopySubresourceRegion(destRes, 0, 0, 0, 0, srcRes, 0, &bx);
}

void Direct3D11BufferStream::writeDataImpl(BufferPtr dest, uint32_t offset) 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = _buf; 
	ID3D11Resource* destRes = std::dynamic_pointer_cast<Direct3D11Buffer>(dest)->_buf;
	D3D11_BOX bx;
	auto elementSize = getFormat()->getSize();
	bx.left = 0; 
	bx.right = (getWidth()) * elementSize;
	bx.top = 0;
	bx.bottom = 1;
	bx.front = 0;
	bx.back = 1;
	ctx->CopySubresourceRegion(destRes, 0, offset * elementSize, 0, 0, srcRes, 0, &bx);
}

LLGL_NAMESPACE_END2;