//=============================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author : ���{�K�G
//
//=============================================================================
#include "main.h"
#include "renderer.h"	// �����_�����O����
#include "game.h"

#include "bg.h"			// �w�i
//#include "bullet.h"	// �o���b�g
#include "camera.h"		// �J��������
#include "collision.h"	// �Փ˔���
#include "enemy.h"		// �G�l�~�[
#include "fade.h"		// �t�F�[�h
#include "input.h"		// �L�[�E�Q�[���p�b�h���͏���
//#include "particle.h"	// �p�[�e�B�N��

//#include "score.h"	// �X�R�A
#include "sound.h"		// �T�E���h

#include "debugproc.h"	// �f�o�b�O�\��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NEXT_MODE				MODE_RESULT		// ���̃��[�h

// �}�b�v�`�b�v�̃t�@�C����
#define GAME_MAP_DATA			"data/MAPCHIP/mapdata32�~64.csv"		// �}�b�v���̃t�@�C����

// �N���X�Ǘ�
#ifdef GAMEMODE_CLASS

//=============================================================================
// ����������
//=============================================================================
void CModeGame::Init()
{
#ifdef _DEBUG
	// �|�[�Y�t���O�̏�����
	m_bPauseFlag = false;	// "false"�i�{�[�Y�����j�ŏ�����
#endif // _DEBUG

	//	g_ViewPortType_Game = TYPE_FULL_SCREEN;	// �r���[�|�[�g�ݒ�

	// �X�N���[�����W�̏�����
	SetScrollPosition(ZERO_VECTOR2);

	// �d�͕����̏�����
	m_GravityDirection = GRAVITY_DEFAULT;

	// �d�͕ύX�G���W���ɐG��Ă��܂���
	m_bIsTouchGrvityChange = false;

	// �w�i�̏�����
	InitBg();

	// �v���C���[�̏�����
	CreatePlayerTextureAndBuffer();	// �e�N�X�`���E���_�o�b�t�@����
	for(int i =0; i < PLAYER_MAX; i++)
	{
		m_Player[i].Init();	// ����������
	}

	// �}�b�v�`�b�v�̏�����
	CreateMapchipTextureAndBuffer(MAPCHIP_STAGE_Sample);	// �e�N�X�`���E���_�o�b�t�@����
	m_Mapchip.Init(GAME_MAP_DATA);	// �X�e�[�W�������[�h

	// �G�l�~�[�̏�����
	InitEnemy();

	// �e�̏�����
//	InitBullet();

	// �X�R�A�̏�����
//	InitScore();

	// �p�[�e�B�N���̏�����
//	InitParticle();

	// BGM�Đ�
//	PlaySound(SOUND_LABEL_BGM_sample001);
}

//=============================================================================
// �I������
//=============================================================================
void CModeGame::Uninit(void)
{
	// �p�[�e�B�N���̏I������
//	UninitParticle();

	// �X�R�A�̏I������
//	UninitScore();

	// �e�̏I������
//	UninitBullet();

	// �}�b�v�`�b�v�̏I������
	ReleaseMapchipTextureAndBuffer();	// �e�N�X�`���E���_�o�b�t�@���

	// �G�l�~�[�̏I������
	UninitEnemy();

	// �v���C���[�̏I������
	ReleasePlayerTextureAndBuffer();	// �e�N�X�`���E���_�o�b�t�@���
//	for (int i = 0; i < PLAYER_MAX; i++)
//	{
//		(m_Player + i)->Uninit();
//	}

	// �w�i�̏I������
	UninitBg();

}

