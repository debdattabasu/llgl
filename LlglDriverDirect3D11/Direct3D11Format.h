#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);


LLGL_CLASS(Direct3D11Format) : public Format
{
public:
	Direct3D11Format(ContextPtr parentContext, FormatType type, uint32_t vectorSize);
	~Direct3D11Format() override;
	void initialize() override;
	DXGI_FORMAT getDxgiFormat();
private:
	DXGI_FORMAT _dxgiFormat;
};

LLGL_NAMESPACE_END2;