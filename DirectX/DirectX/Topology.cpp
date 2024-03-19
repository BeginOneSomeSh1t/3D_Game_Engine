#include "Topology.h"
#include "BindableCodex.h"

namespace Bind
{
	Topology::Topology(Graphics& gfx, D3D11_PRIMITIVE_TOPOLOGY type)
		:
		type(type)
	{}

	void Topology::Bind(Graphics& gfx) noexcept
	{
		GetContext(gfx)->IASetPrimitiveTopology(type);
	}
	DEFINE_RESOLVE(Topology, Topology, Graphics& gfx, D3D11_PRIMITIVE_TOPOLOGY type)
	{
		return Codex::Resolve<Topology>(gfx, type);
	}
	DEFINE_GENERATEUID(Topology, D3D11_PRIMITIVE_TOPOLOGY type)
	{
		using namespace std::string_literals;
		return typeid(Topology).name() + "#"s + std::to_string(type);
	}
	DEFINE_OVERIDDEN_GETUID(Topology)
	{
		return GenerateUID(type);
	}

}