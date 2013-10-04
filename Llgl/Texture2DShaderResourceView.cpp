#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture2DShaderResourceView::Texture2DShaderResourceView(Texture2DPtr parentTexture) :
	Texture2DView(parentTexture)
{

}

Texture2DShaderResourceView::~Texture2DShaderResourceView()
{

}

void Texture2DShaderResourceView::initialize()
{
	Context::LockGuard lock(getParentContext()); 
	initializeDriver();
}

LLGL_NAMESPACE_END;