#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "UI.h"
#include "Managers.h"
#include "Mouse.h"
#include "GameState.h"
#include "Level.h"
#include "Actor.h"



class D2DWindow;
class SimpleTimer;
class Game 
{

	D2DWindow& m_window;
	RectF m_backGroundColor;
	Renderer m_gfx;
	std::unique_ptr<EntityManager> m_EntityMgr;
	std::unique_ptr<UserInterfaceManager> m_UserInterfaceMgr;
	std::unique_ptr<SoundManager> m_soundMgr;
	std::unique_ptr<PathfindingManager> m_pathFindingMgr;
	std::unique_ptr<TextManager> m_textMgr;
	std::unique_ptr<ImageManager> m_imageMgr;
	Level* m_testLevel;
	Actor* player;
	Camera m_cam;
	GameState m_gameState = GameState::running;
	
	
private:
	// Functons
	void InitECS();
	void LoadLevel(const unsigned int& index);
	void InitUI();
	void InitManagers();
	void InitText();
	void InitPlayer();
	void HandleUserInput(Mouse::Event& mouseEvent,Keyboard::Event& kbdEvent);
public:
	Game(D2DWindow& window);
	~Game();
	bool Play(SimpleTimer& timer);
	HRESULT ConstructSceen(const float& deltaTime, const int& gameTime);
	HRESULT RenderSceen();

	
};

