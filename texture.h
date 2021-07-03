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
	//void DrawTexture(char* TextureName, D3DXVECTOR2 Position, D3DXCOLOR Color, float Rotation);
	void DrawTexture(ID3D11Buffer* VertexBuffer, ID3D11ShaderResourceView* TextureData);

private:
	//------------------- �����o�ϐ�
//	ID3D11Buffer*				VertexBuffer = NULL;				// ���_���
//	ID3D11ShaderResourceView*	TextureData;
	D3DXVECTOR2					m_vTexPos;		// �e�N�X�`���̕`��ʒu
	D3DXVECTOR2					m_vSize;		// �e�N�X�`���� ��������
	float						m_fU, m_fV;		// UV���W�n
	float						m_fRotation;	// �e�N�X�`���̉�]�p
};

// �A�j���[�V�����N���X
class CAnimation
{
public:
	//�O�̂��߂̃R���X�g�ƃf�X�g
//	CAnimation();
//	~CAnimation();

	//------------------- �����o�֐�
//	void ChangeAnimIndex(int& CurrentIndex, int& CurrentAnimFlame, int FlameWait, int MotionStartNum, int UseGraphNum);
	void UpdateAnimIndex(int MotionStartIndex, int MotionEndIndex);

private:
	//------------------- �����o�ϐ�
	int m_nDivideX, m_nDivideY;		// �e�N�X�`���̏c���̕�����
	int m_nCurrentAnimIndex;		// ���݂̃A�j���[�V�����ԍ�
	int m_nCurrentFlame;			// ���݂̃t���[���l
	int m_nAnimWait;				// �摜���؂�ւ��Wait�l�i�P�ʂ̓t���[���j
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
