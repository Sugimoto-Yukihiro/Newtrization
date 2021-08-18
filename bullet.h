//==================================================================
//
// バレット処理 [bullet.cpp]
// Auther : 杉本幸宏
//
//==================================================================
#pragma once

#include "texture.h"

//*****************************************************************************
// enum
//*****************************************************************************


//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBullet
{
public:
	CBullet();	// コンストラクタ
	~CBullet();	// デストラクタ

	void Init(char* pTextureName = NULL, int TexDivX = 1, int TexDivY = 1, int AnimWait = 0);	// 初期化処理
	void Uninit();						// 終了処理
	void Update();						// 更新処理
	void Draw(D3DXVECTOR2 ScrollPos);	// 描画処理

	bool SetBullet(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, D3DXVECTOR2 Move, float Attack, float HP);
	bool UnsetBullet();	// 使用しているバレットの解放


	//------------------- セッター関数
	void SetPosition(D3DXVECTOR2 Pos) { m_Position = Pos; };	// バレットの位置をセット
	void SetSize(D3DXVECTOR2 Size) { m_TexBullet.SetTexSize(Size); };			// バレットの大きさをセット
	void SetMove(D3DXVECTOR2 Move) { m_Move = Move; };			// バレットの移動量をセット
	void SetAttack(float Attack) { m_fAttack = Attack; };		// バレットの攻撃力をセット
//	void SetHP(float HP) { m_fHitPoint = HP; } ;				// バレットのHPを取セット
//	void SetBulletType(int Type) { m_nBulletType = Type; } ;	// バレットの種類をセット


	//------------------- ゲッター関数
	D3DXVECTOR2 GetPosition() { return m_Position; };	// バレットの位置を取得
	D3DXVECTOR2 GetSize() { return m_TexBullet.GetTexSize(); };		// バレットの大きさを取得
	D3DXVECTOR2 GetMove() { return m_Move; };			// バレットの移動量を取得
	float GetAttack() { return m_fAttack; };			// バレットの攻撃力を取得
//	float GetHP() { return m_fHitPoint; } ;				// バレットのHPを取得
//	int GetBulletType() { return m_nBulletType; } ;		// バレットの種類を取得
	bool GetUseFlag() { return m_bUse; };				// バレットの使用フラグを取得


private:
	ID3D11ShaderResourceView	*m_Texture;	// テクスチャ情報
	CTexture		m_TexBullet;	// テクスチャクラスのインスタンス
	D3DXVECTOR2		m_Position;		// バレットの座標
//	D3DXVECTOR2		m_Size;			// バレットの大きさ
	D3DXVECTOR2		m_Move;			// バレットの1フレーム当たりの移動量
	float			m_fAttack;		// バレットの攻撃力
//	float			m_fHitPoint;	// バレットのHP
//	int				m_nBulletType;	// バレットの種類
	bool			m_bUse;			// バレットの使用フラグ
};



