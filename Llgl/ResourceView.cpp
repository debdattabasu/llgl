#include "Library.h"

LLGL_NAMESPACE(Llgl);

ResourceView::ResourceView(ResourcePtr parentResource) : ContextChild(parentResource->getParentContext()), 
	_parentResource(parentResource)
{

}

ResourceView::~ResourceView()
{

}

ResourcePtr ResourceView::getParentResource() const
{
	return _parentResource;
}

LLGL_NAMESPACE_END;