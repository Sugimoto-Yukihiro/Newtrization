//=============================================================================
//
// �G�l�~�[���� [enemy.cpp]
// Author : ��_�C��Y
//
//=============================================================================
#include "enemy.h"
#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_WIDTH				(128)	// �L�����T�C�Y
#define TEXTURE_HEIGHT				(192)	// 
#define TEXTURE_MAX					(1)		// �e�N�X�`���̐�

#define TEXTURE_PATTERN_DIVIDE_X	(6)		// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y	(1)		// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define ANIM_WAIT					(4)		// �A�j���[�V�����̐؂�ւ��Wait�l


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;		// ���_���
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

static char *g_TexturName[] = {
	"data/TEXTURE/enemy/enemy01.png",
};

static ENEMY g_Enemy[ENEMY_MAX];							// �G�l�~�[�\����

// �G�l�~�[�̐��`�ړ��p�̈ړ����W�e�[�u��
static D3DXVECTOR3 g_MoveTbl[] = {
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	D3DXVECTOR3(200.0f, 0.0f, 0.0f),
	D3DXVECTOR3(200.0f, 200.0f, 0.0f),
};

// �G�l�~�[�̐��`�ړ��p�̈ړ��X�s�[�h�e�[�u��
static float g_MoveSpd[] = {
	0.01f,
	0.01f,
	0.01f,
};


//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(void)
{
	ID3D11Device *pDevice = GetDevice();

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


	// �G�l�~�[�\���̂̏�����
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		g_Enemy[i].use   = true;
		g_Enemy[i].w     = TEXTURE_WIDTH;
		g_Enemy[i].h     = TEXTURE_HEIGHT;
		g_Enemy[i].pos   = D3DXVECTOR3(200.0f+i*150, 300.0f, 0.0f);
		g_Enemy[i].rot   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[i].texNo = 0;

		g_Enemy[i].countAnim = 0;
		g_Enemy[i].patternAnim = 0;

		g_Enemy[i].time = 0.0f;

	}
	

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
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
void UpdateEnemy(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].use == true)		// ���̃G�l�~�[���g���Ă���H
		{								// Yes
			// �A�j���[�V����  
			g_Enemy[i].countAnim++;
			if ((g_Enemy[i].countAnim % ANIM_WAIT) == 0)
			{
				// �p�^�[���̐؂�ւ�
				g_Enemy[i].patternAnim = (g_Enemy[i].patternAnim + 1) % ANIM_PATTERN_NUM;
			}

			if (i == 0)
			{	// �G�l�~�[�O�Ԃ����e�[�u���ɏ]���č��W�ړ��i���`�ړ��j
				int nowNo = (int)g_Enemy[i].time;		// �������ł���e�[�u�������o���Ă���
				int maxNo = (sizeof(g_MoveTbl) / sizeof(D3DXVECTOR3));	// �o�^�e�[�u�����𐔂��Ă���
				int nextNo = (nowNo + 1) % maxNo;						// �ړ���e�[�u���̔ԍ������߂Ă���
				D3DXVECTOR3 pos = g_MoveTbl[nextNo] - g_MoveTbl[nowNo];	// XYZ�ړ��ʂ��v�Z���Ă���
				float nowTime = g_Enemy[i].time - nowNo;				// ���ԕ����ł��鏭�������o���Ă���
				pos *= nowTime;											// ���݂̈ړ��ʂ��v�Z���Ă���

				// �v�Z���ċ��߂��ړ��ʂ����݂̈ړ��e�[�u��XYZ�ɑ����Ă���
				g_Enemy[i].pos = g_MoveTbl[nowNo] + pos;

				g_Enemy[i].time += g_MoveSpd[nowNo];					// ���Ԃ�i�߂Ă���
				if ((int)g_Enemy[i].time >= maxNo)						// �o�^�e�[�u���Ō�܂ňړ��������H
				{
					g_Enemy[i].time -= maxNo;							// �O�ԖڂɃ��Z�b�g�������������������p���ł���
				}

			}
		}
	}



#ifdef _DEBUG	// �f�o�b�O����\������
	//char *str = GetDebugStr();
	//sprintf(&str[strlen(str)], " EX:%.2f EY:%.2f", g_Enemy[0].Pos.x, g_Enemy[0].Pos.y);
	
#endif

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
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

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].use == true)		// ���̃G�l�~�[���g���Ă���H
		{								// Yes
			// �e�N�X�`���ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_Enemy[i].texNo]);

			//�G�l�~�[�̈ʒu��e�N�X�`���[���W�𔽉f
			float px = g_Enemy[i].pos.x;	// �G�l�~�[�̕\���ʒuX
			float py = g_Enemy[i].pos.y;	// �G�l�~�[�̕\���ʒuY
			float pw = g_Enemy[i].w;		// �G�l�~�[�̕\����
			float ph = g_Enemy[i].h;		// �G�l�~�[�̕\������

			float tw = 1.0f / TEXTURE_PATTERN_DIVIDE_X;	// �e�N�X�`���̕�
			float th = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;	// �e�N�X�`���̍���
			float tx = (float)(g_Enemy[i].patternAnim % TEXTURE_PATTERN_DIVIDE_X) * tw;	// �e�N�X�`���̍���X���W
			float ty = (float)(g_Enemy[i].patternAnim / TEXTURE_PATTERN_DIVIDE_X) * th;	// �e�N�X�`���̍���Y���W

			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			SetSpriteColorRotation(g_VertexBuffer, px, py, pw, ph, tx, ty, tw, th,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				g_Enemy[i].rot.z);

			// �|���S���`��
			GetDeviceContext()->Draw(4, 0);
		}
	}

}


//=============================================================================
// �G�l�~�[�\���̂̐擪�A�h���X���擾
//=============================================================================
ENEMY *GetEnemy(void)
{
	return &g_Enemy[0];
}


