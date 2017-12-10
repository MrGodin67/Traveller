#include "stdafx.h"
#include "Game.h"
#include "SimpleTimer.h"
#include "D2DWindow.h"
#include "FileManager.h"
#include "MapTest.h"
//Private functions
void Game::InitECS()
{
	m_EntityMgr = MakeUnique<EntityManager>(m_cam);
	
	Entity::SetManager(m_EntityMgr.get());
	/*chest = &m_EntityMgr->Add<Chest>();
	chest->Init( TextureLoader::Load(L"assets\\window.png"), RectF(0, 0, 64, 64), Vec2f(74.0f,74.0f), Vec2f(64,64), 1);
	Weapon* weapon1 = &chest->Add<Weapon>(WeaponSubTypes::Sword, TextureLoader::Load(L"assets\\window.png"), RectF(64,64,128,128), RectF(400,300,474,374),
		 L"what is this crap", L"No magic here a hole");
	*/
	testActor = &m_EntityMgr->Add<Actor>(Vec2f(100.0f, 100.0f), Vec2f(48.0f, 48.0f));
	testActor2 = &m_EntityMgr->Add<Actor>(Vec2f(150.0f, 100.0f), Vec2f(48.0f, 48.0f));
	testActor3 = &m_EntityMgr->Add<Actor>(Vec2f(200.0f, 100.0f), Vec2f(48.0f, 48.0f));
	testActor->Add<InputController>(m_window.kbd);
	testActor->Get<Transform>().acceleration = 75.0f;
	testActor2->Get<Transform>().acceleration = 50.0f;
	testActor3->Get<Transform>().acceleration = 50.0f;
	
	testActor->Add<Collider>(Vec2f(124.0f, 124.0f), Vec2f(24.0f, 24.0f));
	testActor2->Add<Collider>(Vec2f(174.0f, 124.0f), Vec2f(24.0f, 24.0f));
	testActor2->Add<FollowCompanion>(testActor,300.0f);
	testActor3->Add<Collider>(Vec2f(224.0f, 124.0f), Vec2f(24.0f, 24.0f));
	testActor3->Add<FollowCompanion>(testActor2, 300.0f);
	

	testActor->Add<Light>(300.0f);
	
	testActor->AddGroup(groupPlayers);
	testActor->AddGroup(groupLight);
	testActor->AddGroup(groupCollider);
	testActor->AddGroup(groupMapLayer1); 
	testActor2->AddGroup(groupMapLayer1);
	testActor2->AddGroup(groupPlayers);
	testActor2->AddGroup(groupCollider);
	testActor3->AddGroup(groupPlayers);
	testActor3->AddGroup(groupCollider);
	testActor3->AddGroup(groupMapLayer1);
	Item i;
	i.image = TextureLoader::Load(L"assets\\charatures.png");
	i.srcRect = { 0.0f,0.0f,32.0f,32.0f };
	testActor->AddItem(i, EquippedItems::body);
	testActor2->AddItem(i, EquippedItems::body);
	testActor3->AddItem(i, EquippedItems::body);
	i.srcRect = { 0.0f,32.0f,32.0f,64.0f };
	Item* armor1 = testActor->AddItem(i, EquippedItems::armor);
	
	i.srcRect = { 0.0f,3*32.0f,32.0f,4*32.0f };
	testActor->AddItem(i, EquippedItems::gloves);

	i.srcRect = { 0.0f,4 * 32.0f,32.0f,5 * 32.0f };
	testActor->AddItem(i, EquippedItems::boots);
	i.srcRect = { 2*32.0f,5 * 32.0f,3*32.0f,6 * 32.0f };
	testActor->AddItem(i, EquippedItems::helm);

	i.image = TextureLoader::Load(L"assets\\weapons.png");
	i.srcRect = { 32.0f*7,4 * 32.0f,32.0f*8,5 * 32.0f };
	Item* it = testActor->AddItem(i, EquippedItems::weapon);
	i.srcRect = { 32.0f * 7,5 * 32.0f,32.0f * 8,6 * 32.0f };
	testActor3->AddItem(i, EquippedItems::weapon);
	int x = 0;
	
}

void Game::LoadLevel(const unsigned int& index)
{
	LevelData data;
	FileManager::ReadLevelFile(mapNames[index], data);
	ID2D1Bitmap* m_image = TextureLoader::Load(data.image_path);
	Assert(m_image);
	MapLayer::SetValues(m_image, data.width, data.height, data.image_size,64, data.cell_width, data.cell_height, -1);
	MapLayer::Load(data.mapLayer1, *m_EntityMgr.get(), groupMapLayer1);
	MapLayer::SetValues(m_image, data.width, data.height, data.image_size, 32, data.cell_width, data.cell_height, -1);
	MapLayer::Load(data.mapLayer2, *m_EntityMgr.get(), groupMapLayer2);
	
	m_cam.ConfineToMap(RectF(0.0f, 0.0f, (float)data.width * (float)data.cell_width,
		(float)data.height * (float)data.cell_height));
	m_cam.UpdatePosition(Vec2f(0.0f, 0.0f));
	m_backGroundColor = RectF(data.back_color[0], data.back_color[1], data.back_color[2], data.back_color[3]);
}

