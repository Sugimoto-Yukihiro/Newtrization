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
static ID3D11Buffer		*g_VertexBuffer2D = NULL;	// ���_���


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTexture::CTexture()	// �R���X�g���N�^
{
	Init();		// �������������s��
}

//=============================================================================
// �����������iCTexture�j
//=============================================================================
void CTexture::Init(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, D3DXCOLOR Color, float Rotaiton,
					int TexDivX, int TexDivY, int AnimWait, int IndexNo)
{
	m_vTexPos = Pos;
	m_vTexSize = Size;
	m_TexColor = Color;
	m_fTexRotation = Rotaiton;
	m_fTexU = m_fTexV = 0.0f;

	//------------------- �x�[�X�N���X�̏�����
	CAnimation::Init(TexDivX, TexDivY, AnimWait, IndexNo);		// CAnimation
}



//=============================================================================
// �I�������iCTexture�j
//=============================================================================
void CTexture::Uninit()	// �S�Ẵ����o�ϐ����O�ŃN���A
{
	m_vTexPos = ZERO_VECTOR2;
	m_vTexSize = ZERO_VECTOR2;
	m_TexColor = DEFAULT_COLOR;
	m_fTexU = m_fTexV = 0.0f;
	m_fTexRotation = 0.0f;

	//------------------- �x�[�X�N���X�̏I������
	CAnimation::Uninit();		// CAnimation
}



//=============================================================================
// �e�N�X�`���`��֐��iCTexture�j
// ���� :	�e�N�X�`���̃t�@�C����, ���_���W
// ���� :	�e�N�X�`�����A�����Ɏw�肳�ꂽ�l�ɕ`�悷�鏈��
//=============================================================================
void CTexture::DrawTexture(ID3D11ShaderResourceView* pTextureData, ID3D11Buffer* pVertexBuffer)
{
	float tw = 0.0f, th = 0.0f, tU = 0.0f, tV = 0.0f;

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &pTextureData);

	//------------------- �A�j���[�V�������l�����āAUV���W�̒l�����肷��
	// 1�̃A�j���[�V�����p�^�[��������̕��ƍ��������߂�
	tw = 1.0f / (float)GetTexDivideX();							// ��
	th = 1.0f / (float)GetTexDivideY();							// ����
	if (GetCurrentAnim() != 0) tU = (float)(GetCurrentAnim() % GetTexDivideX()) * tw;	// �e�N�X�`���̍���X���W
	if (GetCurrentAnim() != 0) tV = (float)(GetCurrentAnim() / GetTexDivideX()) * th;	// �e�N�X�`���̍���Y���W

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColorRotation(pVertexBuffer, m_vTexPos.x, m_vTexPos.y, m_vTexSize.x, m_vTexSize.y, tU, tV, tw, th,
		m_TexColor, m_fTexRotation);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
}

void CTexture::DrawTexture(ID3D11ShaderResourceView* pTextureData)	// �e�N�X�`�����W�̂�
{
	float tw = 0.0f, th = 0.0f, tU = 0.0f, tV = 0.0f;

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &pTextureData);

	//------------------- �A�j���[�V�������l�����āAUV���W�̒l�����肷��
	// 1�̃A�j���[�V�����p�^�[��������̕��ƍ��������߂�
	tw = 1.0f / (float)GetTexDivideX();							// ��
	th = 1.0f / (float)GetTexDivideY();							// ����
	if (GetCurrentAnim() != 0) tU = (float)(GetCurrentAnim() % GetTexDivideX()) * tw;	// �e�N�X�`���̍���X���W
	if (GetCurrentAnim() != 0) tV = (float)(GetCurrentAnim() / GetTexDivideX()) * th;	// �e�N�X�`���̍���Y���W

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColorRotation(g_VertexBuffer2D, m_vTexPos.x, m_vTexPos.y, m_vTexSize.x, m_vTexSize.y, tU, tV, tw, th,
		m_TexColor, m_fTexRotation);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
}

