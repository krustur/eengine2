struct Material
{
	float4 Diffuse;
};

struct VertexIn
{
	float3 PositionLocal : POSITION;
	float4 Color : COLOR;
};

struct VertexOut
{
	float4 PosHey  : SV_POSITION;
	float4 Color : COLOR;
};

cbuffer cbufferPerObject
{
	float4x4 g_WorldViewProj; 
	Material g_Material;
};



VertexOut StandardVertexShader(VertexIn vertexIn)
{
	VertexOut vertexOut;
	
	vertexOut.PosHey = mul(float4(vertexIn.PositionLocal, 1.0f), g_WorldViewProj);
	
	vertexOut.Color = vertexIn.Color;
    
    return vertexOut;
}

float4 StandardPixelShader(VertexOut pixelIn) : SV_Target
{
    return pixelIn.Color;
}

technique11 StandardShaderTechnique
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, StandardVertexShader() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, StandardPixelShader() ) );
    }
}
