#pragma once
#include "SDL.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"
class Game
{
public:

	// 게임 상태 시작화면, 게임 플레이, 게임 클리어
	enum class GameState
	{
		MainMenu,
		Playing,
		GameClear
	};

	Game();
	// --- 실행, 진행, 종료
	bool Initialize();
	void RunLoop();
	void Shutdown();
	// ----- 게임의 Actor 관련
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);


	// ----- 게임의 Sprite 관련
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	// ---- Texture 사용
	class Texture* GetTexture(const std::string& fileName);
	
	// -- 시작 상태 전환, 시작화면 화면, 시작화면 입력 
	void ChangePlaying();
	void ProcessMainMenuInput();

	// -- 클리어 상태 전환, 클리어 입력
	void ChangeClear();
	void ProcessClearInput();
	
	// ---- box 모양 상호작용
	void ProcessBoxs();

	// ---- Game 밖에서도 Game에 plane과 star 사용을 위해서
	std::vector<class Plane*>& GetPlanes() { return mPlanes; }
	std::vector<class Star*> GetStar() { return mStar; }

private:
	// --- 플레이 중 입력, 게임 업데이트 
	void ProcessInput();
	void UpdateGame();
	
	//--- 화면 출력
	void GenerateOutput();
	
	//--- shader 불러오기
	bool LoadShaders();

	// --- 버텍스 생성
	void CreateSpriteVerts();
	
	// --- Data 불러오고 종료 시 제거
	void LoadData();
	void UnloadData();

	std::unordered_map<std::string, class Texture*> mTextures;

	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;
	
	std::vector<class SpriteComponent*> mSprites;
	SpriteComponent* mBGSprite;
	SpriteComponent* mBGSpriteMain;
	SpriteComponent* mBGSpriteClear;
	SpriteComponent* mButtonSprite;
	class Shader* mSpriteShader;
	class VertexArray* mSpriteVerts;

	SDL_Window* mWindow;
	SDL_GLContext mContext;
	Uint32 mTicksCount;
	
	bool mIsRunning;
	bool mUpdatingActors;
	
	class Player* mPlayer;
	std::vector<class Star*> mStar;
	std::vector<class Plane*> mPlanes;

	GameState mCurrentState;

	// 게임 상태 get/set 
	void SetGameState(GameState state) { mCurrentState = state; }
	GameState GetGameState() const { return mCurrentState; }
};


// --- 이제 안 쓰는 멤버
/*
void DisplayClear();
void DisplayMainMenu();
*/

// --- Plane 사용
//void AddPlane(class Plane* pl);
//void RemovePlane(class Plane* pl);
