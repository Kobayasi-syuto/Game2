#include "CSceneGame.h"
#include "CTexture.h"
#include "CMap.h"
#include "CKey.h"
#include "CRectangle.h"
#include "CBullet.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CText.h"

void CSceneGame::Init() {
	//シーンの設定
	mScene = EGAME;

	Texture.Load("Image.tga");
	//文字画像の読み込み
	CText::mFont.Load("font.tga");

	//クラスのメンバ変数への代入
	CPlayer *Player = new CPlayer();
	Player->x = 150;
	Player->y = 150;
	Player->w = 25;
	Player->h = 25;
	Player->mEnabled = true;

	int map[8][9] =
	{
		{ 1, 1, 1, 1, 1, 1, 1, 1,1},
		{ 0, 0, 0, 0, 0, 0, 0, 0,1},
		{ 1, 0, 1, 1, 1, 0, 1, 0,1},
		{ 1, 0, 1, 0, 0, 1, 0, 1,1},
		{ 1, 0, 1, 1, 0, 0, 0, 0,1},
		{ 1, 0, 0, 0, 1, 0, 1, 0,1},
		{ 1, 0, 1, 0, 0, 0, 1, 0,0},
		{ 1, 1, 1, 1, 1, 1, 1, 1,1},
	};

	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < 9; i++) {
			//mapの要素が1の時、四角形配置
			if (map[j][i] == 1) {
				CMap *Map = new CMap();
				//四角形に値を設定
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 50;
			}
			else if (map[j][i] == 2) {
				CEnemy *Enemy = new CEnemy();
				Enemy->x = i * 100 - 350;
				Enemy->y = j * -100 + 250;
				//右へ移動
				Enemy->mFx = 0;
				Enemy->mFy = 1;
			}
		}
	}
}

void CSceneGame::Update() {
	/*
	配列の要素分繰り返す
	配列名.size()
	配列の要素数を取得する
	*/
	for (int i = 0; i < VectorRect.size(); i++) {
		/*
		配列の参照
		配列名[添え字]
		通常の配列同様に添え字で要素にアクセスできる
		*/
		//更新処理
		VectorRect[i]->Update();
	}
	for (int i = 0; i < VectorRect.size() - 1; i++) {
		//衝突処理
		for (int j = i + 1; j < VectorRect.size(); j++) {
			VectorRect[i]->Collision(VectorRect[i], VectorRect[j]);
			VectorRect[j]->Collision(VectorRect[j], VectorRect[i]);
		}
	}

	//リストから削除する
	//イテレータの生成
	std::vector<CRectangle*>::iterator itr;
	//イテレータを先頭
	itr = VectorRect.begin();
	//最後まで繰り返し
	while (itr != VectorRect.end()) {
		if ((*itr)->mEnabled) {
			//次へ
			itr++;
		}
		else {
			//falseのインスタンスを削除
			delete *itr;
			//リストからも削除
			itr = VectorRect.erase(itr);
		}
	}

	for (int i = 0; i < VectorRect.size(); i++) {
		//描画処理
		VectorRect[i]->Render();
	}
	//描画範囲変数の作成　範囲下:-300 範囲上:300 固定
	double mLeft, mRigth, mBottom = -300.0, mTop = 300.0;
	//画像範囲左の設定
	mLeft = CPlayer::spInstance->x - 400.0;
	//画像範囲右の設定
	mRigth = mLeft + 800.0f;
	/*画像の投影変数開始*/
	//行列（設定）をプロジェクションモードへ変更
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();//行列（設定を初期化）
	//2Dの投影範囲を設定
	gluOrtho2D(mLeft, mRigth, mBottom, mTop);
	for (int i = 0; i < VectorRect.size(); i++){
		//描画処理
		VectorRect[i]->Render();
	}
	glLoadIdentity();//行列（設定）を初期化
	//2Dの投影範囲を設定
	gluOrtho2D(-400, 400, -300, 300);
	CText::DrawString("(-380,280)", -380,  280, 16, 16);

}
//次のシーンの取得
CScene::EScene CSceneGame::GetNextScene() {
	return mScene;
}
//デストラクタ
CSceneGame::~CSceneGame() {
	//全てのインスタンスを削除します
	for (int i = 0; i < VectorRect.size(); i++) {
		//インスタンスの削除
		delete VectorRect[i];
	}
	//可変長配列のクリア
	VectorRect.clear();
}
