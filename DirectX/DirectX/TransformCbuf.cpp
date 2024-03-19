#include "TransformCbuf.h"

namespace Bind
{
	TransformCbuf::TransformCbuf(Graphics& gfx, const Drawable& parent, UINT slot)
		:
		parent(parent)
	{
		if (!pVcbuf)
			pVcbuf = std::make_unique<VertexConstBuffer<Transforms>>(gfx, slot);
	}

	void TransformCbuf::Bind(Graphics& gfx) noexcept
	{
		const auto modelView = parent.GetTransformXM() * gfx.GetCamera();
		const Transforms tf =
		{
			DirectX::XMMatrixTranspose(modelView),
			DirectX::XMMatrixTranspose(
				modelView *
				gfx.GetProjection()
			)
		};
		pVcbuf->Update(gfx, tf);
		pVcbuf->Bind(gfx);
	}
	/*Allocate memory for static member*/
	std::unique_ptr<VertexConstBuffer<TransformCbuf::Transforms>> TransformCbuf::pVcbuf;
}