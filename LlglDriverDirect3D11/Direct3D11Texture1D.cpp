#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

Direct3D11Texture1D::Direct3D11Texture1D(ContextPtr parentContext, uint32_t width,  uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming):
	Texture1D(parentContext, width, numMips, arraySize, format, isStreaming), _tex1d(0), _srv(0), _uavs(0)
{

}

Direct3D11Texture1D::~Direct3D11Texture1D()
{
	SAFE_RELEASE(_tex1d);
	SAFE_RELEASE(_srv);
	for(auto uav: _uavs)
	{
		SAFE_RELEASE(uav);
	}
}

void Direct3D11Texture1D::initializeStreaming()
{
	auto caps = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getCapabilities();
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmt = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormat();
	HRESULT hr = S_OK;

	D3D11_TEXTURE1D_DESC td; 
	ZeroMemory(&td, sizeof(td));
	td.Width = getWidth();
	td.MipLevels = getNumMips();
	td.ArraySize = getArraySize();
	td.Format = dxgiFmt;
	td.Usage = D3D11_USAGE_STAGING;
	td.CPUAccessFlags = D3D11_CPU_ACCESS_READ|D3D11_CPU_ACCESS_WRITE;
	hr = dev->CreateTexture1D(&td, NULL, &_tex1d);
	CHECK_HRESULT(hr);
}

void Direct3D11Texture1D::initializeDefault()
{
	auto caps = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getCapabilities();
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmt = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormat();
	HRESULT hr = S_OK;

	D3D11_TEXTURE1D_DESC td; 
	ZeroMemory(&td, sizeof(td));
	td.Width = getWidth();;
	td.MipLevels = getNumMips();
	td.ArraySize = getArraySize();
	td.Format = dxgiFmt;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	if(caps->numUnorderedAccessSlots())
		td.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;

	hr =dev->CreateTexture1D(&td, NULL, &_tex1d);
	CHECK_HRESULT(hr);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvd ;
	ZeroMemory(&srvd, sizeof(srvd));
	srvd.Format = dxgiFmt;
	if(getArraySize() ==1)
	{
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;
		srvd.Texture1D.MostDetailedMip = 0;
		srvd.Texture1D.MipLevels = -1;
	}
	else
	{
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1DARRAY ;
		srvd.Texture1DArray.MostDetailedMip = 0;
		srvd.Texture1DArray.MipLevels = -1;
		srvd.Texture1DArray.ArraySize = getArraySize();
		srvd.Texture1DArray.FirstArraySlice = 0;
	}

	hr = dev->CreateShaderResourceView(_tex1d, &srvd, &_srv);
	CHECK_HRESULT(hr);

	if(caps->numUnorderedAccessSlots())
	{
		_uavs.resize(getNumMips());
		for(uint32_t mipLevel = 0; mipLevel < getNumMips(); mipLevel ++)
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
			ZeroMemory(&uavd, sizeof(uavd));
			uavd.Format =dxgiFmt;
			if(getArraySize() ==1)
			{
				uavd.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE1D;
				uavd.Texture1D.MipSlice = mipLevel;
			}
			else
			{
				uavd.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE1DARRAY;
				uavd.Texture1DArray.MipSlice = mipLevel;
				uavd.Texture1DArray.ArraySize = getArraySize();
				uavd.Texture1DArray.FirstArraySlice = 0;
			}
			hr = dev->CreateUnorderedAccessView(_tex1d, &uavd, &_uavs[mipLevel]);
			CHECK_HRESULT(hr);
		}
	}
}

void Direct3D11Texture1D::initialize()
{
	Texture1D::initialize();
	if (isStreaming()) initializeStreaming();
	else initializeDefault();
}

LLGL_NAMESPACE_END2;