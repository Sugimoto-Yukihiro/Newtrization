//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : ���Α�q, ���{�K�G
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "sprite.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_WIDTH				(200/2)	// �L�����T�C�Y
#define TEXTURE_HEIGHT				(200/2)	// 
#define TEXTURE_MAX					(1)		// �e�N�X�`���̐�

#define TEXTURE_PATTERN_DIVIDE_X	(3)		// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y	(1)		// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define ANIM_WAIT					(4)		// �A�j���[�V�����̐؂�ւ��Wait�l


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;				// ���_���
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

static char *g_TexturName[] = {
	"data/TEXTURE/player.png",
};

static CPlayer	g_aPlayer[PLAYER_MAX];								// �v���C���[�C���X�^���X

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer()
{
	// �v���C���[�\���̂̏�����
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		g_aPlayer[i].use = true;
		g_aPlayer[i].w   = TEXTURE_WIDTH;
		g_aPlayer[i].h   = TEXTURE_HEIGHT;
		g_aPlayer[i].pos = D3DXVECTOR3(500.0f, 500.0f, 0.0f);	// ���S�_����\���ɂ���
		g_aPlayer[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayer[i].texNo = 0;

		g_aPlayer[i].countAnim = 0;
		g_aPlayer[i].patternAnim = 0;
	}
}

void InitPlayer()
{
	//�e�N�X�`������
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Texture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TexturName[i],
			NULL,
			NULL,
			&g_Texture[i],
			NULL);
	}


	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);
}

//=============================================================================
// �I������
//=============================================================================
CPlayer::~CPlayer()
{

}

void UninitPlayer()
{
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Texture[i])
		{
			g_Texture[i]->Release();
			g_Texture[i] = NULL;
		}
	}

}


//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update()
{
	if (use == true)	// ���̃v���C���[���g���Ă���H
	{								// Yes
		// �A�j���[�V����  (wait�l)
		countAnim++;
		if ((countAnim % ANIM_WAIT) == 0)
		{
			// �p�^�[���̐؂�ւ�
			patternAnim = (patternAnim + 1) % ANIM_PATTERN_NUM;
		}

		// �L�[���͂ňړ� 
		if (GetKeyboardPress(DIK_DOWN))
		{
			pos.y += 10.0f;
		}
		else if (GetKeyboardPress(DIK_UP))
		{
			pos.y -= 10.0f;
		}
		if (GetKeyboardPress(DIK_RIGHT))
		{
			pos.x += 10.0f;
		}
		else if (GetKeyboardPress(DIK_LEFT))
		{
			pos.x -= 10.0f;
		}

		// �Q�[���p�b�h�łňړ�����
		if (IsButtonPressed(0, BUTTON_DOWN))
		{
			pos.y += 2.0f;
		}
		else if (IsButtonPressed(0, BUTTON_UP))
		{
			pos.y -= 2.0f;
		}

		if (IsButtonPressed(0, BUTTON_RIGHT))
		{
			pos.x += 2.0f;
		}
		else if (IsButtonPressed(0, BUTTON_LEFT))
		{
			pos.x -= 2.0f;
		}

	}

#ifdef _DEBUG	// �f�o�b�O����\������
//	char *str = GetDebugStr();
//	sprintf(&str[strlen(str)], " PX:%.2f PY:%.2f", g_aPlayer[0].pos.x, g_aPlayer[0].pos.y);
#endif

}

void UpdatePlayer(void)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		g_aPlayer[i].Update();
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw()
{
	if (use == true)
		{
			// �e�N�X�`���ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[texNo]);

			//�v���C���[�̈ʒu��e�N�X�`���[���W�𔽉f
			float px = pos.x;	// �v���C���[�̕\���ʒuX
			float py = pos.y;	// �v���C���[�̕\���ʒuY
			float pw = w;		// �v���C���[�̕\����
			float ph = h;		// �v���C���[�̕\������

			float tw = 1.0f / TEXTURE_PATTERN_DIVIDE_X;	// �e�N�X�`���̕�
			float th = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;	// �e�N�X�`���̍���
			float tx = (float)(patternAnim % TEXTURE_PATTERN_DIVIDE_X) * tw;	// �e�N�X�`���̍���X���W
			float ty = (float)(patternAnim / TEXTURE_PATTERN_DIVIDE_X) * th;	// �e�N�X�`���̍���Y���W

			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			SetSpriteColorRotation(g_VertexBuffer, px, py, pw, ph, tx, ty, tw, th,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				rot.z);

			// �|���S���`��
			GetDeviceContext()->Draw(4, 0);
		}
}


void DrawPlayer(void)
{
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);


	for (int i = 0; i < PLAYER_MAX; i++)
	{
		g_aPlayer[i].Draw();
	}
}


//=============================================================================
// �v���C���[�\���̂̐擪�A�h���X���擾
//=============================================================================
//PLAYER *GetPlayer(void)
//{
//	return &g_aPlayer[0];
//}
