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
//#include "camera.h"		// �J��������
#include "collision.h"	// �Փ˔���
#include "fade.h"		// �t�F�[�h
#include "input.h"		// �L�[�E�Q�[���p�b�h���͏���
#include "sound.h"		// �T�E���h

#include "debugproc.h"	// �f�o�b�O�\��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NEXT_MODE		MODE_RESULT		// ���̃��[�h

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************



//=============================================================================
// ����������
//=============================================================================
void CModeGame::Init()
{
	//------------------- �����o�ϐ��̏�����
	m_vScrollPos = ZERO_VECTOR2;			// �X�N���[�����W�̏�����
	m_GravityDirection = GRAVITY_DEFAULT;	// �d�͕����̏�����
	m_bIsTouchGrvityChange = false;			// "false"�i�G���W���ɐG��Ă��Ȃ��j�ŏ�����
	m_nFlameCnt = 0;						// �o�߃t���[������������
#ifdef _DEBUG
	// �|�[�Y�t���O�̏�����
	m_bPauseFlag = false;		// "false"�i�{�[�Y�����j�ŏ�����
	m_bMapchipDebug = false;	// "false"�i�}�b�v�`�b�v�̃f�o�b�O�\�������j�ŏ�����
#endif // _DEBUG

	//------------------- �ȍ~�A�Q�[�����[�h�N���X���̃C���X�^���X�̏�����
	// �w�i�̏�����
	InitBg();

	// UI�̏�����
	m_GameUI.Init();

	// �v���C���[�̏�����
	CreatePlayerTexture();	// �e�N�X�`���E���_�o�b�t�@����
	m_Player.Init(FIREBOOTS_BULLET_TEXNAME);	// �������������s

	// �}�b�v�`�b�v�̏�����
	m_Mapchip.Init(TEXTURE_NAME_MAPCHIP, NULL, MAPCHIP_TEXTURE_DIVIDE_X, MAPCHIP_TEXTURE_DIVIDE_Y, MAPCHIP_SIZE_DEFAULT);		// �������������s
#ifdef _DEBUG
	// �f�o�b�O�\���p�}�b�v�`�b�v�̏�����
	m_DebugMapchip.Init(TEXTURE_NAME_MAPCHIP_DEBUG, NULL, MAPCHIP_DEBUG_TEXTURE_DIVIDE_X, MAPCHIP_DEBUG_TEXTURE_DIVIDE_Y, MAPCHIP_SIZE_DEFAULT);		// �������������s
#endif // _DEBUG

	// �G�l�~�[�̏�����
	InitEnemy();	// �e�N�X�`������
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		m_Enemy[i].Init();		// �G�l�~�[�̐������Ăяo���}��
	}

	// �e�̏�����
//	InitBullet();

	// �X�R�A�̏�����
	m_Score.Init(SCORE_TEX_NAME, SCORE_DRAW_SIZE);

	// ��ʒ[�̏�����
	m_SideBlack.Init(TEXTURE_NAME_SIDEBLACK);

	// ���͉����̏�����
	for (int i = 0; i < FURYOKU_MAX; i++)
	{
		// ������
		m_FloatForceArea[i].Init(FURYOKU_TEX_NAME);
	}

	// �I�u�W�F�N�g�̔z�u & �}�b�v�`�b�v�̃Z�b�g
	PutAllObject(GAME_MAP_DATA_1);



	//------------------- �v���C���[�̈ʒu�����܂�������A�X�N���[�����W���Z�b�g
	{
		D3DXVECTOR2 pos = ZERO_VECTOR2;	// �ꎞ�I�ȕϐ�
		pos.x = m_Player.GetPosition().x - SCROLL_SET_X;	// �X�N���[�����W<x>�ɒl����
		pos.x = (pos.x < 0.0f) ? 0.0f : pos.x;	// �X�N���[�����W<x>�����Ȃ�u0�v�Ƀ��Z�b�g�A���̐��Ȃ炻�̂܂�
		pos.x = (pos.x + SCREEN_WIDTH > m_Mapchip.GetMapChipSize().x) ? m_Mapchip.GetMapChipSize().x - SCREEN_WIDTH : pos.x;	// ��ʉE��̓_�����[���h�̒[�ɗ�����"STAGE_W"�̒l�Ƀ��Z�b�g

		pos.y = m_Player.GetPosition().y - SCROLL_SET_Y;	// �X�N���[�����W<y>�ɒl����
		pos.y = (pos.y < 0.0f) ? 0.0f : pos.y;	// �X�N���[�����W<y>���Ȃ�u0�v�Ƀ��Z�b�g�A���̐��Ȃ炻�̂܂�
		pos.y = (pos.y + SCREEN_HEIGHT > m_Mapchip.GetMapChipSize().y) ? m_Mapchip.GetMapChipSize().y - SCREEN_HEIGHT : pos.y;	// ��ʉE��̓_�����[���h�̒[�ɗ�����"STAGE_H"�̒l�Ƀ��Z�b�g

		// ���W���Z�b�g
		m_vScrollPos = pos;
	}

	// BGM�Đ�
