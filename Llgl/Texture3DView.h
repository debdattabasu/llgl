#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture3DView) : public ResourceView
{
public:
	virtual ~Texture3DView() override;
	Texture3DPtr getParentResource() const;
protected:
	Texture3DView(Texture3DPtr parentTexture);
};

LLGL_NAMESPACE_END;