//=============================================================================
// �X�V����
//=============================================================================
void CModeGame::Update(void)
{
#ifdef _DEBUG
	// �|�[�Y�L�[�������ꂽ��t���O�𑀍삷��
	if( KEY_PAUSE ) m_bPauseFlag ? false : true;
					// m_bPauseFlag�́H  "true"�Ȃ�"false" ��  :  "false"�Ȃ�"true" ��  �Z�b�g����

	// �|�[�Y�t���O��true�Ȃ珈�����s��Ȃ��B
	if (m_bPauseFlag) return;

	// ���X�^�[�g�̃L�[�������ꂽ�Ƃ�
	if (KEY_RESTART_GAMEMODE)
	{
		CModeGame::Uninit();	// �Q�[�����[�h�̉��
		CModeGame::Init();		// �Q�[�����[�h�̏�����
	}

	//------------------- �L�[�E�Q�[���p�b�g�ł̓��͂Ŏ��̃��[�h��
	if (KEY_MODE_CHANGE)
	{// Enter��������A�X�e�[�W��؂�ւ���
		SetFade(FADE_OUT, NEXT_MODE);	// �t�F�[�h���Ď��̃��[�h��
	//	SetMode(NEXT_MODE);				// ���̃��[�h�ɃV�[���J��
	}
	// �Q�[���p�b�h�œ��͏���
	else if (PAD_MODE_CHANGE)
	{
		SetFade(FADE_OUT, NEXT_MODE);	// �t�F�[�h���Ď��̃��[�h��
	//	SetMode(NEXT_MODE);				// ���̃��[�h�ɃV�[���J��
	}
#endif // _DEBUG


	// �d�͕����̕ύX
	if (KEY_CHANGE_GRAVITY)
	{
		m_GravityDirection = (m_GravityDirection + 1) % GRAVITY_DIRECTION_MAX;
		SetGravityDirection(m_GravityDirection);
	}


	// �}�b�v�`�b�v�̍X�V����
	m_Mapchip.Update();

	// �v���C���[�̍X�V����
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		m_Player[i].Update();
	}

	// �G�l�~�[�̍X�V����
	UpdateEnemy();

	// �e�̍X�V����
//	UpdateBullet();

	// �p�[�e�B�N���̍X�V����
//	UpdateParticle();

	// �����蔻�菈��
	CollisionCheck();

	// �X�R�A�̍X�V����
//	UpdateScore();

	// �w�i�̍X�V����
	UpdateBg();

#ifdef _DEBUG
	PrintDebugProc("\n�X�N���[�����W X: %f  Y: %f\n", GetScrollPosition().x, GetScrollPosition().y);

	PrintDebugProc("�@�@�d�͂̕���:%d ", GetGravityDirection());

	//char *str = GetDebugStr();
	//sprintf(&str[strlen(str)], "�@�@�d�͂̕���:%d ", GetGravityDirection());
#endif // _DEBUG
}

//=============================================================================
// �`�揈��
//=============================================================================
void CModeGame::Draw()
{
	// �w�i�̕`�揈��
	DrawBg();

	// �}�b�v�`�b�v�̕`��
	m_Mapchip.Draw();

	// �e�X�g�摜�\��
//	DrawPolygon();

	// �G�l�~�[�̕`�揈��
//	DrawEnemy();

	// �v���C���[�̕`�揈��
	for(int i = 0; i < PLAYER_MAX; i++)
	{
		(m_Player + i)->Draw();
	}


	// �e�̕`�揈��
//	DrawBullet();

	// �p�[�e�B�N���̕`�揈��
//	DrawParticle();

	// �X�R�A�̕`�揈��
//	DrawScore();
}



//=============================================================================
// �����蔻�菈��
//=============================================================================
void CModeGame::CollisionCheck()
{
	// �v���C���[�ƃ}�b�v�`�b�v�̓����蔻��
	{
	//	int Num = m_Mapchip.GetMapchipNo(m_Player->GetPlayerPos());	// �v���C���[���W�̃}�b�v�`�b�v���擾

		// �v���C���[���W�̃}�b�v�`�b�v���擾���āA���̒l�ɂ���ď�����ς���
	//	switch (Num)
		switch ( m_Mapchip.GetMapchipNo(m_Player->GetPlayerPos()) )	// �v���C���[���W�̃}�b�v�`�b�v���擾
		{
		// �d�͕ύX�G���W���ɐG�ꂽ�Ƃ�
		case 10:
			// �d�͕����̕ύX
			if (!m_bIsTouchGrvityChange)	// �d�͑��u�ɐG��Ă��Ȃ��Ƃ������l�̎�
			{
				/*����֐����ł����*/
				m_GravityDirection = (m_GravityDirection + 1) % GRAVITY_DIRECTION_MAX;
				SetGravityDirection(m_GravityDirection);
				m_bIsTouchGrvityChange = true;	// �d�͑��u�ɐG��Ă��܂���
			}
			break;

			// �d�͑��u�ɐG��Ă��܂���
			m_bIsTouchGrvityChange = false;	// �t���O��"false"�ɃZ�b�g

		default:
			break;
		}

	}

}

