//=============================================================================
// �e�N�X�`���֘A���� [texture.h]
// Author : ���{�K�G
//=============================================================================
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTexture
{
public:
	void SetV(float V);
	void SetU(float U);
	void DrawTexture(char* TextureName, D3DXVECTOR2 Position, D3DXCOLOR Color, float Rotation);

private:
	//------------------- �����o�ϐ�
	ID3D11Buffer*				g_VertexBuffer = NULL;				// ���_���
	ID3D11ShaderResourceView*	TextureData;
	D3DXVECTOR2					m_vTexPos;		// �e�N�X�`���̕`��ʒu
	D3DXVECTOR2					m_vSize;		// �e�N�X�`���� ��������
	float						m_fU, m_fV;		// UV���W�n
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void SetVertex(ID3D11Buffer *buf, float X, float Y, float Width, float Height, float U, float V, float UW, float VH);

void SetSprite(ID3D11Buffer *buf, float X, float Y, float Width, float Height, float U, float V, float UW, float VH);

void SetSpriteColor(ID3D11Buffer *buf, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR color);

void SetSpriteColorRotation(ID3D11Buffer *buf, float X, float Y, float Width, float Height,
	float U, float V, float UW, float VH,
	D3DXCOLOR Color, float Rot);
