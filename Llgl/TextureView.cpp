#include "Library.h"

LLGL_NAMESPACE(Llgl);

TextureView::TextureView(TexturePtr parentTexture) : ResourceView(parentTexture)
{

}

TextureView::~TextureView()
{

}

TexturePtr TextureView::getParentResource() const
{
	return std::dynamic_pointer_cast<Texture>(ResourceView::getParentResource());
}


LLGL_NAMESPACE_END;