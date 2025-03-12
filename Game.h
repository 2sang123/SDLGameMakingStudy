#pragma once
#include "SDL.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"
class Game
{
public:

	// ���� ���� ����ȭ��, ���� �÷���, ���� Ŭ����
	enum class GameState
	{
		MainMenu,
		Playing,
		GameClear
	};

	Game();
	// --- ����, ����, ����
	bool Initialize();
	void RunLoop();
	void Shutdown();
	// ----- ������ Actor ����
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);


	// ----- ������ Sprite ����
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	// ---- Texture ���
	class Texture* GetTexture(const std::string& fileName);
	
	// -- ���� ���� ��ȯ, ����ȭ�� ȭ��, ����ȭ�� �Է� 
	void ChangePlaying();
	void ProcessMainMenuInput();

	// -- Ŭ���� ���� ��ȯ, Ŭ���� �Է�
	void ChangeClear();
	void ProcessClearInput();
	
	// ---- box ��� ��ȣ�ۿ�
	void ProcessBoxs();

	// ---- Game �ۿ����� Game�� plane�� star ����� ���ؼ�
	std::vector<class Plane*>& GetPlanes() { return mPlanes; }
	std::vector<class Star*> GetStar() { return mStar; }

private:
	// --- �÷��� �� �Է�, ���� ������Ʈ 
	void ProcessInput();
	void UpdateGame();
	
	//--- ȭ�� ���
	void GenerateOutput();
	
	//--- shader �ҷ�����
	bool LoadShaders();

	// --- ���ؽ� ����
	void CreateSpriteVerts();
	
	// --- Data �ҷ����� ���� �� ����
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

	// ���� ���� get/set 
	void SetGameState(GameState state) { mCurrentState = state; }
	GameState GetGameState() const { return mCurrentState; }
};


// --- ���� �� ���� ���
/*
void DisplayClear();
void DisplayMainMenu();
*/

// --- Plane ���
//void AddPlane(class Plane* pl);
//void RemovePlane(class Plane* pl);
