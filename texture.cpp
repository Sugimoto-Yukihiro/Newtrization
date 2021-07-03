//=============================================================================
//
// �e�N�X�`���֘A���� [texture.cpp]
// Author : ���{�K�G
//
//=============================================================================

#include "main.h"
#include "texture.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************



//=============================================================================
// �����o�ϐ��̏������iCTexture�j
//=============================================================================
void CTexture::Init()	// �S�Ẵ����o�ϐ����O�ŏ�����
{
	m_vTexPos = ZERO_VECTOR2;
	m_vSize = ZERO_VECTOR2;
	m_Color = DEFAULT_COLOR;
	m_fU = m_fV = 0.0f;
	m_fRotation = 0.0f;

	//------------------- �x�[�X�N���X�̏�����
	CAnimation::Init();		// CAnimation
}



//=============================================================================
// �e�N�X�`���`��֐��iCTexture�j
// ���� :	�e�N�X�`���̃t�@�C����, �`����W, ���_�F, ��]�p
// ���� :	�e�N�X�`�����A�����Ɏw�肳�ꂽ�l�ɕ`�悷�鏈��
//=============================================================================
//void CTexture::DrawTexture(D3DXVECTOR2 Position, D3DXVECTOR2 Size, D3DXCOLOR Color, float Rotation)
void CTexture::DrawTexture(ID3D11Buffer* pVertexBuffer, ID3D11ShaderResourceView* pTextureData)
{
	float tw, th, tU, tV;

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &pTextureData);

	//------------------- �A�j���[�V�������l�����āAUV���W�̒l�����肷��
	// 1�̃A�j���[�V�����p�^�[��������̕��ƍ��������߂�
	tw = 1.0f / GetDivideX();							// ��
	th = 1.0f / GetDivideY();							// ����
	tU = (float)(GetCurrentAnim() % GetDivideX()) * tw;	// �e�N�X�`���̍���X���W
	tV = (float)(GetCurrentAnim() / GetDivideX()) * th;	// �e�N�X�`���̍���Y���W

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColorRotation(pVertexBuffer, m_vTexPos.x, m_vTexPos.y, m_vSize.x, m_vSize.y, tU, tV, tw, th,
		m_Color, m_fRotation);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
}



//=============================================================================
// �Z�b�^�[�֐��iCTexture�j
//=============================================================================
void CTexture::SetU(float U)	// UV���W��U�l��ύX����֐�
{
	m_fU = U;
}

void CTexture::SetV(float V)	// UV���W��V�l��ύX����֐�
{
	m_fU = V;
}



//=============================================================================
// �Q�b�^�[�֐��iCTexture�j
//=============================================================================
D3DXVECTOR2 CTexture::GetTexPos()
{
	return m_vTexPos;
}

D3DXVECTOR2 CTexture::GetTexSize()
{
	return m_vSize;
}



//=============================================================================
// �����o�ϐ��̏������iCAnimation�j
//=============================================================================
void CAnimation::Init()	// �S�Ẵ����o�ϐ����O�ŏ�����
{
	m_nDivideX = m_nDivideY = 0;
	m_nCurrentAnimIndex = 0;
	m_nCurrentFlame = 0;
	m_nAnimWait = 0;
}



//=============================================================================
// �A�j���[�V�����ԍ��̍X�V�֐��iCAnimation�j
// ���� :	�A�j���[�V�����̎n�_�ԍ�, �A�j���[�V�����̏I�_�ԍ�
// ���� :	�A�j���[�V�����ԍ��̍X�V�B
//			Wait�l�ƌ��݂̃t���[���l���r���āA�A�j���[�V�����ԍ��̉��Z���s���B
//=============================================================================
void CAnimation::UpdateAnimIndex(int MotionStartIndex, int MotionEndIndex)
{
	// 1�t���[�����Z
	m_nCurrentFlame++;

	// �؂�ւ���t���[���ɂȂ���������
	if (m_nCurrentFlame >= m_nAnimWait)
	{
		// �A�j���[�V�����ԍ��̍X�V
		m_nCurrentAnimIndex++;

		// �I�_�ԍ����I�[�o�[���Ă�����
		if (m_nCurrentAnimIndex > MotionEndIndex)
		{
			m_nCurrentAnimIndex = MotionStartIndex;	// �n�_�Ƀ��Z�b�g
		}

		// �o�߃t���[�����̃��Z�b�g
		m_nCurrentFlame = 0;
	}

}



//=============================================================================
// �Z�b�^�[�֐��iCAnimation�j
//=============================================================================
void CAnimation::SetDivideX(int DivX)		// ���̃A�j���[�V�����p�^�[�������i�[
{
	m_nDivideX = DivX;
}

void CAnimation::SetDivideY(int DivY)		// �c�̃A�j���[�V�����p�^�[�������i�[
{
	m_nDivideY = DivY;
}

void CAnimation::SetAnimWait(int Wait)		// Wait�l��ύX����֐�
{
	m_nAnimWait = Wait;
}



//=============================================================================
// �Q�b�^�[�֐��iCAnimation�j
//=============================================================================
int CAnimation::GetCurrentAnim()		// ���݂̃A�j���[�V�����ԍ����擾����֐�
{
	return m_nCurrentAnimIndex;
}

