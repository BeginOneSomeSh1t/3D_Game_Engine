#pragma once
#include "IndexedTriangleList.h"

class Beam
{
public:
	template<class V>
	static IndexedTriangleList<V> Make()
	{
		using namespace DirectX;
		std::vector<V> vertices;
		vertices.reserve(8);
		vertices[0].pos = XMVectorSet(-1.f, -1.f, 1.f);
		vertices[1].pos = XMVectorSet(-1.f, -1.f, -1.f);
		vertices[2].pos = XMVectorSet(-1.f, 1.f, -1.f);
		vertices[3].pos = XMVectorSet(-1.f, 1.f, 1.f);
		vertices[4].pos = XMVectorSet(1.f, -1.f, 1.f);
		vertices[5].pos = XMVectorSet(1.f, -1.f, -1.f);
		vertices[6].pos = XMVectorSet(1.f, 1.f, -1.f);
		vertices[7].pos = XMVectorSet(1.f, 1.f, 1.f);


		return { std::move(vertices),
				{
					0,1,2, 2,3,0,
					5,6,2, 2,1,5,
					5,6,7, 7,4,5,
					7,3,0, 0,4,7,
					7,3,2, 2,6,7,
					0,1,5, 5,4,0,
				}
		};
	}
};