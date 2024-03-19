#pragma once
#include "Bindable.h"
#include "GraphicsThrowMacros.h"
#include "BindableCodex.h"

namespace Bind
{
	template<typename C>
	class ConstBuffer : public Bindable
	{
	public:
		void Update(Graphics& gfx, const C& consts)
		{

			INFOMAN(gfx);

			D3D11_MAPPED_SUBRESOURCE msr;
			GFX_THROW_INFO(GetContext(gfx)->Map(
				pConstantBuffer.Get(), 0u,
				D3D11_MAP_WRITE_DISCARD, 0u,
				&msr
			));
			memcpy(msr.pData, &consts, sizeof(consts));

			GetContext(gfx)->Unmap(pConstantBuffer.Get(), 0u);
		}

		ConstBuffer(Graphics& gfx, const C& consts, UINT slot = 0u)
			:
			slot(slot)
		{
			INFOMAN(gfx);

			D3D11_BUFFER_DESC cbd{};
			cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cbd.Usage = D3D11_USAGE_DYNAMIC;
			cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			cbd.MiscFlags = 0u;
			cbd.ByteWidth = sizeof(consts);
			cbd.StructureByteStride = 0u;

			D3D11_SUBRESOURCE_DATA csd{};
			csd.pSysMem = &consts;
			GFX_THROW_INFO(GetDevice(gfx)->CreateBuffer(&cbd, &csd, &pConstantBuffer));
		}
		ConstBuffer(Graphics& gfx, UINT slot = 0u)
			:
			slot(slot)
		{
			INFOMAN(gfx);

			D3D11_BUFFER_DESC cbd;
			cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cbd.Usage = D3D11_USAGE_DYNAMIC;
			cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			cbd.MiscFlags = 0u;
			cbd.ByteWidth = sizeof(C);
			cbd.StructureByteStride = 0u;
			GFX_THROW_INFO(GetDevice(gfx)->CreateBuffer(&cbd, nullptr, &pConstantBuffer));
		}
	protected:
		Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
		UINT slot;
	};


	template <typename C>
	class VertexConstBuffer : public ConstBuffer<C>
	{
		using ConstBuffer<C>::pConstantBuffer;
		using ConstBuffer<C>::slot;
		using Bindable::GetContext;
	public:
		using ConstBuffer<C>::ConstBuffer;
		void Bind(Graphics& gfx) noexcept override
		{
			GetContext(gfx)->VSSetConstantBuffers(slot, 1u, pConstantBuffer.GetAddressOf());
		}
		DECLARE_RESOLVE(VertexConstBuffer ,Graphics& gfx, const C& consts, UINT slot = 0)
		{
			return Codex::Resolve<VertexConstBuffer>(gfx, consts, slot);
		}
		DECLARE_RESOLVE(VertexConstBuffer, Graphics& gfx, UINT slot = 0)
		{
			return Codex::Resolve<VertexConstBuffer>(gfx, slot);
		}
		DECLARE_GENERATEUID(const C&, UINT slot)
		{
			return GenerateUID(slot);
		}
		DECLARE_GENERATEUID(UINT slot = 0)
		{
			using namespace std::string_literals;
			return typeid(VertexConstBuffer).name() + "#"s + std::to_string(slot);
		}
		DECLARE_OVERRIDE_GETUID()
		{
			return GenerateUID(slot);
		}
	};

	template <typename C>
	class PixelConstBuffer : public ConstBuffer<C>
	{
		using ConstBuffer<C>::pConstantBuffer;
		using ConstBuffer<C>::slot;
		using Bindable::GetContext;
	public:
		using ConstBuffer<C>::ConstBuffer;
		void Bind(Graphics& gfx) noexcept override
		{
			GetContext(gfx)->PSSetConstantBuffers(slot, 1u, pConstantBuffer.GetAddressOf());
		}
		DECLARE_RESOLVE(PixelConstBuffer, Graphics& gfx, const C& consts, UINT slot = 0)
		{
			return Codex::Resolve<PixelConstBuffer>(gfx, consts, slot);
		}
		DECLARE_RESOLVE(PixelConstBuffer, Graphics& gfx, UINT slot = 0)
		{
			return Codex::Resolve<PixelConstBuffer>(gfx, slot);
		}
		DECLARE_GENERATEUID(const C&, UINT slot)
		{
			return GenerateUID(slot);
		}
		DECLARE_GENERATEUID(UINT slot)
		{
			using namespace std::string_literals;
			return typeid(PixelConstBuffer).name() + "#"s + std::to_string(slot);
		}
		DECLARE_OVERRIDE_GETUID()
		{
			return GenerateUID(slot);
		}
	};
}

