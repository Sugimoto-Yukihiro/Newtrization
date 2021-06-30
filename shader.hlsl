

//*****************************************************************************
// �萔�o�b�t�@
// CPU����͏������ނ���ACPU�ڐ����ƕϐ��Bshader����͏������񂾂����肾����AGPU�ڐ����ƒ萔
//*****************************************************************************

// �}�g���N�X�o�b�t�@
cbuffer ConstantBuffer : register( b0 )
{
	matrix WorldViewProjection;
}

// �}�e���A���o�b�t�@
cbuffer MaterialBuffer : register( b1 )
{
	float4		Ambient;
	float4		Diffuse;
	float4		Specular;
	float4		Emission;
	float		Shininess;
	float3		Dummy;//16bit���E�p
}


//=============================================================================
// ���_�V�F�[�_
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
	// ���_�̍��W�ϊ�
	outPosition = mul( inPosition, WorldViewProjection );

	// �@����UV�͂��̂܂܃R�s�[����
	outNormal = inNormal;
	outTexCoord = inTexCoord;

	// ���_�J���[�ƃ}�e���A���J���[����������
	outDiffuse = inDiffuse * Diffuse;
}



//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Texture2D		g_Texture : register( t0 );
SamplerState	g_SamplerState : register( s0 );


//=============================================================================
// �s�N�Z���V�F�[�_
//=============================================================================
void PixelShaderPolygon( in  float4 inPosition		: POSITION0,
						 in  float4 inNormal		: NORMAL0,
						 in  float2 inTexCoord		: TEXCOORD0,
						 in  float4 inDiffuse		: COLOR0,

						 out float4 outDiffuse		: SV_Target )
{
	float4 color;

	// �e�N�X�`������F���T���v�����O����
	color = g_Texture.Sample( g_SamplerState, inTexCoord );

	//// ---------------------- ���m�N���ɂ��鏈��
	//{
	//	// ���ϒl�o��
	//	float average = (color.r + color.g + color.b) / 3;

	//	// ���ϒl�i�[
	////	color.r = average;
	////	color.g = average;
	////	color.b = average;
	//	color = float4(average, average, average, color.a);
	//}

	// ���_�V�F�[�_���瑗���Ă����F�ƍ�������
	outDiffuse = color * inDiffuse;
}