//	PlaySound(SOUND_LABEL_BGM_sample001);
}



//=============================================================================
// �I������
//=============================================================================
void CModeGame::Uninit(void)
{
	// BGM��~
//	StopSound();

	// ���͉����G���A�̏I������
	for (int i = 0; i < FURYOKU_MAX; i++)
	{
		m_FloatForceArea[i].Uninit();	// �I��
	}

	// ��ʒ[�̏I������
	m_SideBlack.Uninit();

	// �X�R�A�̏I������
	m_Score.Uninit();

	// �e�̏I������
//	UninitBullet();

#ifdef _DEBUG
	// �f�o�b�O�\���p�}�b�v�`�b�v�̏I������
	m_DebugMapchip.Uninit();
#endif // _DEBUG

	// �}�b�v�`�b�v�̏I������
	m_Mapchip.Uninit();		// �I���������s

	// �G�l�~�[�̏I������
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		m_Enemy[i].Uninit();		// �G�l�~�[�̐������Ăяo���}��
	}
	UninitEnemy();

	// �v���C���[�̏I������
	ReleasePlayerTexture();	// �e�N�X�`�����
	m_Player.Uninit();		// �I���������s

	// UI�̏I������
	m_GameUI.Uninit();

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
	if( KEY_PAUSE ) m_bPauseFlag = (m_bPauseFlag) ? false : true;
								//  m_bPauseFlag�́H  "true"�Ȃ�"false" ��  :  "false"�Ȃ�"true" ��  �Z�b�g����
	// �|�[�Y�t���O��true�Ȃ珈�����s��Ȃ��B
	if (m_bPauseFlag) return;

	// �}�b�v�`�b�v�̃f�o�b�O�\���L�[�������ꂽ�Ƃ�
	if (KEY_MAPCHIP_DEBUG) m_bMapchipDebug = (m_bMapchipDebug) ? false : true;

	// ���X�^�[�g�̃L�[�������ꂽ�Ƃ�
	if (KEY_RESTART_GAMEMODE)
	{
		CModeGame::Uninit();	// �Q�[�����[�h�̉��
		CModeGame::Init();		// �Q�[�����[�h�̏�����
	}
	// �d�͕����̕ύX
	if (KEY_CHANGE_GRAVITY)
	{
		m_GravityDirection = (m_GravityDirection + 1) % GRAVITY_DIRECTION_MAX;
		ChangeGravityDirection(m_GravityDirection);
	}
#endif // _DEBUG

#ifdef KEY_MODE_CHANGE
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
#endif // KEY_MODE_CHANGE

	// �o�߃t���[�������J�E���g
	m_nFlameCnt++;

	// �}�b�v�`�b�v�̍X�V����
	m_Mapchip.Update();

#ifdef _DEBUG
	// �f�o�b�O�\���p�}�b�v�`�b�v�̍X�V����
	if (m_bMapchipDebug) m_DebugMapchip.Update();
#endif // _DEBUG


	// �v���C���[�̍X�V����
	m_Player.Update();	// �v���C���[�̍X�V�������s

	// �G�l�~�[�̍X�V����
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		m_Enemy[i].Update(m_Mapchip);		// �G�l�~�[�̐������Ăяo���}��
	}

	// ��ʒ[�̍X�V����
	m_SideBlack.Update();

	// ���͉����̍X�V����
	for (int i = 0; i < FURYOKU_MAX; i++)
	{
		m_FloatForceArea[i].Update();
	}

	//-------------------  �����蔻�菈��
	CollisionCheck();

	/* �����蔻��̌��ʂɂ���ē��e���ς��X�V�����͂���ȍ~�ɋL�ڂ���I */

	// �X�R�A�̍X�V����
	m_Score.Update(m_nFlameCnt);

	// �w�i�̍X�V����
	UpdateBg();

	// UI�̍X�V����
	m_GameUI.Update();

	// �v���C���[��HP��0�ȉ��ɂȂ�����I��
	if (m_Player.GetCurrentHP() < 0.0f) SetFade(FADE_OUT, NEXT_MODE);

}



