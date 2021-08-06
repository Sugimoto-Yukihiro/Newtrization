//=============================================================================
//
// �f�o�b�O�\������ [debugproc.cpp]
// Author : ��_�C��Y
//
//=============================================================================
#include <stdio.h>
#include "debugproc.h"
#include "renderer.h"

#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
char		g_aStrDebug[1024] = {"\0"};	// �f�o�b�O���


//=============================================================================
// �f�o�b�O�\�������̕`�揈��
//=============================================================================
void DrawDebugProc(void)
{
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

	DebugTextOut(g_aStrDebug, 0, 0);

	// ���N���A
	memset(g_aStrDebug, 0, sizeof g_aStrDebug);
}

//=============================================================================
// �f�o�b�O�\���̓o�^
//=============================================================================
void PrintDebugProc(char *fmt,...)
{
#if 0
	long *pParam;
	static char aBuf[256];

	pParam = (long*)&fmt;
	sprintf(aBuf, fmt, pParam[1], pParam[2], pParam[3], pParam[4],
									pParam[5], pParam[6], pParam[7], pParam[8],
									pParam[9], pParam[10], pParam[11], pParam[12]);
#else
	va_list list;			// �ψ�������������ׂɎg�p����ϐ�
	char *pCur;
	char aBuf[256]={"\0"};
	char aWk[32];

	// �ψ����ɃA�N�Z�X����O�̏�������
	va_start(list, fmt);

	pCur = fmt;
	for( ; *pCur; ++pCur)
	{
		if(*pCur != '%')
		{
			sprintf_s(aWk, "%c", *pCur);
		}
		else
		{
			pCur++;

			switch(*pCur)
			{
			case 'd':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf_s(aWk, "%d", va_arg(list, int));
				break;

			case 'f':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf_s(aWk, "%.2f", va_arg(list, double));		// double�^�Ŏw��
				break;

			case 's':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf_s(aWk, "%s", va_arg(list, char*));
				break;

			case 'c':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf_s(aWk, "%c", va_arg(list, char));
				break;

			default:
				sprintf_s(aWk, "%c", *pCur);
				break;
			}
		}
		strcat_s(aBuf, aWk);
	}

	// �ψ����ɃA�N�Z�X������̏I������
	va_end(list);

	// �A��
	if((strlen(g_aStrDebug) + strlen(aBuf)) < ((sizeof g_aStrDebug) - 1))
	{
		strcat_s(g_aStrDebug, aBuf);
	}
#endif
}


// �f�o�b�N�̕��͂̃Z�b�g
void SetDebugString(void)
{
	// �Q�[�����[�h�̏����擾
	CModeGame GameInf = *GetGame();				// �Q�[�����[�h�N���X�̏����擾
	CPlayer PlayerInf = *GameInf.GetPlayer();	// �v���C���[�̏����擾

	{
		PrintDebugProc("�X�N���[�����W X: %f  Y: %f\n", GameInf.GetScrollPosition().x, GameInf.GetScrollPosition().y);

		PrintDebugProc("�@�d�͂̕��� :");
		if (GameInf.GetGravityDirection() == GRAVITY_DEFAULT) 	PrintDebugProc("�@������\n");
		if (GameInf.GetGravityDirection() == GRAVITY_LEFT)		PrintDebugProc("�@������\n");

		PrintDebugProc("playerAnimIdx : %d\n", PlayerInf.GetCurrentAnim());
		PrintDebugProc("Player���W�@X:%f Y:%f\n", PlayerInf.GetPosition().x, PlayerInf.GetPosition().y);
		PrintDebugProc("�v���C���[���W�̃}�b�v�`�b�v : %d\n", GameInf.GetMapchip()->GetMapchipNo(PlayerInf.GetPosition()) );

		PrintDebugProc("�v���C���[�̃W�����v�l�F %f�@�@�d�͒l�F %f\n", PlayerInf.GetJumpForce(), PlayerInf.GetGravitySpeed());
		PrintDebugProc("�y�v���C���[�̊e�^�U�l�z����F %d�@�_�b�V���F %d�@�W�����v�F %d�@�ڒn�F %d�@\n",
						PlayerInf.GetIsMove(), PlayerInf.GetIsDush(), PlayerInf.GetIsJump(), PlayerInf.GetIsGround()  );
	}


//	char *str = GetDebugStr();
//	sprintf(&str[strlen(str)], " PX:%f PY:%f", GameInf.GetPlayer()->GetPosition().x, GameInf.GetPlayer()->GetPosition().y);

}

