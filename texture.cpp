//=============================================================================
// �X�v���C�g���� [sprite.cpp]
// Author : ���{�K�G
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
// �e�N�X�`���`��֐��iDrawTexture�j
// ���� :	�e�N�X�`���̃t�@�C����, �`����W, ���_�F, ��]�p
// ���� :	�e�N�X�`�����A�����Ɏw�肳�ꂽ�l�ɕ`�悷�鏈��
//=============================================================================
//void CTexture::DrawTexture(D3DXVECTOR2 Position, D3DXVECTOR2 Size, D3DXCOLOR Color, float Rotation)
void CTexture::DrawTexture(ID3D11Buffer* VertexBuffer, ID3D11ShaderResourceView* TextureData)
{
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &TextureData);

	//�v���C���[�̈ʒu��e�N�X�`���[���W�𔽉f
	float tw = 1.0f / TEXTURE_PATTERN_DIVIDE_X;	// �e�N�X�`���̕�
	float th = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;	// �e�N�X�`���̍���
	float tx = (float)(patternAnim % TEXTURE_PATTERN_DIVIDE_X) * tw;	// �e�N�X�`���̍���X���W
	float ty = (float)(patternAnim / TEXTURE_PATTERN_DIVIDE_X) * th;	// �e�N�X�`���̍���Y���W

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColorRotation(VertexBuffer, Position.x, Position.y, Size.x, Size.y, tx, ty, tw, th,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		Rotation);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
}

//=============================================================================
// �A�j���[�V�����ԍ��̍X�V�֐�
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
			m_nCurrentAnimIndex = MotionStartIndex;	// �n�_�ɃZ�b�g
		}

		// �o�߃t���[�����̃��Z�b�g
		m_nCurrentFlame = 0;
	}

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

