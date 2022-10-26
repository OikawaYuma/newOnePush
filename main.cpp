#include <Novice.h>

const int kSTAGE_WIDTH = 960;
const int kSTAGE_HEIGHT = 640;
const int kMAPCHIP_WIDTH = 32;
const int kMAPCHIP_HEIGHT = 32;
const int kBLOCK_SIZE = 32;
const int kPlayer_SIZE = 24;
const int kMAP_SIZE_WIDTH = kSTAGE_WIDTH / kMAPCHIP_WIDTH;
const int kMAP_SIZE_HEIGHT = kSTAGE_HEIGHT / kMAPCHIP_HEIGHT;
const int kMOVE_BLOCK = 10;

const char kWindowTitle[] = "LC1B_09_コバヤシタカヒト";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 960, 640);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//画像
	int M_block_Resorces = Novice::LoadTexture("./Resources./containerBlue.png");
	int block_Resorces = Novice::LoadTexture("./Resources./containerBrown.png");
	int easyr_Resorces = Novice::LoadTexture("./Resources./easyr.png");
	int game_clear_Resorces = Novice::LoadTexture("./Resources./game_clear.png");
	int game_over_Resorces = Novice::LoadTexture("./Resources./game_over.png");
	int paper_Resorces = Novice::LoadTexture("./Resources./paper.png");
	int playerLeft1_Resorces = Novice::LoadTexture("./Resources./playerLeft1.png");
	int playerLeft2_Resorces = Novice::LoadTexture("./Resources./playerLeft2.png");
	int playerRight1_Resorces = Novice::LoadTexture("./Resources./playerRight1.png");
	int playerRight2_Resorces = Novice::LoadTexture("./Resources./playerRight2.png");
	int craneGh = Novice::LoadTexture("./Resources/reachStacker.png");
	int skyGh = Novice::LoadTexture("./Resources/sky.png");
	int stageMap = Novice::LoadTexture("./resources/stageLineAndFlooar.png");
	int playerRight[2] = { 
		Novice::LoadTexture("./resources/playerRight1.png"),
		Novice::LoadTexture("./resources/playerRight2.png") 
	};
	int playerLeft[2] = {
		Novice::LoadTexture("./resources/playerLeft1.png"),
		Novice::LoadTexture("./resources/playerLeft2.png")
	};
	enum gameSelect {
		TITLE,
		STAGESELECT,
		PLAY,
		GAME_CLEAR
	};
	int gameSelect = TITLE;
	enum stageNum {
		TUTLIAL,
		STAGE1,
		STAGE2,
	};
	int stageNum = TUTLIAL;
	int animeCount = 0;
	int playerAnimation = animeCount / 30;

	//マップチップ配列
	int MAP_chiplist[kMAP_SIZE_HEIGHT][kMAP_SIZE_WIDTH]
	{

		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	};
	///stageTUTORIALの時にマップチップリストに使用するマップチップ
	int MAP_chiplist_TUTLIAL[kMAP_SIZE_HEIGHT][kMAP_SIZE_WIDTH]
	{
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,1,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,4,0,0,},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,}
	};

	///stage1の時にマップチップリストに使用するマップチップ
	int MAP_chiplist_STAGE1[kMAP_SIZE_HEIGHT][kMAP_SIZE_WIDTH]
	{
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},

		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},

		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,1,2,1,0,4,0,0,1,0,0,0,0,0,1,1,0,0,0,4,0,2,0,0,0,},

		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,}
	};

	int MAP_chiplist_STAGE2[kMAP_SIZE_HEIGHT][kMAP_SIZE_WIDTH]
	{
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},

		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},

		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,2,0,4,1,},
		{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,},
		{0,0,0,0,0,0,0,1,0,0,2,1,0,0,0,0,0,0,2,1,1,1,1,1,1,1,1,1,1,1,},
		{0,0,0,0,0,0,1,2,4,0,2,1,0,1,4,0,0,0,2,1,1,1,1,1,1,1,1,1,1,1,},

		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,}
	};
	int tmpMAP_chiplist[kMAP_SIZE_HEIGHT][kMAP_SIZE_WIDTH]
	{

		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},

		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},

		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},


		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	};

	for (int i = 0; i < kMAP_SIZE_WIDTH; i++) {
		for (int j = 0; j < kMAP_SIZE_HEIGHT; j++) {
			tmpMAP_chiplist[j][i] = MAP_chiplist[j][i];
		}
	}

	enum Block_done
	{
		NONE,
		BLOCK,
		M_BLOCK,
	};

	enum CHANGE
	{
		UFO,
		ACTION
	};

	int scene = 0;

	typedef struct Vector2
	{
		int x;
		int y;
	};



	typedef struct Vertex
	{
		Vector2 leftTop;
		Vector2 rightTop;
		Vector2 rightBottom;
		Vector2 leftBottom;


	};


	//player

	Vector2 player = { 128,128 };

	Vector2 playerSpeed = { 1,0 };

	int tmpSpeed = 2;

	int playerJump = 0;

	bool isPlayerJump = false;

	int time = 0;



	//クレーン

	int craneScene = 0;
	enum craneS
	{
		moveCrane,
		descentCrane,
		removeCrane,
		drop,
		returnCrane,

	};

	Vector2 cranepos = { 896,128 };
	Vector2 craneArray = { 0,0 };
	Vector2 craneTmp = { 0,0 };
	Vector2 craneTmpSpeed = { 0,0 };

	int frameTimer = 7;
	int frameTimerF = false;
	int craneSpeed = 32;
	int craneDropSpeed = 4;



	//移動ブロック

	Vector2 moveBlock[kMOVE_BLOCK] = {};

	Vector2 preBox = { 0,0 };

	int blockF = false;

	///STAGESELECT

	int stageSelectTimer = 0;


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
		switch (gameSelect) {
		case TITLE: {
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				gameSelect = STAGESELECT;
			}
			break;
		}
		case STAGESELECT: {
			stageSelectTimer++;
			if (stageSelectTimer >= 360) {
				stageSelectTimer = 0;
			}

			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				if (stageSelectTimer <= 120) {
					for (int i = 0; i < 20; i++) {
						for (int j = 0; j < 30; j++) {
							tmpMAP_chiplist[i][j] = MAP_chiplist_TUTLIAL[i][j];
							player.x = 312;
							player.y = 488;
						}
					}
					gameSelect = PLAY;
				}
				else if (stageSelectTimer <= 240) {
					for (int i = 0; i < 20; i++) {
						for (int j = 0; j < 30; j++) {
							tmpMAP_chiplist[i][j] = MAP_chiplist_STAGE1[i][j];
							player.x = 510;
							player.y = 488;
						}
					}
					gameSelect = PLAY;
				}
				else if (stageSelectTimer <= 360) {
					for (int i = 0; i < 20; i++) {
						for (int j = 0; j < 30; j++) {
							tmpMAP_chiplist[i][j] = MAP_chiplist_STAGE2[i][j];
							player.x = 704;
							player.y =392 ;
						}
					}
					gameSelect = PLAY;
				}


			}
			break;
		}
		case PLAY: {

			animeCount++;
			playerAnimation = animeCount / 30;
			if (animeCount >= 60) {
				animeCount = 0;
			}



			switch (scene)
			{
			case UFO:

				craneArray.x = cranepos.x / kMAPCHIP_WIDTH;
				craneArray.y = cranepos.y / kMAPCHIP_HEIGHT;

				if (keys[DIK_SPACE]) {
					time += 1;
					if (keys[DIK_SPACE] && time >= 300) {
						time = 0;
						scene = 1;
					}
					else if (preKeys[DIK_SPACE] == 0 && time <= 300) {
						time = 0;
					}
				}

				switch (craneScene)
				{
				case moveCrane:
					if (frameTimerF == true) {
						frameTimer -= 4;
						if (frameTimer <= 0) {
							craneTmp.x = cranepos.x - craneSpeed;
							craneArray.x = craneTmp.x / kMAPCHIP_WIDTH;
							frameTimer = 100;

							if (tmpMAP_chiplist[craneArray.y][craneArray.x] == 0) {
								cranepos.x -= craneSpeed;
							}
						}
						if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
							craneScene = 1;
						}

					}

					if (keys[DIK_SPACE] == 0 && preKeys[DIK_SPACE] != 0) {
						frameTimerF = true;
					}


					break;
				case descentCrane:

					craneTmp.y = cranepos.y + craneDropSpeed;
					craneArray.y = craneTmp.y / kMAPCHIP_WIDTH;
					if (tmpMAP_chiplist[craneArray.y][craneArray.x] == 0) {
						cranepos.y += craneDropSpeed;

					}
					else if (tmpMAP_chiplist[craneArray.y][craneArray.x] == 1) {
						craneScene = 2;
					}
					else if (tmpMAP_chiplist[craneArray.y][craneArray.x] == 2) {
						tmpMAP_chiplist[craneArray.y][craneArray.x] = 0;
						blockF = true;
						craneScene = 2;
					}
					else if (tmpMAP_chiplist[craneArray.y][craneArray.x] == 3) {
						craneScene = 2;
					}
					else if (tmpMAP_chiplist[craneArray.y][craneArray.x] == 4) {
						craneScene = 2;
					}
					break;
				case removeCrane:
					craneTmp.y = cranepos.y - craneDropSpeed;
					craneArray.y = craneTmp.y / kMAPCHIP_WIDTH;
					if (tmpMAP_chiplist[craneArray.y][craneArray.x] == 0) {
						cranepos.y -= craneDropSpeed;
					}
					if (tmpMAP_chiplist[craneArray.y][craneArray.x] == 3 && frameTimerF == true) {
						craneScene = 3;
					}
					else if (tmpMAP_chiplist[craneArray.y][craneArray.x] == 3 && frameTimerF == false) {
						craneScene = 4;
					}



					break;

				case drop:
					if (frameTimerF == true) {
						frameTimer -= 4;
						if (frameTimer <= 0) {
							craneTmp.x = cranepos.x - craneSpeed;
							craneArray.x = craneTmp.x / kMAPCHIP_WIDTH;
							frameTimer = 100;
							cranepos.x -= craneSpeed;

						}
						if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
							frameTimerF = false;


						}


					}
					if (frameTimerF == false) {
						craneTmp.y = cranepos.y + craneDropSpeed + kMAPCHIP_WIDTH;
						craneArray.y = craneTmp.y / kMAPCHIP_WIDTH;



						if (tmpMAP_chiplist[craneArray.y][craneArray.x] == 0) {
							cranepos.y += craneDropSpeed;
						}
						else if (tmpMAP_chiplist[craneArray.y][craneArray.x] != 0) {
							if (blockF == true) {
								tmpMAP_chiplist[craneArray.y - 1][craneArray.x] = 2;
								blockF = false;
							}
							craneScene = 2;
						}
					}


					break;

				case returnCrane:
					if (cranepos.x != 896) {
						cranepos.x += 2;

					}
					else if (cranepos.x == 896) {
						craneScene = 0;
					}

					break;
				}







				/*if (keys[DIK_W] && preKeys[DIK_W] == 0) {
					craneTmp.y = cranepos.y - craneSpeed;
					craneArray. y = craneTmp.y / kMAPCHIP_WIDTH;
					if (tmpMAP_chiplist[craneArray.y][craneArray.x] == 0) {
						cranepos.y -= craneSpeed;
					}
				}
				if (keys[DIK_S] && preKeys[DIK_S] == 0) {
					craneTmp.y = cranepos.y + craneSpeed;
					craneArray.y = craneTmp.y / kMAPCHIP_WIDTH;
					if (tmpMAP_chiplist[craneArray.y][craneArray.x] == 0) {
						cranepos.y += craneSpeed;
					}
				}*/
				/*if (keys[DIK_A] && preKeys[DIK_A] == 0) {
					craneTmp.x = cranepos.x - craneSpeed;
					craneArray.x = craneTmp.x / kMAPCHIP_WIDTH;
					if (tmpMAP_chiplist[craneArray.y][craneArray.x] == 0) {
						cranepos.x -= craneSpeed;
					}
				}
				if (keys[DIK_D] && preKeys[DIK_D] == 0) {
					craneTmp.x = cranepos.x + craneSpeed;
					craneArray.x = craneTmp.x / kMAPCHIP_WIDTH;
					if (tmpMAP_chiplist[craneArray.y][craneArray.x] == 0) {
						cranepos.x += craneSpeed;
					}
				}*/




				break;


			case ACTION:
				if (keys[DIK_SPACE]) {
					time += 1;
					if (keys[DIK_SPACE] && time >= 300) {
						time = 0;
						scene = 0;

					}
					else if (preKeys[DIK_SPACE] == 0 && time <= 300) {
						time = 0;
					}
				}

				//頂点
				Vertex pos = {
					player.x / kMAPCHIP_WIDTH    ,player.y / kMAPCHIP_HEIGHT, //左上
					(player.x - 1 + kPlayer_SIZE) / kMAPCHIP_WIDTH, player.y / kMAPCHIP_HEIGHT,//右上
					(player.x - 1 + kPlayer_SIZE) / kMAPCHIP_WIDTH, (player.y - 1 + kPlayer_SIZE) / kMAPCHIP_HEIGHT,//右下
					player.x / kMAPCHIP_WIDTH, (player.y - 1 + kPlayer_SIZE) / kMAPCHIP_HEIGHT,//左下
				};


				pos.leftTop.y = (player.y - tmpSpeed) / kBLOCK_SIZE;
				pos.rightTop.y = (player.y - tmpSpeed) / kBLOCK_SIZE;

				if (isPlayerJump == false && keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
					isPlayerJump = true;


					playerJump = 16;


				}
				if (isPlayerJump == true && playerJump > 0) {
					player.y -= playerJump;
					playerJump -= 2;
				}
				if (tmpMAP_chiplist[pos.leftTop.y][pos.leftTop.x] != NONE || tmpMAP_chiplist[pos.rightTop.y][pos.rightTop.x] != NONE) {

					playerJump = 0;

				}

				//地面の接地面

				pos.leftBottom.y = (player.y + kPlayer_SIZE) / kBLOCK_SIZE;
				pos.rightBottom.y = (player.y + kPlayer_SIZE) / kBLOCK_SIZE;

				if (tmpMAP_chiplist[pos.leftBottom.y][pos.leftBottom.x] == 4 && tmpMAP_chiplist[pos.rightBottom.y][pos.rightBottom.x] == 4) {
					if (tmpMAP_chiplist[pos.leftBottom.y][pos.leftBottom.x] == 4) {
						tmpMAP_chiplist[pos.leftBottom.y][pos.leftBottom.x] = NONE;
					}
					if (tmpMAP_chiplist[pos.rightBottom.y][pos.rightBottom.x] == 4) {
						tmpMAP_chiplist[pos.rightBottom.y][pos.rightBottom.x] = NONE;
					}
				}
				else if (tmpMAP_chiplist[pos.leftBottom.y][pos.leftBottom.x] != NONE && tmpMAP_chiplist[pos.rightBottom.y][pos.rightBottom.x] != NONE) {
					playerJump = 0;
					playerSpeed.y = 0;
					if (isPlayerJump == true && playerJump <= 0) {
						isPlayerJump = false;
					}
				}
				else if (tmpMAP_chiplist[pos.leftBottom.y][pos.leftBottom.x] != NONE || tmpMAP_chiplist[pos.rightBottom.y][pos.rightBottom.x] != NONE) {
					playerSpeed.y = 0;
					playerJump = 0;
					if (isPlayerJump == true && playerJump <= 0) {
						isPlayerJump = false;
					}
				}

				else if (tmpMAP_chiplist[pos.leftBottom.y][pos.leftBottom.x] == NONE && tmpMAP_chiplist[pos.rightBottom.y][pos.rightBottom.x] == NONE) {
					playerSpeed.y = 2;
				}




				// x座標の反転
				pos.leftTop.x = (player.x - tmpSpeed) / kBLOCK_SIZE;
				pos.leftBottom.x = (player.x - tmpSpeed) / kBLOCK_SIZE;
				pos.rightBottom.x = (player.x + kPlayer_SIZE) / kBLOCK_SIZE;
				pos.rightTop.x = (player.x + kPlayer_SIZE) / kBLOCK_SIZE;
				if (tmpMAP_chiplist[pos.leftTop.y][pos.leftTop.x] == 4 || tmpMAP_chiplist[pos.leftBottom.y][pos.leftBottom.x] == 4) {
					if (tmpMAP_chiplist[pos.leftTop.y][pos.leftTop.x] == 4) {
						tmpMAP_chiplist[pos.leftTop.y][pos.leftTop.x] = NONE;
					}
					if (tmpMAP_chiplist[pos.leftBottom.y][pos.leftBottom.x] == 4) {
						tmpMAP_chiplist[pos.leftBottom.y][pos.leftBottom.x] = NONE;
					}
				}
				else if (tmpMAP_chiplist[pos.leftTop.y][pos.leftTop.x] != NONE && tmpMAP_chiplist[pos.leftBottom.y][pos.leftBottom.x] != NONE) {
					playerSpeed.x = 1;

				}
				else if (tmpMAP_chiplist[pos.leftTop.y][(player.x - kPlayer_SIZE) / kBLOCK_SIZE] == NONE && tmpMAP_chiplist[(player.y + kPlayer_SIZE - tmpSpeed) / kBLOCK_SIZE][(player.x - tmpSpeed) / kBLOCK_SIZE] != NONE) {
					playerSpeed.x = 1;
				}

				if (tmpMAP_chiplist[pos.rightTop.y][pos.rightTop.x] == 4 || tmpMAP_chiplist[pos.rightBottom.y][pos.rightBottom.x] == 4) {
					if (tmpMAP_chiplist[pos.rightTop.y][pos.rightTop.x] == 4) {
						tmpMAP_chiplist[pos.rightTop.y][pos.rightTop.x] = NONE;
					}
					if (tmpMAP_chiplist[pos.rightBottom.y][pos.rightBottom.x] == 4) {
						tmpMAP_chiplist[pos.rightBottom.y][pos.rightBottom.x] = NONE;
					}
				}
				else if (tmpMAP_chiplist[pos.rightTop.y][pos.rightTop.x] != NONE && tmpMAP_chiplist[pos.rightBottom.y][pos.rightBottom.x] != NONE) {
					playerSpeed.x = -1;
				}
				else if (tmpMAP_chiplist[pos.rightTop.y][(player.x + kPlayer_SIZE * 2) / kBLOCK_SIZE] == NONE && tmpMAP_chiplist[(player.y + kPlayer_SIZE - tmpSpeed) / kBLOCK_SIZE][(player.x + kPlayer_SIZE + tmpSpeed) / kBLOCK_SIZE] != NONE) {
					playerSpeed.x = -1;
				}

				player.x += playerSpeed.x;
				player.y += playerSpeed.y;


				break;
			}
			break;
		}
		case GAME_CLEAR: {
			break;
		}
		}



		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		switch (gameSelect) {
		case TITLE: {


			break;
		}
		case STAGESELECT: {
			break;
		}
		case PLAY: {

			Novice::DrawSprite(0, 0, skyGh, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite(0, 0, stageMap, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);

			for (int i = 0; i < kMAP_SIZE_HEIGHT; i++) {
				for (int j = 0; j < kMAP_SIZE_WIDTH; j++) {
					if (tmpMAP_chiplist[i][j] == 1) {

						Novice::DrawSprite(j * kMAPCHIP_WIDTH, i * kMAPCHIP_HEIGHT, block_Resorces, 1.0f, 1.0f, 0.0f, 0xffffffff);
						//Novice::DrawBox(j * kMAPCHIP_WIDTH, i * kMAPCHIP_HEIGHT, kMAPCHIP_WIDTH, kMAPCHIP_HEIGHT, 0.0f, RED, kFillModeSolid);
					}
					if (tmpMAP_chiplist[i][j] == 2) {
						Novice::DrawSprite(j * kMAPCHIP_WIDTH, i * kMAPCHIP_HEIGHT, M_block_Resorces, 1.0f, 1.0f, 0.0f, 0xffffffff);
						//Novice::DrawBox(j * kMAPCHIP_WIDTH, i * kMAPCHIP_HEIGHT, kMAPCHIP_WIDTH, kMAPCHIP_HEIGHT, 0.0f, GREEN, kFillModeSolid);

					}
					if (tmpMAP_chiplist[i][j] == 4) {
						Novice::DrawSprite(j * kMAPCHIP_WIDTH, i * kMAPCHIP_HEIGHT, paper_Resorces, 1.0f, 1.0f, 0.0f, 0xffffffff);
						//Novice::DrawBox(j * kMAPCHIP_WIDTH, i * kMAPCHIP_HEIGHT, kMAPCHIP_WIDTH, kMAPCHIP_HEIGHT, 0.0f, GREEN, kFillModeSolid);

					}

				}
			}
			Novice::DrawSprite(player.x, player.y, playerRight1_Resorces, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
			//Novice::DrawSprite();
			if (blockF == true) {
				Novice::DrawSprite(cranepos.x, cranepos.y, M_block_Resorces, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
			}
			Novice::DrawSprite(cranepos.x - 32, cranepos.y - 512, craneGh, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
			break;
		}
		case GAME_CLEAR: {
			break;

		}
		}



		Novice::ScreenPrintf(10, 10, "%d", scene);
		Novice::ScreenPrintf(10, 30, "%d", time);
		Novice::ScreenPrintf(10, 50, "%d", stageSelectTimer);

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