// ��������_�Ƃ����`��
void CTexture::DrawTextureTopLeft(ID3D11ShaderResourceView* pTextureData)	// �e�N�X�`�����W�̂�
{
	float tw = 0.0f, th = 0.0f, tU = 0.0f, tV = 0.0f;

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &pTextureData);

	//------------------- �A�j���[�V�������l�����āAUV���W�̒l�����肷��
	// 1�̃A�j���[�V�����p�^�[��������̕��ƍ��������߂�
	tw = 1.0f / (float)GetTexDivideX();							// ��
	th = 1.0f / (float)GetTexDivideY();							// ����
	if (GetCurrentAnim() != 0) tU = (float)(GetCurrentAnim() % GetTexDivideX()) * tw;	// �e�N�X�`���̍���X���W
	if (GetCurrentAnim() != 0) tV = (float)(GetCurrentAnim() / GetTexDivideX()) * th;	// �e�N�X�`���̍���Y���W

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColorTopLeft(g_VertexBuffer2D, m_vTexPos.x, m_vTexPos.y, m_vTexSize.x, m_vTexSize.y, tU, tV, tw, th,
		m_TexColor);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);
}


//=============================================================================
// �Z�b�^�[�֐��iCTexture�j
//=============================================================================
//// �S�Ẵ����o�ϐ����ꊇ�ŕύX����֐�
//void CTexture::SetTextureInf(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, D3DXCOLOR Color, float Rotation, D3DXVECTOR2 UV)
//{
//	m_vTexPos = Pos;
//	m_vTexSize = Size;
//	m_TexColor = Color;
//	m_fTexRotation = Rotation;
//	m_fTexU = UV.x;
//	m_fTexV = UV.y;
//}

// �e�N�X�`���̕`��ʒu��ύX����֐�
void CTexture::SetTexPos(D3DXVECTOR2 Pos)
{
	m_vTexPos = Pos;
}

// �e�N�X�`���̕`��T�C�Y��ύX����֐�
void CTexture::SetTexSize(D3DXVECTOR2 Size)
{
	m_vTexSize = Size;
}

// �e�N�X�`���̒��_�F��ύX����֐�
void CTexture::SetTexColor(D3DXCOLOR Color)
{
	m_TexColor = Color;
}

// �e�N�X�`���̉�]�l��ύX����֐�
void CTexture::SetTexRotation(float Rotaiton)
{
	m_fTexRotation = Rotaiton;
}

// UV���W��U�l��ύX����֐�
void CTexture::SetTexU(float U)
{
	m_fTexU = U;
}

// UV���W��V�l��ύX����֐�
void CTexture::SetTexV(float V)
{
	m_fTexV = V;
}


//=============================================================================
// �Q�b�^�[�֐��iCTexture�j
//=============================================================================
//// �e�N�X�`���̕`��ʒu���擾����֐�
//D3DXVECTOR2 CTexture::GetTexPos()
//{
//	return m_vTexPos;
//}
//
//// �e�N�X�`���̃T�C�Y���擾����֐�
//D3DXVECTOR2 CTexture::GetTexSize()
//{
//	return m_vTexSize;
//}


// ************************ �A�j���[�V�����N���X ************************

//=============================================================================
// �����������iCAnimation�j
//=============================================================================
void CAnimation::Init(int DivX, int DivY, int Wait, int Index)	// �S�Ẵ����o�ϐ����O�ŏ�����
{
	m_nDivideX = DivX;				// �e�N�X�`���̉��̕��������Z�b�g
	m_nDivideY = DivY;				// �e�N�X�`���̏c�̕��������Z�b�g
	m_nAnimWait = Wait;				// �摜���؂�ւ��^�C�~���O���Z�b�g
	m_nCurrentAnimIndex = Index;	// �摜�ԍ����w��
	m_nCurrentFlame = 0;			// �t���[���J�E���g��0
}



//=============================================================================
// �I�������iCAnimation�j
//=============================================================================
void CAnimation::Uninit()	// �S�Ẵ����o�ϐ����O�ŃN���A
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
	// ���݂̌o�߃t���[�������Z
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
// ���̃A�j���[�V�����p�^�[�������i�[
void CAnimation::SetTexDivideX(int DivX)
{
	m_nDivideX = DivX;
}

// �c�̃A�j���[�V�����p�^�[�������i�[
void CAnimation::SetTexDivideY(int DivY)
{
	m_nDivideY = DivY;
}

// Wait�l��ύX����֐�
void CAnimation::SetAnimWait(int Wait)
{
	m_nAnimWait = Wait;
}



