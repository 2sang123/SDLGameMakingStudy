#include "Game.h"
#include <GL/glew.h>
#include "Texture.h"
#include "VertexArray.h"
#include "Shader.h"
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Actor.h"
#include "Player.h"
#include "Plane.h"
#include "BoxComponent.h"
#include "Star.h"

Game::Game()
	:mWindow(nullptr)
	, mSpriteShader(nullptr)
	, mIsRunning(true)
	, mUpdatingActors(false)
	, mCurrentState(GameState::MainMenu)
{

}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow("Finding star", 75, 50,
		1280, 960, SDL_WINDOW_OPENGL);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	mContext = SDL_GL_CreateContext(mWindow);

	//
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}
	glGetError();

	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}

	CreateSpriteVerts();

	mTicksCount = SDL_GetTicks();

	LoadData();

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		switch (mCurrentState)
		{
		case GameState::MainMenu:
			ProcessMainMenuInput(); // 메인 메뉴 입력 처리
			break;

		case GameState::Playing:
			ProcessInput(); // 게임 입력 처리
			UpdateGame(); // 게임 업데이트
			break;

		case GameState::GameClear:
			ProcessClearInput();
			break;
		default:
			break;
		}
		GenerateOutput(); // 화면 출력
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(keyState);
	}
	mUpdatingActors = false;
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	for (auto pending : mPendingActors)
	{
		pending->ComputeWorldTransform();
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	for (auto actor : deadActors)
	{
		delete actor;
	}

	ProcessBoxs();
}



void Game::ChangePlaying() 
{
	mCurrentState = GameState::Playing;
}
void Game::ChangeClear()
{
	mCurrentState = GameState::GameClear;
}

void Game::ProcessMainMenuInput()
{
	SDL_Event event;
	const Uint8* keyState = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		case SDL_KEYDOWN:
			// 키보드 입력 처리
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				mIsRunning = false; // ESC 키를 누르면 프로그램 종료
				break;
			case SDLK_RETURN:
				// ENTER 키를 누르면 Playing 상태로 변경
				ChangePlaying();
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

void Game::ProcessClearInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		case SDL_KEYDOWN:
			switch ((event.key.keysym.sym))
			{
			case SDLK_ESCAPE:
				mIsRunning = false; // ESC 키를 누르면 프로그램 종료
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

void Game::GenerateOutput()
{

	// 화면 클리어
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// 이미지에 알파 표시를 위해서 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Shader, Vertex를 활성화
	mSpriteShader->SetActive();
	mSpriteVerts->SetActive();

	// 게임 상태에 따라서 화면을 그림
	switch (mCurrentState)
	{
	case GameState::MainMenu:
		mBGSpriteMain->Draw(mSpriteShader);
		break;
	case GameState::Playing:
		mBGSprite->Draw(mSpriteShader);
		for (auto sprite : mSprites)
		{
			if (sprite != mBGSpriteClear)
			{
				sprite->Draw(mSpriteShader);
			}
		}
		break;
	case GameState::GameClear:
		mBGSpriteClear->Draw(mSpriteShader);
		break;
	default:
		break;
	}
	
	SDL_GL_SwapWindow(mWindow);
}

bool Game::LoadShaders()
{
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}

	mSpriteShader->SetActive();
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(1280.f, 960.f);
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);
	return true;
}

void Game::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f,  0.5f, 0.f, 0.f, 0.f, 
		 0.5f,  0.5f, 0.f, 1.f, 0.f, 
		 0.5f, -0.5f, 0.f, 1.f, 1.f, 
		-0.5f, -0.5f, 0.f, 0.f, 1.f  
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}


