//=============================================================================
//
// �G�l�~�[���� [enemy.cpp]
// Author : ��_�C��Y, ���{�K�G
//
//=============================================================================

#include "main.h"
#include "renderer.h"

#include "enemy.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_WIDTH				(64.0f)	// �L�����T�C�Y
#define TEXTURE_HEIGHT				(64.0f)	// 
//#define TEXTURE_MAX					(1)		// �e�N�X�`���̐�

#define TEXTURE_PATTERN_DIVIDE_X	(1)		// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y	(1)		// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define ANIM_WAIT					(4)		// �A�j���[�V�����̐؂�ւ��Wait�l

#define TEXTURE_SIZE				D3DXVECTOR2(TEXTURE_WIDTH, TEXTURE_HEIGHT)			// �T�C�Y

#define VALUE_MOVE					(4.0f)	// �G�l�~�[�̈ړ����x

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11ShaderResourceView	*g_Texture[ENEMY_TEX_PATTARN_MAX] = { NULL };	// �e�N�X�`�����

static char *g_TextureName[] = {
	"data/TEXTURE/enemy/0813_CHARACTER_�x����.PNG",	// ENEMY_TEX_01
	"data/TEXTURE/enemy/0813_CHARACTER_�x������.PNG",	// ENEMY_TEX_01
};

//CEnemy g_Enemy[ENEMY_MAX];							// �G�l�~�[�\����

// �G�l�~�[�̐��`�ړ��p�̈ړ����W�e�[�u��
//static D3DXVECTOR3 g_MoveTbl[] = {
//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
//	D3DXVECTOR3(200.0f, 0.0f, 0.0f),
//	D3DXVECTOR3(200.0f, 200.0f, 0.0f),
//};

// �G�l�~�[�̐��`�ړ��p�̈ړ��X�s�[�h�e�[�u��
//static float g_MoveSpd[] = {
//	0.01f,
//	0.01f,
//	0.01f,
//};


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy()
{
	Init();	// ����������

	//// �G�l�~�[�\���̂̏�����
	//use = true;
	//w = TEXTURE_WIDTH;
	//h = TEXTURE_HEIGHT;
	//pos = D3DXVECTOR3((float)SCREEN_CENTER_X, 300.0f, 0.0f);
	//rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//texNo = 0;

	//countAnim = 0;
	//patternAnim = 0;

	//time = 0.0f;
}

void CEnemy::Init()
{
	// �G�l�~�[�N���X�̏�����
	m_use = false;
//	m_w = TEXTURE_WIDTH;
//	m_h = TEXTURE_HEIGHT;
	m_pos = D3DXVECTOR2(0.0f, 0.0f);
//	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_texNo = 0;

//	countAnim = 0;
//	patternAnim = 0;

//	time = 0.0f;


//	for (int i = 0; i < ENEMY_TEX_PATTARN_MAX; i++)
//	{
//		CreateTexture(g_TextureName[i], &g_Texture[i]);
//	}

//	m_Tex[ENEMY_TEX_01].SetTexSize(TEXTURE_SIZE);	// �w�i�̃T�C�Y���Z�b�g
//	m_Tex[ENEMY_TEX_01].SetTexPos(SCREEN_CENTER);	// �w�i�̈ʒu���Z�b�g


	// �e�N�X�`���̏�����
	CTexture::Init();
	SetTexSize(TEXTURE_SIZE);	// �G�l�~�[�e�N�X�`���̃T�C�Y���Z�b�g
	SetTexDivideX(TEXTURE_PATTERN_DIVIDE_X);	// ���������Z�b�g
	SetTexDivideY(TEXTURE_PATTERN_DIVIDE_Y);	// ���������Z�b�g

	// �d�͂̏�����
	//CGravity::Init();
	//SetGravityObjectSize(TEXTURE_SIZE);	// �G�l�~�[�̃T�C�Y���Z�b�g
}

