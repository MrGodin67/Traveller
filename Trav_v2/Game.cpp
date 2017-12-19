#include "stdafx.h"
#include "Game.h"
#include "SimpleTimer.h"
#include "D2DWindow.h"
#include "FileManager.h"
#include "MapTest.h"
#include "Level.h"

//Private functions
void Game::InitECS()
{
	m_EntityMgr = std::make_unique<EntityManager>(m_cam);
	
	
}

void Game::LoadLevel(const unsigned int& index)
{
	m_testLevel  = new Level();
	m_testLevel->CreateLevel(m_EntityMgr.get(), 0);
	m_pathFindingMgr->Initialize(m_testLevel->PathMap(),
		m_testLevel->MapDimensions(), m_testLevel->CellDimensions());
	m_cam.ConfineToMap(RectF(0.0f, 0.0f,
		(float)(m_testLevel->MapDimensions().x * m_testLevel->CellDimensions().x),
		(float)(m_testLevel->MapDimensions().y * m_testLevel->CellDimensions().y)));
	
	SafeDelete(&m_testLevel);

	

	
}

void Game::InitUI()
{
	m_UserInterfaceMgr = MakeUnique<UserInterfaceManager>();
	m_UserInterfaceMgr->SetCurrentWindow("start");
}

void Game::InitManagers()
{
	Locator::SetGraphics(&m_gfx);
	m_textMgr = std::make_unique<TextManager>();
	Locator::SetTextManager(m_textMgr.get());
	m_soundMgr = std::make_unique<SoundManager>();
	Locator::SetSoundManager(m_soundMgr.get());
	m_imageMgr = std::make_unique<ImageManager>();
	Locator::SetImageManager(m_imageMgr.get());
	//m_levelMgr = std::make_unique<LevelManager>();
	//Locator::SetLevelManager(m_levelMgr.get());
	m_pathFindingMgr = std::make_unique<PathfindingManager>();
	Locator::SetPathFinder(m_pathFindingMgr.get());
	
}



void Game::InitText()
{
	
	Locator::Text()->InitializeFont("Tahoma8",  FontPair(L"Tahoma",8.0f ));
	Locator::Text()->InitializeFont("Tahoma10", FontPair(L"Tahoma", 10.0f));
	Locator::Text()->InitializeFont("Tahoma12", FontPair(L"Tahoma", 12.0f));
	Locator::Text()->InitializeFont("Tahoma14", FontPair(L"Tahoma", 14.0f));
	Locator::Text()->InitializeFont("Tahoma16", FontPair(L"Tahoma", 16.0f));
	Locator::Text()->InitializeFont("Tahoma18", FontPair(L"Tahoma", 18.0f));
	Locator::Text()->InitializeFont("Tahoma20", FontPair(L"Tahoma", 20.0f));
	Locator::Text()->InitializeFont("Tahoma22", FontPair(L"Tahoma", 22.0f));
	
}

void Game::InitPlayer()
{
	player = &m_EntityMgr->Add<Actor>(*m_EntityMgr.get());
	player->Add<Transform>(Vec2f(100.0f, 100.0f), Vec2f(0.0f, 0.0f), Vec2f(48.0f, 48.0f));
	player->Add<Body>(m_imageMgr->Load("tank_1", L"assets\\images\\tank1_body.png"));
	player->Add<Turret>(m_imageMgr->Load("turret_1", L"assets\\images\\tank1_gun.png"));
	player->Add<Collider>(Vec2f(100.0f, 100.0f) + (Vec2f(48.0f, 48.0f)*0.5f), (Vec2f(48.0f, 48.0f)*0.5f));
	player->Get<Transform>().acceleration = 70.0f;
	
	//player->AddGroup(groupMapLayer1);
	player->AddGroup(groupPlayers);

	m_cam.UpdatePosition(player->Get<Transform>().Center());

	
}

void Game::HandleUserInput(Mouse::Event & mouseEvent, Keyboard::Event & kbdEvent)
{
	if (mouseEvent.GetType() == Mouse::Event::LRelease)
	{
		if (player->Has<Path>())
		{
			player->Remove<Path>();
			player->RemoveGroup(groupPathFollowing);
		}
		Vec2f pos = m_cam.ConvertToWorldSpace(Vec2f(mouseEvent.GetPosX(), mouseEvent.GetPosY()));
		m_EntityMgr->GetPath(player, pos);
	}
}


Game::Game(D2DWindow& window)
	:m_window(window), m_cam((float)window.ScreenWidth(), (float)window.ScreenHeight())
{
	InitECS();
	InitManagers();
	InitText();
	

	//Locator::Audio()->AddSound("ding", L"ding.wav");

	/*FILE* file;
	LevelData data;
	ZeroMemory(&data, sizeof(LevelData));

	std::size_t res = sizeof(Maps::map2_layer0) / sizeof(int);


	for (int c = 0; c < Maps::map1_width*Maps::map1_height; c++)
		data.mapLayers[0][c] = Maps::map1_layer0[c];

	for (int c = 0; c < Maps::map1_width*Maps::map1_height; c++)
		data.mapLayers[1][c] = Maps::map1_layer1[c];

	data.layer_count = 2;
	wsprintf(data.image_path, L"%s", Maps::map1_image_path);
	data.image_size = 32;
	data.cell_width = Maps::map1_cell_width;
	data.cell_height = Maps::map1_cell_height;
	data.width = Maps::map1_width;
	data.height = Maps::map1_height;
	data.armor_count = data.enemy_count = data.potion_count = data.weapons_count = 2;
	data.back_color[0] = 0.0f;
	data.back_color[1] = 0.0f;
	data.back_color[2] = 0.0f;
	data.back_color[3] = 1.0f;

	fopen_s(&file, "test.bin", "wb");
	fwrite(&data, sizeof(LevelData), 1, file);
	fclose(file);*/
	LoadLevel(0);
	InitPlayer();
}


Game::~Game()
{
}

bool Game::Play(SimpleTimer& timer)
{
	static float gameTime = 0;
	gameTime += timer.Time();
	// get future thread completions
	Locator::PathFinding()->checkForDone();
	// game logic
	HRESULT hr = ConstructSceen(timer.Time(), (int)gameTime);
	if (FAILED(hr)) { return false; }
	
	// render to screen
	hr = RenderSceen();
	if (FAILED(hr)) { return false; }
		
	return true;
}

HRESULT Game::ConstructSceen(const float & deltaTime, const int & gameTime)
{
	
	static float timer = 0.0f;
	timer += deltaTime;
	HRESULT hr = S_OK;
	switch (m_gameState)
	{
	case GameState::running:
	{
		HandleUserInput(m_window.mouse.Read(), m_window.kbd.ReadKey());
		m_EntityMgr->Refresh();
		m_EntityMgr->Update(deltaTime);
		

	}
		break;
	case GameState::start:
		
		break;
	}

	
	return hr;
}

HRESULT Game::RenderSceen()
{
	HRESULT hr = S_OK;
	
	hr = Locator::Graphics()->BeginSceen(m_backGroundColor);
	if (FAILED(hr))return hr;
	//~
	switch (m_gameState)
	{
	case GameState::running:
		
		m_EntityMgr->Draw();
		break;
	case GameState::start:
		m_UserInterfaceMgr->Draw();
		break;
	}
	
	
	//~
	Locator::Graphics()->EndSceen();
	return hr;
}


