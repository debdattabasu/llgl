#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture1DShaderResourceView::Texture1DShaderResourceView(Texture1DPtr parentTexture) :
	Texture1DView(parentTexture)
{

}

Texture1DShaderResourceView::~Texture1DShaderResourceView()
{

}

void Texture1DShaderResourceView::initialize()
{
	Context::LockGuard lock(getParentContext()); 
	initializeDriver();
}

LLGL_NAMESPACE_END;