struct VSOut
{
	float3 color : COLOR;
	float4 pos : SV_POSITION;
};

cbuffer CBuff
{
	matrix transform;
};

VSOut ForVertex(float3 pos : POSITION, float3 color : COLOR)
{
	VSOut output;
	output.pos = mul(float4(pos, 1.0f), transform);
	output.color = color;
	return output;
}
