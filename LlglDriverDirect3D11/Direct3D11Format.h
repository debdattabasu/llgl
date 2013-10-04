#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);


LLGL_CLASS(Direct3D11Format) : public Format
{
public:
	Direct3D11Format(ContextPtr parentContext, FormatType type, uint32_t vectorSize);
	~Direct3D11Format() override;
	void initializeDriver() override;
	DXGI_FORMAT getDxgiFormatTypeless();
	DXGI_FORMAT getDxgiFormatTyped();
	DXGI_FORMAT getDxgiFormatDepthTyped();
	
	DXGI_FORMAT _dxgiFormatTypeless;
	DXGI_FORMAT _dxgiFormatTyped;
	DXGI_FORMAT _dxgiFormatDepthTyped;

};

LLGL_NAMESPACE_END2;