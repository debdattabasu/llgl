#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(TextureView) : public ResourceView
{
public:
	virtual ~TextureView() override;
	TexturePtr getParentResource() const;
protected:
	TextureView(TexturePtr parentTexture);

};

LLGL_NAMESPACE_END;