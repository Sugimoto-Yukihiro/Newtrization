//=============================================================================
//
// 当たり判定処理 [collision.h]
// Author : 杉本幸宏
//
//=============================================================================
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CollisionBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2);
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float radius1, float radius2);
bool CollisionBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float radius1, float radius2);

float dotProduct(D3DXVECTOR3 *v1, D3DXVECTOR3 *v2);
void crossProduct(D3DXVECTOR3 *ret, D3DXVECTOR3 *v1, D3DXVECTOR3 *v2);
bool RayCast(D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 *hit, D3DXVECTOR3 *normal);
