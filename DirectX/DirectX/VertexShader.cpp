#include "VertexShader.h"
#include "GraphicsThrowMacros.h"
#include "ConversionMacros.h"
#include "BindableCodex.h"
#include <typeinfo>

namespace Bind
{
	

	VertexShader::VertexShader(Graphics& gfx, const std::string& path)
		:
		path(path)
	{
		INFOMAN(gfx);

		GFX_THROW_INFO(D3DReadFileToBlob(std::wstring{path.begin(), path.end()}.c_str(), &pBytecodeBlob));
		GFX_THROW_INFO(GetDevice(gfx)->CreateVertexShader(
			pBytecodeBlob->GetBufferPointer(),
			pBytecodeBlob->GetBufferSize(),
			nullptr,
			&pVertexShader
		));
	}

	void VertexShader::Bind(Graphics& gfx) noexcept
	{
		GetContext(gfx)->VSSetShader(pVertexShader.Get(), nullptr, 0u);
	}

	ID3DBlob* VertexShader::GetBytecode() const noexcept
	{
		return pBytecodeBlob.Get();
	}

	DEFINE_RESOLVE(VertexShader, VertexShader, Graphics& gfx, const std::string& path)
	{
		return Codex::Resolve<VertexShader>(gfx, path);
	}

	DEFINE_GENERATEUID(VertexShader, const std::string& path)
	{
		using namespace std::string_literals;
		return typeid(VertexShader).name() + "#"s + path;
	}

	DEFINE_OVERIDDEN_GETUID(VertexShader)
	{
		return GenerateUID(path);
	}

}