void Game::InitUI()
{
	m_UserInterfaceMgr = MakeUnique<UserInterfaceManager>();
	m_UserInterfaceMgr->SetCurrentWindow("start");
}



void Game::InitText()
{
	m_textMgr = MakeUnique<TextManager>();
	m_textMgr->InitializeFont("Tahoma8",FontPair(L"Tahoma",8.0f ));
	m_textMgr->InitializeFont("Tahoma10", FontPair(L"Tahoma", 10.0f));
	m_textMgr->InitializeFont("Tahoma12", FontPair(L"Tahoma", 12.0f));
	m_textMgr->InitializeFont("Tahoma14", FontPair(L"Tahoma", 14.0f));
	m_textMgr->InitializeFont("Tahoma16", FontPair(L"Tahoma", 16.0f));
	m_textMgr->InitializeFont("Tahoma18", FontPair(L"Tahoma", 18.0f));
	m_textMgr->InitializeFont("Tahoma20", FontPair(L"Tahoma", 20.0f));
	m_textMgr->InitializeFont("Tahoma22", FontPair(L"Tahoma", 22.0f));
	Locator::SetTextManager(m_textMgr.get());
}

void Game::HandleUserInput(Mouse::Event & mouseEvent, Keyboard::Event & kbdEvent)
{
	static int x = 0;
	static int y = 0;
	
	float speed = 14.0f;
	if (m_window.kbd.KeyIsPressed(VK_UP))
		testActor->Get<Transform>().velocity.y = -speed;
	else if (m_window.kbd.KeyIsPressed(VK_DOWN))
		testActor->Get<Transform>().velocity.y = speed;
	else if (m_window.kbd.KeyIsPressed(VK_LEFT))
		testActor->Get<Transform>().velocity.x = -speed;
	else if (m_window.kbd.KeyIsPressed(VK_RIGHT))
		testActor->Get<Transform>().velocity.x = speed;
	else
		testActor->Get<Transform>().velocity = { 0.0f, 0.0f };
	//testActor->Get<Transform>().velocity = vel;
	
	
	UIReturn result;
	m_UserInterfaceMgr->OnMouseMove(m_window.mouse.GetPosX(),m_window.mouse.GetPosY());
	if (mouseEvent.GetType() == Mouse::Event::LRelease)
	{
		result = m_UserInterfaceMgr->OnMouseClick(mouseEvent.GetPosX(), mouseEvent.GetPosY());
		if (result.action != UI_RETURN_ACTION_NONE)
		{
			
			
			switch (result.action)
			{
			case UI_RETURN_ACTION_EXIT:
				PostQuitMessage(0);
				break;
			};
		}
	}
}


Game::Game(D2DWindow& window)
	:m_gfx(), m_window(window), m_cam((float)window.ScreenWidth(), (float)window.ScreenHeight())
{
	Locator::SetGraphics(&m_gfx);
	InitECS();

	InitUI();
	InitText();
	



	FILE* file;
	LevelData data;
	ZeroMemory(&data, sizeof(LevelData));

	std::size_t res = sizeof(Maps::map2_layer0) / sizeof(int);


	for (int c = 0; c < Maps::map1_width*Maps::map1_height; c++)
		data.mapLayer1[c] = Maps::map1_layer0[c];

	for (int c = 0; c < Maps::map1_width*Maps::map1_height; c++)
		data.mapLayer2[c] = Maps::map1_layer1[c];

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
	fclose(file);
	LoadLevel(0);
	
}


Game::~Game()
{
}

bool Game::Play(SimpleTimer& timer)
{
	static float gameTime = 0;
	gameTime += timer.Time();
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
	
	
	HRESULT hr = S_OK;
	switch (m_gameState)
	{
	case GameState::running:
		m_EntityMgr->Refresh(); // remove all tagged Entities
		
		
		//testActor->Update(deltaTime);
		//m_cam.UpdatePosition(testActor->Get<Transform>().position);
		//testActor->Get<Transform>().Translate(-m_cam.GetPosition());
		m_EntityMgr->Update(deltaTime);
	
		
		break;
	case GameState::start:
		HandleUserInput(m_window.mouse.Read(), m_window.kbd.ReadKey());
		break;
	}

	
	return hr;
}

HRESULT Game::RenderSceen()
{
	HRESULT hr = S_OK;
	
	hr = m_gfx.BeginSceen(m_backGroundColor);
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
	m_gfx.EndSceen();
	return hr;
}


