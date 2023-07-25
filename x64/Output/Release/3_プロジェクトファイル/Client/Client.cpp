#include"Player.h"
#include "Map.h"
#include <Novice.h>
#include "GameTitle.h"

const char kWindowTitle[] = "K022G1068";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 800);
	Novice::AllowWindowSizeChanged(0);
	//Novice::SetWindowMode(kFullscreen);
	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	int gameScene = GameStatus::Game_Title;
	int wingraph_;
	int losegraph_;
	wingraph_ = Novice::LoadTexture("./Resources/winscreen.png");
	losegraph_ = Novice::LoadTexture("./Resources/losescreen.png");

	GameTitle* gameTitle = new GameTitle();
	Player* player = new Player();
	Map* map = new Map();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		switch (gameScene)
		{
			case GameStatus::Game_Title:
			{
				gameTitle->Draw();
				player->SetLose(false);
				player->SetWin(false);
				if (keys[DIK_RETURN] && preKeys[DIK_RETURN])
				{
					player->Respawn();
					gameScene = GameStatus::Game_Start;
				}
				break;
			}

			case GameStatus::Game_Start:
			{
				player->Update(keys, preKeys);
				map->DrawMap();
				Novice::SetBlendMode(kBlendModeNormal);
				player->Draw();
				if (player->GetWin())
				{
					Novice::DrawSprite(0, 0, wingraph_, 1, 1, 0, WHITE);
					if (keys[DIK_SPACE] && preKeys[DIK_SPACE])
					{
						gameScene = GameStatus::Game_Title;
					}
				}
				else if(player->GetLose())
				{
					Novice::DrawSprite(0, 0, losegraph_, 1, 1, 0, WHITE);
					if (keys[DIK_SPACE] && preKeys[DIK_SPACE])
					{
						gameScene = GameStatus::Game_Title;
					}
				}
				break;
			}
		}
		///
		/// ↑更新処理ここまで
		///
		/// 
	
		///
		/// ↓描画処理ここから
		///
		
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
