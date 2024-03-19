#include "Drawable.h"
#include "GraphicsThrowMacros.h"
#include "IndexBuffer.h"
#include <cassert>

void Drawable::Draw(Graphics& gfx) const noxnd
{
	for (auto& b : binds)
	{
		b->Bind(gfx);
	}
	gfx.DrawIndexed(pIndexBuffer->GetCount());
}

void Drawable::AddBind(std::shared_ptr<Bind::Bindable> bind) noxnd
{
	//special case for index buffer
	if (typeid(*bind) == typeid(Bind::IndexBuffer))
	{
		assert("Binding multiple index buffers is not allowed" && pIndexBuffer == nullptr);
		pIndexBuffer = &static_cast<Bind::IndexBuffer&>(*bind);
	}
	binds.push_back(std::move(bind));
}