//=============================================================================
// �`�揈��
//=============================================================================
void CModeGame::Draw()
{
	// �`��O�̏����������s
	PresetDraw2D();

	// �w�i�̕`�揈��
	DrawBg();

	// ���͉����G���A�̕`�揈��
	for (int i = 0; i < FURYOKU_MAX; i++)
	{
		m_FloatForceArea[i].Draw(m_vScrollPos);
	}

	// �}�b�v�`�b�v�̕`�揈��
	m_Mapchip.Draw(m_vScrollPos);

#ifdef _DEBUG
	// �f�o�b�O�\���p�}�b�v�`�b�v�`�揈��
	if (m_bMapchipDebug) m_DebugMapchip.Draw(m_vScrollPos);
#endif // _DEBUG

	// �G�l�~�[�̕`�揈��
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		m_Enemy[i].Draw(m_vScrollPos);		// �G�l�~�[�̐������Ăяo���}��
	}


	// �v���C���[�̕`�揈��
	m_Player.Draw(m_vScrollPos);

	// �X�R�A�̕`�揈��
//	DrawScore();

	// ��ʒ[�̕`��
	m_SideBlack.Draw();	// UI�̑O�ɕ`�悷��

	// UI�̕`�揈��
	m_GameUI.Draw();

	// �X�R�A�̕`��
	m_Score.Draw(SCORE_DRAW_POS_RIGHT);
}



//=============================================================================
// �����蔻�菈��
//=============================================================================
void CModeGame::CollisionCheck()
{
	// �v���C���[�ƃ}�b�v�`�b�v�̓����蔻��
	{
		// �v���C���[���W�̃}�b�v�`�b�v�ԍ����擾
		int nChip_Id = m_Mapchip.GetMapchipNo(m_Player.GetLegPos());

		// ���̔ԍ��ɂ���ď�����ς���
		if (MAPCHIP_POISON_min <= nChip_Id && nChip_Id <= MAPCHIP_POISON_MAX)
		{	// �y�Ŕ���̃}�b�v�`�b�v�ԍ��ɓ������Ă������z
			m_Player.SetPoisonFlag(true);	// �ŏ�Ԃ�true�ɂ���
		}
		else if (MAPCHIP_CANGE_GRAVITY_min <= nChip_Id && nChip_Id <= MAPCHIP_CANGE_GRAVITY_MAX)
		{	// �y�d�͕ύX����z
			// �d�͕����̕ύX
			if (!m_bIsTouchGrvityChange)	// ���߂ďd�͑��u�ɐG�ꂽ���̈�񂾂��s��
			{
				m_GravityDirection = (m_GravityDirection + 1) % GRAVITY_DIRECTION_MAX;	// �d�͂̕�����ύX
				ChangeGravityDirection(m_GravityDirection);	// �d�͕����Z�b�g

				m_bIsTouchGrvityChange = true;	// �d�͑��u�ɐG��Ă��܂���
			}

		}
		else if (MAPCHIP_GOAL_min <= nChip_Id && nChip_Id <= MAPCHIP_GOAL_MAX)
		{	// �y�S�[������z
			RequestGameClear(m_Score.GetScore());	// �Q�[���N���A
		}
		else
		{	// �y�Ȃɂ��������Ă��Ȃ����z
			m_bIsTouchGrvityChange = false;	// �t���O��"false"�ɃZ�b�g
			m_Player.SetPoisonFlag(false);	// �ŏ�Ԃ�false�ɂ���
		}

	}

	// �v���C���[�ƕ��͉����G���A�̓����蔻��
	{
		bool Hit = false;
		for (int i = 0; i < FURYOKU_MAX, !Hit; i++)
		{
			// ���g�p�Ȃ�s��Ȃ�
			if (!m_FloatForceArea[i].GetUseFlag()) return;

			// �v���C���[�̌��݂̍��W���擾
			D3DXVECTOR2 PlayerPos = m_Player.GetPosition();

			// �����蔻����s
			if (m_FloatForceArea[i].HitCheck(&PlayerPos, m_Player.GetSize() * 0.5f))
			{	// �������Ă�����
				// �d�͏����t���O��܂�
				m_Player.SetGravityFlag(false);
				m_Player.SetBouyant(m_FloatForceArea[i].GetForceValue() * m_FloatForceArea[i].GetDirection());	// ���͂��Z�b�g
				Hit = true;	// �������Ă���
			}

			// ���͈ړ���̍��W���Z�b�g
			m_Player.SetPosition(PlayerPos);
		}

		// �ǂ���������Ă��Ȃ���
		if (!Hit)
		{
			// �v���C���[�̌��݂̍��W���擾
			D3DXVECTOR2 PlayerPos = m_Player.GetPosition();

			// ���͈ړ�������
			PlayerPos += m_Player.GetBouyant();

			// ���͈ړ���̍��W���Z�b�g
			m_Player.SetPosition(PlayerPos);
		}

	}


}

