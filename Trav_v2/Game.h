#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "UI.h"
#include "Managers.h"
#include "Mouse.h"
#include "GameState.h"
#include "Chest.h"
#include "MapLayer.h"
#include "Actor.h"
#include "TextureLoader.h"
const char mapNames[10][MAX_PATH] =
{
	{ "test.bin" },
	{ "test1.bin" },
	{ "test.bin" },
	{ "test.bin" },
	{ "test.bin" },
	{ "test.bin" },
	{ "test.bin" },
	{ "test.bin" },
	{ "test.bin" },
	{ "test.bin" }
};

class D2DWindow;
class SimpleTimer;
class Game
{
	Renderer m_gfx;
	D2DWindow& m_window;
	RectF m_backGroundColor;
	std::unique_ptr<EntityManager> m_EntityMgr;
	std::unique_ptr<TextManager> m_textMgr;
	std::unique_ptr<ImageManager> m_imageMgr;
	std::unique_ptr<UserInterfaceManager> m_UserInterfaceMgr;
	Camera m_cam;
	GameState m_gameState = GameState::running;
	Chest* chest;
	Actor* testActor;
	Actor* testActor2;
	Actor* testActor3;
	
private:
	// Functons
	void InitECS();
	void LoadLevel(const unsigned int& index);
	void InitUI();
	
	void InitText();
	void HandleUserInput(Mouse::Event& mouseEvent,Keyboard::Event& kbdEvent);
public:
	Game(D2DWindow& window);
	~Game();
	bool Play(SimpleTimer& timer);
	HRESULT ConstructSceen(const float& deltaTime, const int& gameTime);
	HRESULT RenderSceen();

	
};

