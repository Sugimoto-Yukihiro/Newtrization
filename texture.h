//=============================================================================
//
// �e�N�X�`���֘A���� [texture.h]
// Author : ���{�K�G
//
//=============================================================================
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
// �A�j���[�V�����N���X
class CAnimation
{
public:
//	CAnimation();		// �R���X�g���N�^
//	~CAnimation();		// �f�X�g���N�^

	//------------------- �����o�֐�
	void UpdateAnimIndex(int MotionStartIndex, int MotionEndIndex);
	void Init();

	//------------------- �Z�b�^�[�֐�
	//void SetCurrentAnim(int CurAnim);	// ���݂̃A�j���[�V�����ԍ����擾
	void SetDivideX(int DivX);		// ���̃A�j���[�V�����p�^�[�������i�[
	void SetDivideY(int DivY);		// �c�̃A�j���[�V�����p�^�[�������i�[
	void SetAnimWait(int Wait);		// �A�j���[�V������Wait�l���Z�b�g

	//------------------- �Q�b�^�[�֐�
	int GetCurrentAnim();			// ���݂̃A�j���[�V�����ԍ����擾
	int GetDivideX();				// ���̃A�j���[�V�����p�^�[�������擾
	int GetDivideY();				// �c�̃A�j���[�V�����p�^�[�������擾
//	int GetAnimWait();				// �A�j���[�V������Wait�l���擾

private:
	//------------------- �����o�ϐ�
	int m_nDivideX, m_nDivideY;		// �e�N�X�`���̏c���̕�����
	int m_nCurrentAnimIndex;		// ���݂̃A�j���[�V�����ԍ�
	int m_nCurrentFlame;			// ���݂̃t���[���l
	int m_nAnimWait;				// �摜���؂�ւ��Wait�l�i�P�ʂ̓t���[���j
};

// �e�N�X�`���N���X
class CTexture : public CAnimation
{
public:
	//------------------- �����o�֐�
	void DrawTexture(ID3D11Buffer* VertexBuffer, ID3D11ShaderResourceView* TextureData);
	void Init();

	//------------------- �Z�b�^�[�֐�
	void SetV(float V);
	void SetU(float U);

	//------------------- �Q�b�^�[�֐�
	D3DXVECTOR2 GetTexPos();
	D3DXVECTOR2 GetTexSize();

private:
	//------------------- �����o�ϐ�
//	ID3D11Buffer*				VertexBuffer = NULL;				// ���_���
//	ID3D11ShaderResourceView*	TextureData;
	D3DXVECTOR2					m_vTexPos;		// �e�N�X�`���̕`��ʒu
	D3DXVECTOR2					m_vSize;		// �e�N�X�`���� ��������
	D3DXCOLOR					m_Color;		// ���_�F
	float						m_fU, m_fV;		// UV���W�n
	float						m_fRotation;	// �e�N�X�`���̉�]�p
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