//****************************************************
// ����		�F �Q�[���S�̂̏d�͂̕������Z�b�g
// ����		�F �d�͕���
// �߂�l	�F void
//****************************************************
void CModeGame::ChangeGravityDirection(int Direction)
{
	/* �d�͏����N���X���p�����Ă���S�ẴI�u�W�F�N�g�́A�d�͕����̌�����ύX */
	// �v���C���[
	{
		m_Player.SetGravityObjectDirection(Direction);	// �v���C���[�̏d�͕������Z�b�g
		m_Player.SetSize(D3DXVECTOR2(m_Player.GetSize().y, m_Player.GetSize().x));	// �T�C�Y�l�����ւ�

		// �ς���������ɂ���ď����ς���
		if (m_GravityDirection == GRAVITY_LEFT)			// �������֕ς�������̏���
		{
			m_Player.SetTexRotation(D3DXToRadian(0));	// ��]�l���������񃊃Z�b�g
			m_Player.SetTexRotation(D3DXToRadian(90));	// �v���C���[�e�N�X�`����90����]
		}
		else if (m_GravityDirection == GRAVITY_DEFAULT)	// �f�t�H���g�֕ς�������̏���
		{
			m_Player.SetTexRotation(D3DXToRadian(0));	// ��]�l�����Z�b�g
		}

	}



}


