#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(ResourceView) : public ContextChild
{
public:
	virtual ~ResourceView() override;
	ResourcePtr getParentResource() const;
protected:
	ResourceView(ResourcePtr parentResource);
private:
	ResourcePtr _parentResource;
};

LLGL_NAMESPACE_END;