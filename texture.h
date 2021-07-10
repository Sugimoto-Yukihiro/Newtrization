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
	void Init();					// �����o�ϐ��̏�����

	//------------------- �Z�b�^�[�֐�
	void SetAnimInf(int DivX, int DivY, int Wait);
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
	void Init();							// �����o�ϐ��̏�����
//	void AddTexPos(D3DXVECTOR2 Pos);		// �e�N�X�`���\�����W�����炷

	//------------------- �Z�b�^�[�֐�
	void SetTextureInf(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, D3DXCOLOR Color, float Rotation, D3DXVECTOR2 UV);
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
	int		m_nTexNo;		// �e�N�X�`���ԍ�

private:
	//------------------- �����o�ϐ�
//	ID3D11Buffer*				VertexBuffer = NULL;// ���_���
//	ID3D11ShaderResourceView*	TextureData;
	D3DXVECTOR2					m_vTexPos;			// �e�N�X�`���̕`��ʒu
	D3DXVECTOR2					m_vTexSize;			// �e�N�X�`���� ��������
	D3DXCOLOR					m_TexColor;			// ���_�F
	float						m_fTexU, m_fTexV;	// UV���W�n
	float						m_fTexRotation;		// �e�N�X�`���̉�]�p

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

void CreateTexture(const char* TextureName, ID3D11ShaderResourceView** TexrureData);
void CreateVertexBuffer(ID3D11Buffer** VertexBuffer);
void ReleaseTexture(ID3D11ShaderResourceView** TexrureData, ID3D11Buffer** VertexBuffer);
void PresetDraw2D(ID3D11Buffer** g_VertexBuffer);