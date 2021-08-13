//=============================================================================
//
// �e�N�X�`���֘A���� [texture.h]
// Author : ���{�K�G
//
//=============================================================================
#pragma once

//#include "main.h"

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
	void UpdateAnimIndex(int MotionStartIndex, int MotionEndIndex);	// �A�j���[�V����
	void Init(int DivX = 1, int DivY = 1, int Wait = 0, int Index = 0);		// �����o�ϐ��̏�����
	void Uninit();		// �I������

	//------------------- �Z�b�^�[�֐�
	void SetTexDivideX(int DivX);	// ���̕��������i�[
	void SetTexDivideY(int DivY);	// �c�̕��������i�[
	void SetAnimWait(int Wait);		// �A�j���[�V������Wait�l���Z�b�g

	//------------------- �Q�b�^�[�֐�
	int GetCurrentAnim();			// ���݂̃A�j���[�V�����ԍ����擾
	int GetTexDivideX();			// ���̕��������擾
	int GetTexDivideY();			// �c�̕��������擾
//	int GetAnimWait();				// �A�j���[�V������Wait�l���擾

private:
	//------------------- �����o�ϐ�
	int m_nDivideX, m_nDivideY;		// �e�N�X�`���̏c���̕�����
	int m_nAnimWait;				// �摜���؂�ւ��Wait�l�i�P�ʂ̓t���[���j
	int m_nCurrentAnimIndex;		// ���݂̃A�j���[�V�����ԍ�
	int m_nCurrentFlame;			// ���݂̃t���[���l
};


// �e�N�X�`���N���X
class CTexture : public CAnimation
{
public:
	CTexture();		// �R���X�g���N�^
//	~CTexture();		// �f�X�g���N�^

	//------------------- �����o�֐�
	void DrawTexture(ID3D11ShaderResourceView* TextureData, ID3D11Buffer* VertexBuffer);
	void DrawTexture(ID3D11ShaderResourceView* TextureData);
	void DrawTextureTopLeft(ID3D11ShaderResourceView* TextureData);	// ��]�͔��f����Ȃ��I

	// ����������
//�~	void Init(D3DXVECTOR2 Pos = ZERO_VECTOR2, D3DXVECTOR2 Size = ZERO_VECTOR2, D3DXCOLOR Color = DEFAULT_COLOR, float Rotaiton = 0.0f,	// �e�N�X�`��
	void Init(D3DXVECTOR2 Pos = D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2 Size = D3DXVECTOR2(0.0f, 0.0f), D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), float Rotaiton = 0.0f,	// �e�N�X�`��
		int TexDivX = 1, int TexDivY = 1, int AnimWait = 0, int IndexNo = 0);	// �A�j���[�V����
	// �I������
	void Uninit();

//	void AddTexPos(D3DXVECTOR2 Pos);		// �e�N�X�`���\�����W�����炷

	//------------------- �Z�b�^�[�֐�
	//void SetTextureInf(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, D3DXCOLOR Color, float Rotation, D3DXVECTOR2 UV);
	void SetTexPos(D3DXVECTOR2 Pos);		// �e�N�X�`���̕`��ʒu���Z�b�g
	void SetTexSize(D3DXVECTOR2 Size);		// �e�N�X�`���̃T�C�Y���Z�b�g
	void SetTexColor(D3DXCOLOR Color);		// ���_�F�̃Z�b�g
	void SetTexRotation(float Rotaiton);	// ��]�l�̃Z�b�g
	void SetTexU(float U);					// �e�N�X�`����UV���W��U�l���Z�b�g
	void SetTexV(float V);					// �e�N�X�`����UV���W��V�l���Z�b�g

	//------------------- �Q�b�^�[�֐�
	D3DXVECTOR2 GetTexPos();				// �e�N�X�`���̕`��ʒu���擾
	D3DXVECTOR2 GetTexSize();				// �e�N�X�`���̃T�C�Y���擾

	//------------------- �����o�ϐ�(public)
//	int		m_nTexNo;		// �e�N�X�`���ԍ�		// tecture.cpp���Ŏg���ĂȂ����炢���

private:
	//------------------- �����o�ϐ�
//	ID3D11Buffer*				VertexBuffer = NULL;// ���_���
//	ID3D11ShaderResourceView*	TextureData;
	D3DXVECTOR2					m_vTexPos;			// �e�N�X�`���̕`��ʒu
	D3DXVECTOR2					m_vTexSize;			// �e�N�X�`���� ��������
	D3DXCOLOR					m_TexColor;			// ���_�F
	float						m_fTexU, m_fTexV;	// UV���W�n(�e�N�X�`���֐��̓����I�ɏ������Ă�)
	float						m_fTexRotation;		// �e�N�X�`���̉�]�p

};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void SetVertex(float X, float Y, float Width, float Height, float U, float V, float UW, float VH);
void SetSprite(ID3D11Buffer *buf, float X, float Y, float Width, float Height, float U, float V, float UW, float VH);
void SetSpriteColor(ID3D11Buffer *buf, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR color);
void SetSpriteColorRotation(ID3D11Buffer *buf, float X, float Y, float Width, float Height,
	float U, float V, float UW, float VH,
	D3DXCOLOR Color, float Rot);
void SetSpriteColorTopLeft(ID3D11Buffer *buf, float X, float Y, float Width, float Height,
	float U, float V, float UW, float VH,
	D3DXCOLOR Color);


// �e�N�X�`�����̐���
void CreateTexture(const char* TextureName, ID3D11ShaderResourceView** TexrureData);
// �e�N�X�`�����̉��
void ReleaseTexture(ID3D11ShaderResourceView** TexrureData);

// ���_�o�b�t�@����
void CreateVertexBuffer(ID3D11Buffer** VertexBuffer);	// �C�ӂ̒��_�o�b�t�@�𐶐�
void CreateVertexBuffer(void);							// �e�N�X�`���֐��̃O���[�o���̒��_�o�b�t�@ver
// ���_�o�b�t�@�̉��
void ReleaseVertexBuffer(ID3D11Buffer** VertexBuffer);	// �C�ӂ̒��_�o�b�t�@�����
void ReleaseVertexBuffer(void);							// �e�N�X�`���֐��̃O���[�o���̒��_�o�b�t�@ver


// �`�揈��( DrawTexture() ) �̑O��1�񂾂��Ăяo�����܂��Ȃ��i����ł��Ăяo���Ă������ǁA�����߂�����d���Ȃ�j
void PresetDraw2D(ID3D11Buffer** g_VertexBuffer);		// �C�ӂ̒��_�o�b�t�@���g�p
void PresetDraw2D(void);								// �O���[�o���̒��_�o�b�t�@���g�p
