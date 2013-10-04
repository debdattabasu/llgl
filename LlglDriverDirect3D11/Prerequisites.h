#pragma once
#include "Llgl/Library.h"
#include <d3d11.h>

#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=0; } }

#define CHECK_HRESULT(hr) { if(FAILED(hr)) {throw UnexpectedErrorException(); }}

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Driver);
LLGL_CLASS(Direct3D11Context);
LLGL_CLASS(Direct3D11Capabilities);
LLGL_CLASS(Direct3D11Format);
LLGL_CLASS(Direct3D11Buffer);
LLGL_CLASS(Direct3D11BufferDataAccessView);
LLGL_CLASS(Direct3D11Texture1DStream);
LLGL_CLASS(Direct3D11Texture1D);
LLGL_CLASS(Direct3D11Texture1DSlice);
LLGL_CLASS(Direct3D11Texture2DStream);
LLGL_CLASS(Direct3D11Texture2DSlice);
LLGL_CLASS(Direct3D11Texture2D);
LLGL_CLASS(Direct3D11Texture3DStream);
LLGL_CLASS(Direct3D11Texture3DSlice);
LLGL_CLASS(Direct3D11Texture3D);

LLGL_NAMESPACE_END2;