//****************************************************
// ����		�F �}�b�v�`�b�v�Ƃ̓����蔻����Ƃ�A���W�̒������s��
// ����		�F �}�b�v�`�b�v���, ���݂̍��W, �ړ��O�̍��W, ���W�������s�����ǂ����̃t���O
// �߂�l	�F �y������z���������`�b�v�̔ԍ��@�@�y�O��z�u-1�v
//****************************************************
//int HitCheckMapchip(CMapchip Mapchip, D3DXVECTOR2* CurrentPos, D3DXVECTOR2 OldPos, D3DXVECTOR2 HalfObjectSize)
int HitCheckMapchip(CMapchip Mapchip, D3DXVECTOR2* CurrentPos, D3DXVECTOR2 OldPos, bool Flag)
{
	int nCurX, nCurY, nCurNo;
	int nOldX, nOldY, nOldNo;

	// ���݂̍��W�̃`�b�v�ԍ��ƁA�}�b�v�`�b�v���W�n�ł̈ʒu�����߂�
	nCurNo = Mapchip.GetMapchipNo(*CurrentPos, &nCurX, &nCurY);	// �ړ���̏��
	nOldNo = Mapchip.GetMapchipNo(OldPos, &nOldX, &nOldY);		// �ړ��O�̏��

	// �`�b�v�Ɠ������Ă��邩����
	// �ړ���̍��W�ɂ���}�b�v�`�b�v�ԍ����A�����蔻�葮���������Ă����� �� �������Ă���
	if (MAPCHIP_HIT_min <= nCurNo && nCurNo <= MAPCHIP_HIT_MAX)	// �ړ���̍��W�ɂ���}�b�v�`�b�v�ԍ����A�uMAPCHIP_HIT_min�v�ƁuMAPCHIP_HIT_MAX�v�̊Ԃ̂Ƃ�
	{	// �}�b�v�`�b�v�Ɠ������Ă��鎞�̏���
		//========= 1.���W�𒲐�
		if(Flag)	// ���W�������s���t���O�������Ă�����A���W�������s��
		{
			// x��
			if ( (nCurX - nOldX) != 0)
			{
				// �܂��́A�`�b�v �� �ړ��O���W(�v���C���[) �̈ʒu�֌W�𒲂ׂ�
				int isLeft = (nOldX < nCurX);	// �ړ��O���W�������ɂ���Ƃ��́u1�v�ɂȂ�
	
				if (isLeft)
				{	// �ړ��O���W�������̎�
				//	CurrentPos->x = (Mapchip.GetMapchipSize().x * nCurX) - HalfObjectSize.x;
					CurrentPos->x = (Mapchip.GetMapchipSize().x * nCurX);			// ���W�����i�����o�������j

					/* ��̖��߂������ƁA�����[�v���ɁAisLeft=0����ƂȂ�A����ʂ����Ⴄ */
					CurrentPos->x -= 1.0f;		// ������΍�́A��肽���Ȃ����ǉ��}���u
				}
				else
				{
				//	CurrentPos->x = (Mapchip.GetMapchipSize().x * (nCurX + 1)) + HalfObjectSize.x;
					CurrentPos->x = (Mapchip.GetMapchipSize().x * (nCurX + 1) );	// ���W�����i�����o�������j
				}
			}

			// y��
			if ( (nCurY - nOldY) != 0)
			{
				// �܂��́A�`�b�v �� �ړ��O���W(�v���C���[) �̈ʒu�֌W�𒲂ׂ�
				int isTop = (nOldY < nCurY);	// �ړ��O���W���㑤�ɂ���Ƃ��́u1�v�ɂȂ�

				if (isTop)
				{	// �ړ��O���W�������̎�
				//	CurrentPos->y = (Mapchip.GetMapchipSize().y * nCurY) - HalfObjectSize.y;
					CurrentPos->y = (Mapchip.GetMapchipSize().y * nCurY);		// ���W�����i�����o�������j

					/* ��̖��߂������ƁA�����[�v���ɁAisTop =0 ����ƂȂ�A����ʂ����Ⴄ */
					CurrentPos->y -= 0.5f;		// ������΍�́A��肽���Ȃ����ǉ��}���u
				}
				else
				{
				//	CurrentPos->y = (Mapchip.GetMapchipSize().y * (nCurY + 1)) + HalfObjectSize.y;
					CurrentPos->y = (Mapchip.GetMapchipSize().y * (nCurY + 1));	// ���W�����i�����o�������j
				}
			}
		}

		//========= 2.���������`�b�v�̔ԍ���Ԃ�
		return nCurNo;
	}

	// �������Ă��Ȃ����@�� �u-1�v��Ԃ�
	return (-1);
}



