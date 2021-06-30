

//*****************************************************************************
// 定数バッファ
// CPUからは書き込むから、CPU目線だと変数。shaderからは書き込んだっきりだから、GPU目線だと定数
//*****************************************************************************

// マトリクスバッファ
cbuffer ConstantBuffer : register( b0 )
{
	matrix WorldViewProjection;
}

// マテリアルバッファ
cbuffer MaterialBuffer : register( b1 )
{
	float4		Ambient;
	float4		Diffuse;
	float4		Specular;
	float4		Emission;
	float		Shininess;
	float3		Dummy;//16bit境界用
}


//=============================================================================
// 頂点シェーダ
//=============================================================================
void VertexShaderPolygon( in  float4 inPosition		: POSITION0,
						  in  float4 inNormal		: NORMAL0,
						  in  float4 inDiffuse		: COLOR0,
						  in  float2 inTexCoord		: TEXCOORD0,

						  out float4 outPosition	: SV_POSITION,
						  out float4 outNormal		: NORMAL0,
						  out float2 outTexCoord	: TEXCOORD0,
						  out float4 outDiffuse		: COLOR0 )
{
	// 頂点の座標変換
	outPosition = mul( inPosition, WorldViewProjection );

	// 法線とUVはそのままコピーする
	outNormal = inNormal;
	outTexCoord = inTexCoord;

	// 頂点カラーとマテリアルカラーを合成する
	outDiffuse = inDiffuse * Diffuse;
}



//*****************************************************************************
// グローバル変数
//*****************************************************************************
Texture2D		g_Texture : register( t0 );
SamplerState	g_SamplerState : register( s0 );


//=============================================================================
// ピクセルシェーダ
//=============================================================================
void PixelShaderPolygon( in  float4 inPosition		: POSITION0,
						 in  float4 inNormal		: NORMAL0,
						 in  float2 inTexCoord		: TEXCOORD0,
						 in  float4 inDiffuse		: COLOR0,

						 out float4 outDiffuse		: SV_Target )
{
	float4 color;

	// テクスチャから色をサンプリングする
	color = g_Texture.Sample( g_SamplerState, inTexCoord );

	//// ---------------------- モノクロにする処理
	//{
	//	// 平均値出す
	//	float average = (color.r + color.g + color.b) / 3;

	//	// 平均値格納
	////	color.r = average;
	////	color.g = average;
	////	color.b = average;
	//	color = float4(average, average, average, color.a);
	//}

	// 頂点シェーダから送られてきた色と合成する
	outDiffuse = color * inDiffuse;
}