//****************************************************
// ����		�F �}�b�v�`�b�v�Ƃ̓����蔻����Ƃ�A���W�̒������s��
// ����		�F �}�b�v�`�b�v���, ���݂̍��W, �ړ��O�̍��W, ���W�������s�����ǂ����̃t���O(X��), ���W�������s�����ǂ����̃t���O(Y��)
// �߂�l	�F �y������z���������`�b�v�̔ԍ��@�@�y�O��z�u-1�v
//****************************************************
int HitCheckMapchip(CMapchip Mapchip, D3DXVECTOR2* CurrentPos, D3DXVECTOR2 OldPos, bool FlagX, bool FlagY)
{
	// ���̊֐����Ŏg�p����ϐ��̐錾

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
		{
			// x��
			if ( (nCurX - nOldX) != 0 && FlagX)	// �����Ȃ��Ƃ��͒�������K�v���Ȃ�
			{
				// �܂��́A�`�b�v �� �ړ��O���W(�v���C���[) �̈ʒu�֌W�𒲂ׂ�
				int isLeft = (nOldX < nCurX);	// �ړ��O���W�������ɂ���Ƃ��́u1�v�ɂȂ�
	
				if (isLeft)
				{	// �ړ��O���W�������̎�
					CurrentPos->x = (Mapchip.GetChipSize().x * nCurX);			// ���W�����i�����o�������j

					/* ��̖��߂������ƁA�����[�v���ɁAisLeft = 0����ƂȂ�A����ʂ����Ⴄ */
					CurrentPos->x -= 0.5f;		// ������΍�́A��肽���Ȃ����ǉ��}���u
				}
				else
				{
					CurrentPos->x = (Mapchip.GetChipSize().x * (nCurX + 1) );	// ���W�����i�����o�������j
				}
			}

			// y��
			if ( (nCurY - nOldY) != 0 && FlagY)	// �����Ȃ��Ƃ��͒�������K�v���Ȃ�
			{
				// �܂��́A�`�b�v �� �ړ��O���W(�v���C���[) �̈ʒu�֌W�𒲂ׂ�
				int isTop = (nOldY < nCurY);	// �ړ��O���W���㑤�ɂ���Ƃ��́u1�v�ɂȂ�

				if (isTop)
				{	// �ړ��O���W���㑤�̎�
					CurrentPos->y = (Mapchip.GetChipSize().y * nCurY);		// ���W�����i�����o�������j

					/* ��̖��߂������ƁA�����[�v���ɁAisTop = 0 ����ƂȂ�A����ʂ����Ⴄ */
					CurrentPos->y -= 0.5f;		// ������΍�́A��肽���Ȃ����ǉ��}���u
				}
				else
				{
					CurrentPos->y = (Mapchip.GetChipSize().y * (nCurY + 1));	// ���W�����i�����o�������j
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
// �I�u�W�F�N�g�̔z�u����
//=============================================================================
/*******************************************************************************
�֐���	:	int PutAllObject(const char* pCsvStr)
����		:	�}�b�v�z��̐擪�A�h���X
�߂�l	:	������1		���s��0
����		:	�S�ẴI�u�W�F�N�g�̃Z�b�g
			�y�}�b�v�`�b�v�f�[�^�������ŃZ�b�g���Ă���z
			�y���Ӂz���̊֐����Ăяo���O�ɁA�S�ẴI�u�W�F�N�g�̏������������s�����ƁI
*******************************************************************************/
int CModeGame::PutAllObject(const char* pCsvMapFile)
{
	// ���̊֐����Ŏg�p����ϐ��̐錾
	char* pLoadedMapData = NULL;	// �}�b�v����Csv�t�@�C���̓ǂݍ��ݐ�
	char* p = NULL;					// strtok_s�p�̃|�C���^
	char* pToken = NULL;			// strtok_s�Œ��o�����g�[�N���������|�C���^
	int nTokenCnt = 0;				// �i�[�����g�[�N���̐����J�E���g����ϐ��i�� �}�b�v�`�b�v�z��̗v�f���j

	// Csv�t�@�C���́A�R�����g�������폜������Ԃ̂��̂�ǂݍ��݁i�J���}�ŋ�؂�ꂽ���l�f�[�^�𒊏o�j
//	if ( LoadCsvFile(pCsvMapFile, pLoadedMapData, 8, ",") < 0)	// �������Ԃ��ꂽ��A�ǂݍ��ݎ��s
	if ( LoadCsvFile(pCsvMapFile, &pLoadedMapData, true) < 0)	// �������Ԃ��ꂽ��A�ǂݍ��ݎ��s
	{	// csv�t�@�C���̃��[�h���s���i�G���[�`�F�b�N�j
		return 0;	// ���s��Ԃ�
	}

	// �}�b�v�`�b�v�f�[�^���Z�b�g
	m_Mapchip.SetMapChipData(pLoadedMapData);
#ifdef _DEBUG
	m_DebugMapchip.SetMapChipData(pLoadedMapData);	// �f�o�b�O�\���p�}�b�v�`�b�v
#endif // _DEBUG


	// �S�ẴI�u�W�F�N�g���Z�b�g
	{
		pToken = strtok_s(pLoadedMapData, ",", &p);			// �J���}�ɋ��܂ꂽ������𒊏o
		do
		{
			// �I�u�W�F�N�g�̐ݒu�L�������������Ƃ��̏���
			if (strrchr(pToken, PLAYER_SYMBOL) != NULL)		// �v���C���[�̐ݒu�L�������݂��邩���ׂ�
			{
				// �v���C���[��ݒu
				m_Player.SetPlayer( m_Mapchip.GetMapchipPosition(nTokenCnt) );	// 'P'�̑��݂���`�b�v�̒��S�Ƀv���C���[���Z�b�g
			}
			else if (strrchr(pToken, ENEMY_SYMBOL) != NULL)	// �G�l�~�[�̐ݒu�L�������݂��邩���ׂ�
			{
				// �G�l�~�[��ݒu
				PutEnemy(m_Mapchip.GetMapchipPosition(nTokenCnt));	// 'E'�̑��݂���`�b�v�̒��S�ɕ��͉����G���A���Z�b�g
			}
			else if (strrchr(pToken, FURYOKU_SYMBOL) != NULL)	// ���͉����̐ݒu�L�������݂��邩���ׂ�
			{
				// ���͉����G���A��ݒu
				PutFloatForceArea( m_Mapchip.GetMapchipPosition(nTokenCnt) );	// 'F'�̑��݂���`�b�v�̒��S�ɕ��͉����G���A���Z�b�g
			}
			else {	// �����Ȃ���

			}

			// �g�[�N�����i���݂̃}�b�v�`�b�v�z��̗v�f���j�̃J�E���g
			nTokenCnt++;

			// ���̕�����̃u���b�N���i�[
			pToken = strtok_s(NULL, ",", &p);
		} while (pToken != NULL);	// ������Ȃ��Ȃ�܂ŌJ��Ԃ�
	}

	return 1;	// ������Ԃ�
}

// �S�ẴI�u�W�F�N�g�̃Z�b�g
//void CModeGame::PutAllObject(char* MapDataFile, int chipTexDivX, int chipTexDivY)
//{
//	char* pLoad = NULL;	// �ǂݍ��ݐ�
//	// Csv�t�@�C���́A�R�����g�������폜������Ԃ̂��̂�ǂݍ��݁i�J���}�ŋ�؂�ꂽ���l�f�[�^�𒊏o�j
//	LoadCsvFile(MapDataFile, pLoad, 8, ",");	// csv�t�@�C���̃��[�h
//	m_Mapchip.SetMapChipData(pLoad);			// �}�b�v�`�b�v�f�[�^���Z�b�g
//
//	// �v���C���[��G�l�~�[�����z�u
//	PutPlayer(pLoad);	// �v���C���[��z�u
////	PutEnemy(pLoad);	// �G�l�~�[��z�u
//
//}

// csv�̃}�b�v�f�[�^����A�v���C���[��z�u����
//void CModeGame::PutPlayer(const char* csvMapData, char Symbol)
//{
//	int X, Y;	// �}�b�v�`�b�v���W�n�ł�,�@�v���C���[�̈ʒu
//	const char* SymbolPlace = NULL;
//	SymbolPlace = strrchr(csvMapData, Symbol);	// �v���C���[�̃V���{�������邩����
//}



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

// �}�b�v�`�b�v�ւ̃A�N�Z�X
CPlayer* CModeGame::GetPlayer()
{
	return &m_Player;	// �v���C���[�̏���Ԃ�
}

// �d�͕����̎擾
int CModeGame::GetGravityDirection()
{
	return m_GravityDirection;	// �Q�[���S�̂̏d�͕����̏���Ԃ�
}

//=============================================================================
// �Z�b�^�[�֐�
//=============================================================================
// �X�N���[�����W�̎擾
void CModeGame::SetScrollPosition(D3DXVECTOR2 Pos)
{
	m_vScrollPos = Pos;
}

//=============================================================================
// �����o�֐��iprivate�j
//=============================================================================
bool CModeGame::PutFloatForceArea(D3DXVECTOR2 Pos)
{
	bool bRet = false;	// �߂�l

	for (int i = 0; i < FURYOKU_MAX; i++)
	{
		// ���̓G���A�̃Z�b�g
		if (m_FloatForceArea[i].SetFloatForceErea(Pos, m_Mapchip.GetChipSize(), FURYOKU_DIRECTION, FURYOKU_FORCE, FURYOKU_TEX_COLOR))
		{	// �Z�b�g�ł�����
			bRet = true;	// �������Z�b�g
			break;			// ���̃��[�v���甲����
		}
	}

	// �Z�b�g�ł����� �� true
	// �ł��Ȃ������� �� false
	return bRet;
}

bool CModeGame::PutEnemy(D3DXVECTOR2 Pos)
{
	bool bRet = false;	// �߂�l

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		// �G�l�~�[�̃Z�b�g
		if ( m_Enemy[i].SetEnemy(Pos, false) )
		{	// �Z�b�g�ł�����
			bRet = true;	// �������Z�b�g
			break;			// ���̃��[�v���甲����
		}
	}

	// �Z�b�g�ł����� �� true
	// �ł��Ȃ������� �� false
	return bRet;
}