//=============================================================================
// �Q�b�^�[�֐�
//=============================================================================
// �X�N���[�����W�̃Z�b�g
D3DXVECTOR2 CModeGame::GetScrollPosition()
{
	return m_vScrollPos;
}

// �}�b�v�`�b�v�ւ̃A�N�Z�X
CMapchip* CModeGame::GetMapchip()
{
	return &m_Mapchip;	// �}�b�v�`�b�v�̏���Ԃ�
}

// �d�͕����̎擾
int CModeGame::GetGravityDirection()
{
	return m_GravityDirection;
}

//=============================================================================
// �Z�b�^�[�֐�
//=============================================================================
// �X�N���[�����W�̎擾
void CModeGame::SetScrollPosition(D3DXVECTOR2 Pos)
{
	m_vScrollPos = Pos;
}

// �Q�[���S�̂̏d�͂̕������Z�b�g
void CModeGame::SetGravityDirection(int Direction)
{
	// �d�͏����N���X���p�����Ă���S�ẴI�u�W�F�N�g�́A�d�͕����̌�����ύX
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (!m_Player->GetPlayerUseFlag()) return;	// �v���C���[�����g�p�Ȃ�s��Ȃ�
		m_Player[i].SetGravityObjectDirection(Direction);	// �v���C���[�̏d�͕������Z�b�g
	}
	
}

#endif // GAMEMODE_CLASS





