#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture1DView::Texture1DView(Texture1DPtr parentTexture) : ResourceView(parentTexture)
{

}

Texture1DView::~Texture1DView()
{

}

Texture1DPtr Texture1DView::getParentResource() const
{
	return std::dynamic_pointer_cast<Texture1D>(ResourceView::getParentResource());
}

LLGL_NAMESPACE_END;