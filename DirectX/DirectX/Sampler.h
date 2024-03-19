#pragma once
#include "Bindable.h"

namespace Bind
{
	class Sampler : public Bindable
	{
	public:
		Sampler(Graphics& gfx);
		void Bind(Graphics& gfx) noexcept override;
		DECLARE_RESOLVE(Sampler, Graphics& gfx);
		DECLARE_GENERATEUID();
		DECLARE_OVERRIDE_GETUID();
	protected:
		Microsoft::WRL::ComPtr<ID3D11SamplerState> pSampler;
	};
}