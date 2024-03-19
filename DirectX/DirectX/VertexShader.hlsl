
cbuffer CBuf
{
	 matrix transform;
};

float4 main(float3 pos : Position) : SV_POSITION
{
	return mul(float4(pos, 1.f), transform);
}



