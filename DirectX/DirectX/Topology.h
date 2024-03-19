#pragma once
#include "Bindable.h"


namespace Bind
{
	class Topology : public Bindable
	{
	public:
		Topology(Graphics& gfx, D3D11_PRIMITIVE_TOPOLOGY type);
		void Bind(Graphics& gfx) noexcept override;
		DECLARE_RESOLVE(Topology, Graphics& gfx, D3D11_PRIMITIVE_TOPOLOGY type);
		DECLARE_GENERATEUID(D3D11_PRIMITIVE_TOPOLOGY type);
		DECLARE_OVERRIDE_GETUID();
	protected:
		D3D11_PRIMITIVE_TOPOLOGY type;
	};
}