int CAnimation::GetDivideX()			// �������̃A�j���[�V�����p�^�[�������擾����֐�
{
	return m_nDivideX;
}

int CAnimation::GetDivideY()			// �c�����̃A�j���[�V�����p�^�[�������擾����֐�
{
	return m_nDivideY;
}



//=============================================================================
// ���_�f�[�^�ݒ�(2D)
//=============================================================================
void SetVertex(ID3D11Buffer *buf, float X, float Y, float Width, float Height, float U, float V, float UW, float VH)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	// ��������_�Ƃ��Đݒ肷��v���O����
	vertex[0].Position = D3DXVECTOR3(X, Y, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	vertex[1].Position = D3DXVECTOR3(X + Width, Y, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	vertex[2].Position = D3DXVECTOR3(X, Y + Height, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	vertex[3].Position = D3DXVECTOR3(X + Width, Y + Height, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(buf, 0);
}

// �e�N�X�`���̔z�u
void SetSprite(ID3D11Buffer *buf, float X, float Y, float Width, float Height, float U, float V, float UW, float VH)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = Width * 0.5f;		// �e�N�X�`���̔����̕�   // �R���s���[�^�[�͊���Z�����
	hh = Height * 0.5f;		// �e�N�X�`���̔����̍��� // �|���Z�̕�������������

	// �w�肳�ꂽ���W�𒆐S�ɐݒ肷��v���O����

	// ���_�O�ԁi����̒��_�j
	vertex[0].Position = D3DXVECTOR3(X - hw, Y - hh, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	// ���_�P�ԁi�E��̒��_�j
	vertex[1].Position = D3DXVECTOR3(X + hw, Y - hh, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	// ���_�Q�ԁi�����̒��_�j
	vertex[2].Position = D3DXVECTOR3(X - hw, Y + hh, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	// ���_�R�ԁi�E���̒��_�j
	vertex[3].Position = D3DXVECTOR3(X + hw, Y + hh, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(buf, 0);
}

// +�F
void SetSpriteColor(ID3D11Buffer *buf, float X, float Y, float Width, float Height,
		float U, float V, float UW, float VH,
		D3DXCOLOR color)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = Width * 0.5f;		// �R���s���[�^�[�͊���Z�����
	hh = Height * 0.5f;		// �|���Z�̕�������������

	// �w�肳�ꂽ���W�𒆐S�ɐݒ肷��v���O����

	// ���_�O�ԁi����̒��_�j
	vertex[0].Position = D3DXVECTOR3(X - hw, Y - hh, 0.0f);
	vertex[0].Diffuse = color;
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	// ���_�P�ԁi�E��̒��_�j
	vertex[1].Position = D3DXVECTOR3(X + hw, Y - hh, 0.0f);
	vertex[1].Diffuse = color;
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	// ���_�Q�ԁi�����̒��_�j
	vertex[2].Position = D3DXVECTOR3(X - hw, Y + hh, 0.0f);
	vertex[2].Diffuse = color;
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	// ���_�R�ԁi�E���̒��_�j
	vertex[3].Position = D3DXVECTOR3(X + hw, Y + hh, 0.0f);
	vertex[3].Diffuse = color;
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(buf, 0);

}

// +�F�E��]
void SetSpriteColorRotation(ID3D11Buffer *buf, float X, float Y, float Width, float Height,
	float U, float V, float UW, float VH,
	D3DXCOLOR Color, float Rot)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = Width * 0.5f;		// �R���s���[�^�[�͊���Z�����
	hh = Height * 0.5f;		// �|���Z�̕�������������

	// �w�肳�ꂽ���W�𒆐S�ɉ�]����v���O����
	float BaseAngle = atan2f(hh, hw);		// ���S�_���璸�_�ɑ΂���p�x
	D3DXVECTOR2 temp = D3DXVECTOR2(hw, hh);
	float Radius = D3DXVec2Length(&temp);	// ���S�_���璸�_�ɑ΂��鋗��

	// �����ŃA�t�B���ϊ��isincos�̂�j���g����4���_����]������
	float x = X - cosf(BaseAngle + Rot) * Radius;
	float y = Y - sinf(BaseAngle + Rot) * Radius;
	vertex[0].Position = D3DXVECTOR3(x, y, 0.0f);

	x = X + cosf(BaseAngle - Rot) * Radius;
	y = Y - sinf(BaseAngle - Rot) * Radius;
	vertex[1].Position = D3DXVECTOR3(x, y, 0.0f);

	x = X - cosf(BaseAngle - Rot) * Radius;
	y = Y + sinf(BaseAngle - Rot) * Radius;
	vertex[2].Position = D3DXVECTOR3(x, y, 0.0f);

	x = X + cosf(BaseAngle + Rot) * Radius;
	y = Y + sinf(BaseAngle + Rot) * Radius;
	vertex[3].Position = D3DXVECTOR3(x, y, 0.0f);

	vertex[0].Diffuse = Color;
	vertex[1].Diffuse = Color;
	vertex[2].Diffuse = Color;
	vertex[3].Diffuse = Color;

	vertex[0].TexCoord = D3DXVECTOR2(U, V);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(buf, 0);

}

