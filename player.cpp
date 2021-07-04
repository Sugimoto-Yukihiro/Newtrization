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
#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_WIDTH				(300.0f)	// �L�����T�C�Y	X
#define TEXTURE_HEIGHT				(100.0f)	//				Y
#define TEXTURE_SIZE				D3DXVECTOR2(TEXTURE_WIDTH, TEXTURE_HEIGHT)	// �L�����T�C�Y

#define TEXTURE_MAX					(1)			// �e�N�X�`���̐�

#define TEXTURE_PATTERN_DIVIDE_X	(3)			// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y	(1)			// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define ANIM_WAIT					(4)			// �A�j���[�V�����̐؂�ւ��f�t�H���gWait�l
#define MOVE_VALUE					(10.0f)

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
// �R���X�g���N�^�E�f�X�g���N�^
//=============================================================================
CPlayer::CPlayer()		// �R���X�g���N�^
{
	// �v���C���[�N���X�̏�����
	m_bUse = true;
	m_nTexNo = 0;
}

CPlayer::~CPlayer()		// �f�X�g���N�^
{

}

//=============================================================================
// ����������
//=============================================================================
void CPlayer::Init()
{
	// �v���C���[�N���X�̏�����
	m_bUse = true;
	m_nTexNo = 0;

	//------------------- �x�[�X�N���X�̏�����
	CTexture::Init();	// CTexture

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

	// �v���C���[�N���X������
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		(g_aPlayer + i)->SetPlayerUseFlag(true);
		(g_aPlayer + i)->SetTextureInf(SCREEN_CENTER, TEXTURE_SIZE, DEFAULT_COLOR, 0.0f, ZERO_VECTOR2);
		(g_aPlayer + i)->SetAnimInf(1, 1, 10);
	}

}

//=============================================================================
// �I������
//=============================================================================
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
	if (m_bUse == true)	// ���̃v���C���[���g���Ă���H
	{					// Yes
		// �A�j���[�V����
	//	UpdateAnimIndex(0, 0);	// 

		{
			D3DXVECTOR2 move;	// �v���C���[�̒l��ۑ�����ϐ�
			move = GetTexPos();	// ���݂̃v���C���[�̍��W�ŏ�����

			// �L�[���͂ňړ�
			if (GetKeyboardPress(DIK_DOWN))
			{
				move.y += MOVE_VALUE;
			}
			else if (GetKeyboardPress(DIK_UP))
			{
				move.y -= MOVE_VALUE;
			}
			else if (GetKeyboardPress(DIK_RIGHT))
			{
				move.x += MOVE_VALUE;
			}
			else if (GetKeyboardPress(DIK_LEFT))
			{
				move.x -= MOVE_VALUE;
			}

			// �Q�[���p�b�h�ňړ�����
			if (IsButtonPressed(0, BUTTON_DOWN))
			{
				move.y += MOVE_VALUE;
			}
			else if (IsButtonPressed(0, BUTTON_UP))
			{
				move.y -= MOVE_VALUE;
			}
			else if (IsButtonPressed(0, BUTTON_RIGHT))
			{
				move.x += MOVE_VALUE;
			}
			else if (IsButtonPressed(0, BUTTON_LEFT))
			{
				move.x -= MOVE_VALUE;
			}

			// �v���C���[�̍ŏI�I�ȍ��W���Z�b�g
			SetTexPos(move);
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
	if (m_bUse == true)
		{
			DrawTexture(g_VertexBuffer, g_Texture[0]);
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

	// �v���C���[�̕`��
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		g_aPlayer[i].Draw();
	}
}



//=============================================================================
// �Z�b�^�[�֐�
//=============================================================================
// �v���C���[��use�t���O�̃Z�b�g
void CPlayer::SetPlayerUseFlag(bool Use)
{
	m_bUse = Use;
}

// �v���C���[���E������
void CPlayer::KillPlayer()
{
	// �v���C���[��use�t���O��܂�
	SetPlayerUseFlag(false);

	/* �v���C���[�����񂾌�ɉ����������s���ꍇ�͂����ɋL�� */

}

//=============================================================================
// �Q�b�^�[�֐�
//=============================================================================
// �v���C���[��use�t���O�̎擾
bool CPlayer::GetPlayerUseFlag()
{
	return m_bUse;
}



//=============================================================================
// �v���C���[�\���̂̐擪�A�h���X���擾
//=============================================================================
//PLAYER *GetPlayer(void)
//{
//	return &g_aPlayer[0];
//}
