#pragma once
#include <vector>
#include "Vertex.h"
#include <DirectXMath.h>
#include "ConditionalNoexcept.h"



class IndexedTriangleList
{
	using USHORT = unsigned short;
public:
	IndexedTriangleList() = default;
	IndexedTriangleList(VertexSystem::VertexBuffer verts_in, std::vector<USHORT> indes_in)
		:
		vertices(std::move(verts_in)),
		indices(std::move(indes_in))
	{
		assert(vertices.Size() > 2);
		assert(indices.size() % 3 == 0);
	}
	void Transform(DirectX::FXMMATRIX matrix)
	{
		using Elements = VertexSystem::VertexLayout::ElementType;
		for (int i = 0; i < vertices.Size(); i++)
		{
			auto& pos = vertices[i].Attr<Elements::Position3D>();
			DirectX::XMStoreFloat3(
				&pos,
				DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&pos), matrix)
			);
		}
	}
	/*void SetNormalsIndependentFlat() noxnd
	{
		using namespace DirectX;
		assert(indices.size() % 3 == 0 && indices.size() > 0);
		for (size_t i = 0; i < indices.size(); i += 3)
		{
			auto& v0 = vertices[indices[i]];
			auto& v1 = vertices[indices[i + 1]];
			auto& v2 = vertices[indices[i + 2]];
			const auto p0 = XMLoadFloat3(&v0.pos);
			const auto p1 = XMLoadFloat3(&v1.pos);
			const auto p2 = XMLoadFloat3(&v2.pos);

			const auto n = XMVector3Normalize(XMVector3Cross((p1 - p0), (p2 - p0)));

			XMStoreFloat3(&v0.n, n);
			XMStoreFloat3(&v1.n, n);
			XMStoreFloat3(&v2.n, n);
		}
	}*/

public:
	VertexSystem::VertexBuffer vertices;
	std::vector<USHORT> indices;
};