// �G�l�~�[�̃e�N�X�`���ꊇ����
void InitEnemy(void)
{
//	for (int i = 0; i < ENEMY_MAX; i++)
//	{
//		g_Enemy[i].Init();		// �G�l�~�[�̐������Ăяo���}��
//	}

	// �e�N�X�`������
	for (int i = 0; i < ENEMY_TEX_PATTARN_MAX; i++)
	{
		CreateTexture(g_TextureName[i], &g_Texture[i]);
	}

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{

}

// �G�l�~�[�̃e�N�X�`�����
void UninitEnemy()
{
	for (int i = 0; i < ENEMY_TEX_PATTARN_MAX; i++)
	{
		ReleaseTexture(&g_Texture[i]);	// ���
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemy::Update(CMapchip Mapchip)
{
	if (m_use == true)	// ���̃G�l�~�[���g���Ă���H
	{					// Yes
		// �A�j���[�V����  
	//	SetAnimWait(ANIM_WAIT);				// �f�t�H���g�̃A�j���[�V����Wait�l���Z�b�g
	//	UpdateAnimIndex(0, 5);				// 0-5�Ԗڂ̊Ԃ��A�j���[�V��������


		// �ړ��O�̃G�l�~�[�̍��W���擾
		D3DXVECTOR2 OldPosEnemy = m_pos;

		// �G�l�~�[�̈ړ�AI
		/*
			�����F
				�܂��͉E������ "VALUE_MOVE"�����E�����Ɉړ�������B
				�G�l�~�[�̉E�[�̕����̃}�b�v�`�b�v�ԍ��𒲂ׂĕǔ���̔ԍ��̎��͐i�s�������t�i�������j�ɂ���

				�ǔ���̔ԍ��@���@MAPCHIP_HIT_min �� MAPCHIP_HIT_MAX�̊Ԃ̐����i�܂�1~9�ԁj�ygame.h 42�s�ځz

				�}�b�v�`�b�v�ԍ��𒲂ׂāA���̒l��
						" MAPCHIP_HIT_min <= ���ׂ��}�b�v�`�b�v�ԍ� && ���ׂ��}�b�v�`�b�v�ԍ� <= MAPCHIP_HIT_MAX "
							��������i�s�������t�ɂ���I�I
		*/

		// �������ɓ�����
		{

		}

		// �E�����ɓ�����
		if (m_left == false)		// �������t���O�� false�̂Ƃ��i�܂�A�E�����ړ��j
		{
			m_pos.x += VALUE_MOVE;	// x���̕����ɓ������i�E�����j
		}

		// �}�b�v�`�b�v�̔ԍ��𒲂ׂ�
		{
			/* Mapchip.GetMapchip( ���ׂ������W )�@���@�}�b�v�`�b�v�ԍ��킩�� 
				�E�����̎��́A�G�l�~�[�E�[�̍��W
				�������̎��́A�G�l�~�[���[�̍��W

				�E�[�̏ꍇ�A�i�G�l�~�[�̒��S���W + �G�l�~�[�̕��̔����̑傫���j�� �G�l�~�[�̉E�[
												GetTexSize().x / 2
			*/
	

		}

	}



#ifdef _DEBUG	// �f�o�b�O����\������
	//char *str = GetDebugStr();
	//sprintf(&str[strlen(str)], " EX:%.2f EY:%.2f", g_Enemy[0].Pos.x, g_Enemy[0].Pos.y);
	
#endif

}

//void UpdateEnemy(void)
//{
//	for (int i = 0; i < ENEMY_MAX; i++)
//	{
//		g_Enemy[i].Update();		// �G�l�~�[�̐������Ăяo���}��
//	}
//}


//=============================================================================
// �`�揈��
//=============================================================================
void CEnemy::Draw(D3DXVECTOR2 ScrollPos)
{
	// �`��̑O����
//	PresetDraw2D();

	if (m_use == true)	// ���̃G�l�~�[���g���Ă���H
	{					// Yes
		// �\�����W�ɕϊ�
		SetTexPos(m_pos - ScrollPos);

		// �G�l�~�[�̐i�s�����ɂ���Ďg�p�e�N�X�`����ς���
		if (m_left) m_texNo = ENEMY_TEX_LEFT;	// ������
		else m_texNo = ENEMY_TEX_01;			// �E����
		
		// �`����s
		DrawTexture(g_Texture[m_texNo]);	// texNo�̃e�N�X�`����`��
	}

}

//void DrawEnemy(void)
//{
//	for (int i = 0; i < ENEMY_MAX; i++)
//	{
//		g_Enemy[i].Draw();			// �G�l�~�[�̐������Ăяo���}��
//	}
//}


// �G�l�~�[�̃Z�b�g
bool CEnemy::SetEnemy(D3DXVECTOR2 Pos, bool LeftFlag)
{
	// ���Ɏg�p���������玸�s��Ԃ�
	if (m_use) return(false);

	// �g�p���̎��@���@�g�p�t���O��true�ɂ��ăG�l�~�[���w����W�ɃZ�b�g
	m_pos = Pos;		// ���W�Z�b�g
	m_left = LeftFlag;	// �������������w��
	m_use = true;		// �g�p�t���O���Z�b�g

	// ������Ԃ�
	return (true);
}

void CEnemy::KillEnemy()
{

}


//=============================================================================
// �G�l�~�[�\���̂̐擪�A�h���X���擾
//=============================================================================
//ENEMY *GetEnemy(void)
//{
//	return &g_Enemy[0];
//}


