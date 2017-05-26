#include "StageState.h"
#include "Game.h"
#include "InputManager.h"
#include "Camera.h"
#include "DialogWindow.h"
#include "SaveComponent.h"
#include <iostream>


TileMap* StageState::tileMap;
GameObject* StageState::player = nullptr;
std::vector<std::unique_ptr<GameObject>> StageState::objectArray = std::vector<std::unique_ptr<GameObject>>();
std::vector<std::unique_ptr<Window>> StageState::windowArray;
std::unordered_map<int, TileMap*> StageState::roomTable;
int** StageState::roomArray;

StageState::StageState(int sizeX, int sizeY):
	healthBar("healthBar2.png",5,15,10)
{
	int random;
	bool endRandom;
	srand(time(NULL));
	SaveComponent _("teste.txt");

	roomArray = new int[sizeX][sizeY];

	//Inicializa a array de salas
	for(int i = 0; i < sizeX; i++){
		for(int j = 0; j < sizeY; j++){
			roomArray[i][j] = -1;
		}
	}

	roomArray[0][0] = 0;

	for(int i = 0; i < sizeX; i++){
		for(int j = 0; j < sizeY; j++){

		}
	}

	tileSet = new TileSet(64, 64, "tileset3d2.png", 9, 9);
	tileMap = new TileMap("resources/map/tileMap.txt", tileSet);
	//Camera::GetInstance().maxPos = Vec2(tileMap.m_nodes[0]->m_data.tileMap->GetWidth()*tileMap.m_nodes[0]->m_data.tileMap->GetTileWidth(),
	//									tileMap.m_nodes[0]->m_data.tileMap->GetHeight()*tileMap.m_nodes[0]->m_data.tileMap->GetTileHeight());
	player = new Gallahad(200, 1000);
	Camera::GetInstance().Follow(player);
	AddObject(player);
	AddObject(new Notfredo(800, 1280));
}

StageState::~StageState()
{
	delete roomArray;
	music.Stop();
	player = nullptr;
	objectArray.clear();
	windowArray.clear();
}

TileMap* StageState::GetTileMap()
{
	return tileMap;
}

GameObject* StageState::GetPlayer()
{
	return player;
}

void StageState::AddObject(GameObject* ptr)
{
	objectArray.emplace_back(ptr);
}

void StageState::AddObjectAsFirst(GameObject* ptr)
{
	objectArray.emplace(objectArray.begin(), ptr);
}

void StageState::RemoveObject(GameObject* ptr)
{
	for(unsigned i = 0; i < objectArray.size(); i++)
	{
		if(ptr == objectArray.at(i)->Get())
		{
			objectArray.erase(objectArray.begin()+i);
			break;
		}
	}
}

void StageState::AddWindow(Window* ptr)
{
	windowArray.emplace_back(ptr);
}

bool StageState::IsColliding(Rect a, Rect b)
{
	return (((a.x+a.w >= b.x) && (a.x <= b.x+b.w)) && ((a.y+a.h >= b.y) && (a.y <= b.y+b.h)));
}

void StageState::Pause()
{
	paused = true;
}

void StageState::Resume()
{
	paused = false;
}

void StageState::LoadAssets()
{
	music.Open("stageState.ogg");
	bg.Open("LancelotIdle.png");
	bg.Open("LancelotRunning.png");
	bg.Open("notattack.png");
	bg.Open("healthBar.png");
	bg.Open("stealthBar.png");
	bg.Open("NotfredoRunning.png");
	bg.Open("NotfredoIdle.png");
	bg.Open("tileset3d2.png");
	music.Play(-1);
}

void StageState::Update()
{
	if(InputManager::GetInstance().KeyPress(SDLK_ESCAPE))
	{
		quitRequested = true;
	}
	if(InputManager::GetInstance().KeyPress(SDLK_RETURN))
	{
		if(paused)
			Resume();
		else
			Pause();
	}

	//Teste do sistema de janelas
	if(InputManager::GetInstance().KeyPress(SDLK_j))
	{
		AddWindow(new DialogWindow(0, 512, 512, 640, "uhaeuh aeuheauh aeuheauh euhuhe huaheuhua ehueah uea hueah eueuhaauhea ehuauehe uhaeuhuha euhea"));
	}

	if(!paused)
	{
		for(unsigned i = 0; i < objectArray.size(); i++)
		{
			objectArray.at(i)->Update(Game::GetInstance().GetDeltaTime());
		}
		for(unsigned i = 0; i < objectArray.size(); i++)
		{
			for(unsigned j = i+1; j < objectArray.size(); j++)
			{
				if(objectArray.at(j)->Is("Animation"))
				{

				}
				else if(IsColliding(objectArray.at(i)->box, objectArray.at(j)->box))
				{
					objectArray.at(i)->NotifyObjectCollision(objectArray.at(j)->Get());
					objectArray.at(j)->NotifyObjectCollision(objectArray.at(i)->Get());
				}
			}
		}
		for(unsigned i = 0; i < objectArray.size(); i++)
		{
			if(objectArray.at(i)->IsDead())
			{
				if(objectArray.at(i)->Get() == Camera::GetInstance().GetFocus())
					Camera::GetInstance().Unfollow();
				if(objectArray.at(i)->Get() == player)
					player = nullptr;
				objectArray.erase(objectArray.begin()+i);
			}
		}

		Gallahad* p = (Gallahad*) player;
		if(player)
			healthBar.SetPercentage(p->GetHealth()/10.0);
		else
			healthBar.SetPercentage(0);

		Camera::GetInstance().Update(Game::GetInstance().GetDeltaTime());
	}
}

void StageState::Render() {
	tileMap->RenderLayer(0, Camera::GetInstance().pos.x, Camera::GetInstance().pos.y);
	for(unsigned int i = 0; i < objectArray.size(); i++)
		objectArray.at(i)->Render();
	tileMap->RenderLayer(1, Camera::GetInstance().pos.x, Camera::GetInstance().pos.y);
	for(unsigned int i = 0; i < windowArray.size(); i++)
		windowArray.at(i)->Render();
	healthBar.Render(10,10);
}

bool StageState::QuitRequested()
{
	return quitRequested;
}

bool StageState::Is(std::string type)
{
	return (type == "Stage");
}

StageState* StageState::get()
{
	return this;
}
