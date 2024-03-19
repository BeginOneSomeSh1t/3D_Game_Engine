#include "TransformCDualBuffs.h"

//namespace Bind
//{
//	TransformCDualBuffs::TransformCDualBuffs(Graphics& gfx, const Drawable& parent, UINT slotV, UINT slotP)
//		:
//		TransformCbuf(gfx, parent, slotV)
//	{
//		if (!pPcbuf)
//			pPcbuf = std::make_unique<PixelConstBuffer<Transforms>>(gfx, slotP);
//	}
//
//	void TransformCDualBuffs::Bind(Graphics& gfx) noexcept
//	{
//		const auto tf = GetTransforms(gfx);
//		TransformCbuf::UpdateBindImpl(gfx, tf);
//		UpdateBindImpl(gfx, tf);
//	}
//
//	void TransformCDualBuffs::UpdateBindImpl(Graphics& gfx, const Transforms& tf) noexcept
//	{
//		pPcbuf->Update(gfx, tf);
//		pPcbuf->Bind(gfx);
//	}
//	// allocate for static member
//	std::unique_ptr<PixelConstBuffer<TransformCbuf::Transforms>> TransformCDualBuffs::pPcbuf;
//}
//
//
