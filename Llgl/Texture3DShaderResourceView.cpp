#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture3DShaderResourceView::Texture3DShaderResourceView(Texture3DPtr parentTexture) :
	Texture3DView(parentTexture)
{

}

Texture3DShaderResourceView::~Texture3DShaderResourceView()
{

}

void Texture3DShaderResourceView::initialize()
{
	Context::LockGuard lock(getParentContext()); 
	initializeDriver();
}

LLGL_NAMESPACE_END;