//=============================================================================
// �Q�b�^�[�֐��iCAnimation�j
//=============================================================================
//int CAnimation::GetCurrentAnim()	// ���݂̃A�j���[�V�����ԍ����擾����֐�
//{
//	return m_nCurrentAnimIndex;
//}
//
//int CAnimation::GetTexDivideX()	// �������̃A�j���[�V�����p�^�[�������擾����֐�
//{
//	return m_nDivideX;
//}
//
//int CAnimation::GetTexDivideY()	// �c�����̃A�j���[�V�����p�^�[�������擾����֐�
//{
//	return m_nDivideY;
//}



//=============================================================================
// ���_�f�[�^�ݒ�(2D)
//=============================================================================
void SetVertex(float X, float Y, float Width, float Height, float U, float V, float UW, float VH)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer2D, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

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

	GetDeviceContext()->Unmap(g_VertexBuffer2D, 0);
}

// �e�N�X�`���̔z�u
void SetSprite(ID3D11Buffer *buf, float X, float Y, float Width, float Height, float U, float V, float UW, float VH)
{
	// �o�b�t�@���w�肳��Ă��Ȃ���΃O���[�o���̂���g��
	if (buf == NULL) buf = g_VertexBuffer2D;

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

// +�F�E���㌴�_
void SetSpriteColorTopLeft(ID3D11Buffer *buf, float X, float Y, float Width, float Height,
	float U, float V, float UW, float VH,
	D3DXCOLOR Color)
{
	// �o�b�t�@���w�肳��Ă��Ȃ���΃O���[�o���̂���g��
	if (buf == NULL) buf = g_VertexBuffer2D;

	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	// ��������_�Ƃ��Đݒ肷��v���O����
	vertex[0].Position = D3DXVECTOR3(X, Y, 0.0f);
	vertex[0].Diffuse = Color;
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	vertex[1].Position = D3DXVECTOR3(X + Width, Y, 0.0f);
	vertex[1].Diffuse = Color;
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	vertex[2].Position = D3DXVECTOR3(X, Y + Height, 0.0f);
	vertex[2].Diffuse = Color;
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	vertex[3].Position = D3DXVECTOR3(X + Width, Y + Height, 0.0f);
	vertex[3].Diffuse = Color;
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(buf, 0);

}



void CreateTexture(const char* TextureName, ID3D11ShaderResourceView** TexrureData)
{
	//�e�N�X�`������
	D3DX11CreateShaderResourceViewFromFile(GetDevice(),
		TextureName,
		NULL,
		NULL,
		TexrureData,
		NULL);

}

// ���_�o�b�t�@�i2D�j�̐���
void CreateVertexBuffer(ID3D11Buffer** VertexBuffer)	// �C�ӂ̒��_�o�b�t�@�𐶐�
{
	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;	// 2D��4���_
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, VertexBuffer);
}
void CreateVertexBuffer(void)	// �O���[�o���̒��_�o�b�t�@�𐶐�
{
	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;	// 2D��4���_
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer2D);
}

// �e�N�X�`�����̉��
void ReleaseTexture(ID3D11ShaderResourceView** TextureData)
{
	if (*TextureData)
	{
		TextureData[0]->Release();	// ����������s
		*TextureData = NULL;		// NULL���Z�b�g
	}

}
bool ReleaseTexture(ID3D11ShaderResourceView* TextureData)
{
	if (TextureData)	// NULL����Ȃ��Ȃ���
	{
		TextureData->Release();	// ����������s
		return(true);			// "���s���Ă�"��Ԃ�
	}

	return(false);	// ����������s���ĂȂ�
}

// ���_�o�b�t�@�i2D�j�̉��
void ReleaseVertexBuffer(ID3D11Buffer** VertexBuffer)	// �C�ӂ̒��_�o�b�t�@�����
{
	if (*VertexBuffer)
	{
		VertexBuffer[0]->Release();
		*VertexBuffer = NULL;
	}

}
void ReleaseVertexBuffer(void)	// �O���[�o���̒��_�o�b�t�@�����
{
	if (g_VertexBuffer2D)
	{
		g_VertexBuffer2D->Release();
		g_VertexBuffer2D = NULL;
	}

}

// �`��O�����i���_�o�b�t�@�̐ݒ�j
void PresetDraw2D(ID3D11Buffer** VertexBuffer)	// �C�ӂ̒��_�o�b�t�@
{
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, VertexBuffer, &stride, &offset);

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);
}
void PresetDraw2D(void)	// �O���[�o���̒��_�o�b�t�@
{
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer2D, &stride, &offset);

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);
}
