#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture2DView) : public TextureView
{
public:
	virtual ~Texture2DView() override;
	Texture2DPtr getParentResource() const;
protected:
	Texture2DView(Texture2DPtr parentTexture);
};

LLGL_NAMESPACE_END;