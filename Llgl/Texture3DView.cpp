#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture3DView::Texture3DView(Texture3DPtr parentTexture) : ResourceView(parentTexture)
{

}

Texture3DView::~Texture3DView()
{

}

Texture3DPtr Texture3DView::getParentResource() const
{
	return std::dynamic_pointer_cast<Texture3D>(ResourceView::getParentResource());
}

LLGL_NAMESPACE_END;