void Game::LoadData()
{
	Actor* mainMenuBgActor = new Actor(this);
	mBGSpriteMain = new SpriteComponent(mainMenuBgActor);
	mBGSpriteMain->SetTexture(GetTexture("Assets/FinalMainImage.png"));
	mBGSpriteMain->SetScale(1280.f / mBGSpriteMain->GetTexWidth(),
		960.f / mBGSpriteMain->GetTexHeight());
	
	// ---- Game Play
	Actor* bgActor = new Actor(this); 
	mBGSprite = new SpriteComponent(bgActor);
	mBGSprite->SetTexture(GetTexture("Assets/SpaceBGAiMake.png"));
	mBGSprite->SetScale(1280.f / mBGSprite->GetTexWidth(),
		960.f / mBGSprite->GetTexHeight());
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j <5; j++)
		{
			Plane* plane = new Plane(this);
			plane->SetScale(1.f);
			plane->SetPosition(Vector2(-340.f + (i*230.f), -390.f+(j*150.f)));
			mPlanes.push_back(plane);
		}
	}
	
	for (int i = 0; i < 2; i++)
	{
		Plane* plane = new Plane(this);
		plane->SetScale(1.f);
		plane->SetPosition(Vector2(540.f, -320.f+(i*300.f)));
		mPlanes.push_back(plane);
	}

	for (int i = 0; i < 2; i++)
	{
		Plane* plane = new Plane(this);
		plane->SetScale(1.f);
		plane->SetPosition(Vector2(-550.f, -150.f+(i*300.f)));
		mPlanes.push_back(plane);
	}

	Star* star = new Star(this);
	star->SetScale(1.f);
	star->SetPosition(Vector2(500.f, 330.0f));
	mStar.push_back(star);

	mPlayer = new Player(this);
	mPlayer->SetScale(0.5f);
	mPlayer->SetPosition(Vector2(-510.f, -409.0f));

	//--- Game clear
	Actor* clearbgActor = new Actor(this); // 배경 스프라이트를 위한  Actor 생성
	mBGSpriteClear = new SpriteComponent(clearbgActor);
	mBGSpriteClear->SetTexture(GetTexture("Assets/ClearImage2.png"));
	mBGSpriteClear->SetScale(1280.f / mBGSpriteClear->GetTexWidth(),
		960.f / mBGSpriteClear->GetTexHeight());

}

void Game::UnloadData()
{

	while (!mActors.empty())
	{
		delete mActors.back();
	}

	for (auto i : mTextures)
	{
		i.second->Unload();
		delete i.second;
	}
	mTextures.clear();
}

Texture* Game::GetTexture(const std::string& fileName)
{
	Texture* tex = nullptr;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		tex = new Texture();
		if (tex->Load(fileName))
		{
			mTextures.emplace(fileName, tex);
		}
		else
		{
			delete tex;
			tex = nullptr;
		}
	}
	return tex;
}


void Game::Shutdown()
{
	UnloadData();
	delete mSpriteVerts;
	mSpriteShader->Unload();
	delete mSpriteShader;
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void Game::ProcessBoxs()
{
	BoxComponent* boxA = mPlayer->GetBoxComponent();
	if (boxA)
	{
		for (size_t i = 0; i < mStar.size(); ++i)
		{
			BoxComponent* boxB = mStar[i]->GetBoxComponent();

			if (boxB && BoxComponent::Intersect(*boxA, *boxB))
			{
				Player* player = mPlayer;
				Star* star = mStar[i];

				if (player && star)
				{
					ChangeClear();
				}
			}
		}
	}
}

//---- 필요없어진 코드들 정리


//void Game::DisplayMainMenu()
//{
//	mBGSpriteMain->Draw(mSpriteShader);
//}


//void Game::DisplayClear()
//{
//	
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT);
//
//
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//
//	mSpriteShader->SetActive();
//	mSpriteVerts->SetActive();
//
//	
//	mBGSpriteClear->Draw(mSpriteShader);
//
//	
//	SDL_GL_SwapWindow(mWindow);
//}

//void Game::AddPlane(Plane* pl)
//{
//	mPlanes.emplace_back(pl);
//}
//
//void Game::RemovePlane(Plane* pl)
//{
//	auto iter = std::find(mPlanes.begin(),
//		mPlanes.end(), pl);
//	if (iter != mPlanes.end())
//	{
//		mPlanes.erase(iter);
//	}
//}