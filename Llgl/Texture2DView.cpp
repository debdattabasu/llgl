#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture2DView::Texture2DView(Texture2DPtr parentTexture) : ResourceView(parentTexture)
{

}

Texture2DView::~Texture2DView()
{

}

Texture2DPtr Texture2DView::getParentResource() const
{
	return std::dynamic_pointer_cast<Texture2D>(ResourceView::getParentResource());
}

LLGL_NAMESPACE_END;