// �\���̊Ǘ�
#ifdef GAMEMODE_STRUCT

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void CheckHit(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//static int	g_ViewPortType_Game = TYPE_FULL_SCREEN;

static bool	g_bPauseFlag = false;				// �|�[�YON/OFF
static D3DXVECTOR2 g_vScrollPos = ZERO_VECTOR2;	// �X�N���[�����W

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGame(void)
{
//	g_ViewPortType_Game = TYPE_FULL_SCREEN;

	// �X�N���[�����W�̏�����
	g_vScrollPos = ZERO_VECTOR2;

	// �w�i�̏���������
	InitBg();

	// �v���C���[�̏�����
	InitPlayer();

	// �G�l�~�[�̏�����
	InitEnemy();

	// �e�̏�����
//	InitBullet();

	// �X�R�A�̏�����
//	InitScore();

	// �p�[�e�B�N���̏�����
//	InitParticle();

	// BGM�Đ�
//	PlaySound(SOUND_LABEL_BGM_sample001);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	// �p�[�e�B�N���̏I������
//	UninitParticle();

	// �X�R�A�̏I������
//	UninitScore();

	// �e�̏I������
//	UninitBullet();

	// �G�l�~�[�̏I������
	UninitEnemy();

	// �v���C���[�̏I������
	UninitPlayer();

	// �w�i�̏I������
	UninitBg();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	//------------------- �L�[�E�Q�[���p�b�g�ł̓��͂Ŏ��̃��[�h��
	if (KEY_MODE_CHANGE)
	{// Enter��������A�X�e�[�W��؂�ւ���
		SetFade(FADE_OUT, NEXT_MODE);	// �t�F�[�h���Ď��̃��[�h��
	//	SetMode(NEXT_MODE);				// ���̃��[�h�ɃV�[���J��
	}
	// �Q�[���p�b�h�œ��͏���
	else if (PAD_MODE_CHANGE)
	{
		SetFade(FADE_OUT, NEXT_MODE);	// �t�F�[�h���Ď��̃��[�h��
	//	SetMode(NEXT_MODE);				// ���̃��[�h�ɃV�[���J��
	}

	// �|�[�Y�t���O��true�Ȃ珈�����s��Ȃ��B
	if(g_bPauseFlag == true) return;

	// �v���C���[�̍X�V����
	UpdatePlayer();

	// �G�l�~�[�̍X�V����
	UpdateEnemy();

	// �e�̍X�V����
//	UpdateBullet();

	// �p�[�e�B�N���̍X�V����
//	UpdateParticle();

	// �����蔻�菈��
	CheckHit();

	// �X�R�A�̍X�V����
//	UpdateScore();

	// �w�i�̍X�V����
	UpdateBg();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame(void)
{
	// �w�i�̕`�揈��
	DrawBg();

	// �e�X�g�摜�\��
//	DrawPolygon();

	// �G�l�~�[�̕`�揈��
	DrawEnemy();

	// �v���C���[�̕`�揈��
	DrawPlayer();

	// �e�̕`�揈��
//	DrawBullet();

	// �p�[�e�B�N���̕`�揈��
//	DrawParticle();

	// �X�R�A�̕`�揈��
//	DrawScore();
}

//=============================================================================
// �����蔻�菈��
//=============================================================================
void CheckHit(void)
{
	//ENEMY *enemy = GetEnemy();		// �G�l�~�[�̃|�C���^�[��������
	//PLAYER *player = GetPlayer();	// �v���C���[�̃|�C���^�[��������
	//BULLET *bullet = GetBullet();	// �e�̃|�C���^�[��������

	// �G�ƃv���C���[�L����
	//for (int i = 0; i < MAX_ENEMY; i++)
	//{
	//	//�G�̗L���t���O���`�F�b�N����
	//	if (enemy[i].use == false)
	//		continue;

	//	//BC�̓����蔻��
	//	if (CollisionBC(GetPlayer()->pos, enemy[i].pos,
	//		player->rsize, enemy[i].rsize))
	//	{
	//		// �G�L�����N�^�[�͓|�����
	//		enemy[i].use = false;
	//		ReleaseShadow(enemy[i].shadowIdx);
	//	}
	//}

	// �v���C���[�̒e�ƓG
	//for (int i = 0; i < MAX_BULLET; i++)
	//{
	//	//�e�̗L���t���O���`�F�b�N����
	//	if (bullet[i].use == false)
	//		continue;

	//	// �G�Ɠ������Ă邩���ׂ�
	//	for (int j = 0; j < MAX_ENEMY; j++)
	//	{
	//		//�G�̗L���t���O���`�F�b�N����
	//		if (enemy[j].use == false)
	//			continue;

	//		//BC�̓����蔻��
	//		if (CollisionBC(bullet[i].pos, enemy[j].pos,
	//			bullet[i].fWidth, enemy[j].rsize))
	//		{
	//			// �����������疢�g�p�ɖ߂�
	//			bullet[i].use = false;
	//			ReleaseShadow(bullet[i].shadowIdx);

	//			// �G�L�����N�^�[�͓|�����
	//			enemy[j].use = false;
	//			ReleaseShadow(enemy[j].shadowIdx);

	//			// �X�R�A�𑫂�
	//			AddScore(10);
	//		}
	//	}

	//}


	// �G�l�~�[���S�����S�������ԑJ��
	//int enemy_count = 0;
	//for (int i = 0; i < MAX_ENEMY; i++)
	//{
	//	if (enemy[i].use == false) continue;
	//	enemy_count++;
	//}

	// �G�l�~�[���O�C�H
	//if (enemy_count == 0)
	//{
	//	SetFade(FADE_OUT, MODE_RESULT);
	//}

}



//=============================================================================
// �Q�b�^�[�֐�
//=============================================================================
// �X�N���[�����W�̎擾
void SetScrollPosition(D3DXVECTOR2 Pos)
{
	g_vScrollPos = Pos;
}



//=============================================================================
// �Z�b�^�[�֐�
//=============================================================================
// �X�N���[�����W�̃Z�b�g
D3DXVECTOR2* GetScrollPosition()
{
	return &g_vScrollPos;
}

#endif // GAMEMODE_STRUCT
