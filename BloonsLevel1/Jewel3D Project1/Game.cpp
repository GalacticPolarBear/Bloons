#include "Game.h"

bool startpath = false;
Game::Game(ConfigTable &config)
	: Config(config)
{
	EventManager::Subscribe(this, BULLET_COLL);
	EventManager::Subscribe(this, TOWER_COLL);
	EventManager::Subscribe(this, SCREEN_COLL);
	EventManager::Subscribe(this, SHOOT_BULLET);
}

Game::~Game()
{
	EventManager::UnSubscribe(this);

	Exit();
}


void Game::EventCallBack(EventData * e)
{
	if (e->Type == TOWER_COLL)
	{
		//Need to add the index from the aliens array as a target for the Tower.
		//Both are received from the Message.
		
	}

	 if (e->Type == BULLET_COLL)
	{
		//Need to perform the damage and delete the projectile.
		//If the damage was enough to kill the Alien we need the index of the alien and the index for the projectile.
		Entity *alien = reinterpret_cast<Entity *>(e->Int2);
		Entity *bullet = reinterpret_cast<Entity *>(e->Int1);
		
	
		//AllAliens[alienIndex - AllAliens.begin()]->
		//alien->GetComponent<Alien>()->Health -= bullet.
	}
	 
	if (e->Type == SCREEN_COLL)
	{
		PlayerHealth --;
		Entity *remove = static_cast<Entity*>(e->Void);
		MainGroup.RemoveEntity(*remove);
	}

	if (e->Type == SHOOT_BULLET)
	{
		PlayerHealth--;
		Entity *remove = static_cast<Entity*>(e->Void);
		MainGroup.RemoveEntity(*remove);
	}

}

void Game::MakeAlienWave(int num, int spacing, Path& path)
{
	if (num == 0)
		return;

	for (int i = 0; i < num; i++)
	{
		Entity * newEnt = new Entity();

		newEnt->AddComponent<Sprite>();
		newEnt->AddComponent<Material>()->Program = SpriteShader;
		newEnt->GetComponent<Material>()->Textures.push_back(TextureSlot(SpriteTexture, 0));
		newEnt->GetComponent<Material>()->SetBlendMode(BlendFunc::Linear);
		newEnt->GetComponent<Sprite>()->SetCenteredX(true);
		newEnt->GetComponent<Sprite>()->SetCenteredY(true);
		newEnt->Transform.Scale = (vec3(50, 50, 1));
		newEnt->Transform.Position = vec3(802, 735 + (i * spacing),  (float)i / num);
		newEnt->AddComponent<Alien>();
		newEnt->GetComponent<Alien>()->AlienPath.SetPath(path);
		newEnt->AddComponent<Collider>(vec2(50,50), ALIEN);
		MainGroup.AddEntity(*newEnt);
	}
}

//Create a Tower and set its position to the Mouse Cursor.
Entity* Game::MakeTower(BuildUnit toBuild)
{
	//Make a Tower 
	Entity * toReturn = new Entity();
	toReturn->AddComponent<Sprite>();
	toReturn->AddComponent<Material>()->Program = TowerShader;
	
	if (toBuild == TOWERRED)
		toReturn->GetComponent<Material>()->Textures.push_back(TextureSlot(TowerRed, 0));
	else
		toReturn->GetComponent<Material>()->Textures.push_back(TextureSlot(TowerBlue, 0));
	
	toReturn->GetComponent<Material>()->SetBlendMode(BlendFunc::Linear);
	toReturn->GetComponent<Sprite>()->SetCenteredX(true);
	toReturn->GetComponent<Sprite>()->SetCenteredY(true);
	toReturn->Transform.Scale = (vec3(50, 50, 1));
	toReturn->Transform.Position = vec3(Input::GetMouseX(), Input::GetMouseY(), 1);
	toReturn->AddComponent<Tower>();
	toReturn->AddComponent<Collider>(vec2(50, 50), TOWER);

	return toReturn;
}

//Did we collide with a UI element?
bool Game::CheckTower()
{
	for (auto ui : UI)
	{
		if (ui->GetComponent<Collider>()->CheckPointCollision(vec2(Input::GetMouseX(), Input::GetMouseY())))
		{
			if (PlayerGold >= ui->GetComponent<Tower>()->Cost)
			{
				return true;
			}
		}
	}

	return false;
}

Entity* Game::MakeBullet(vec3& startPos, vec2 & traj)
{
	//Make a Bullet 
	Entity * toReturn = new Entity();
	toReturn->AddComponent<Sprite>();
	toReturn->AddComponent<Material>()->Program = ProjShader;
	toReturn->GetComponent<Material>()->Textures.push_back(TextureSlot(ProjTexture, 0));
	
	toReturn->GetComponent<Material>()->SetBlendMode(BlendFunc::Linear);
	toReturn->GetComponent<Sprite>()->SetCenteredX(true);
	toReturn->GetComponent<Sprite>()->SetCenteredY(true);
	toReturn->Transform.Scale = (vec3(9, 19, 1));
	toReturn->AddComponent<Collider>(vec2(9, 19), BULLET);

	return toReturn;
}


bool Game::Init()
{
	//Load game assets here...
	
	if (!AssetLoader.LoadFont("./Assets/Fonts/georgia_64.font", MousePosText)) return false;
	if (!AssetLoader.LoadShader("./Assets/Shaders/Default/Font.shader", MousePosText)) return false;

	if (!AssetLoader.LoadFont("./Assets/Fonts/georgia_64.font", HealthText)) return false;
	if (!AssetLoader.LoadShader("./Assets/Shaders/Default/Font.shader", HealthText)) return false;

	if (!AssetLoader.LoadFont("./Assets/Fonts/georgia_64.font", GoldText)) return false;
	if (!AssetLoader.LoadShader("./Assets/Shaders/Default/Font.shader", GoldText)) return false;

	if (!AssetLoader.LoadSprite("./Assets/Textures/BloonsBGPSD.png", GameBG)) return false;
	if (!AssetLoader.LoadShader("./Assets/Shaders/Default/Sprite.shader", GameBG)) return false;

	if (!AssetLoader.LoadSprite("./Assets/Textures/GnomeRed.png", Tower1)) return false;
	if (!AssetLoader.LoadShader("./Assets/Shaders/Default/Sprite.shader", Tower1)) return false;

	if (!AssetLoader.LoadSprite("./Assets/Textures/GnomeBlue.png", Tower2)) return false;
	if (!AssetLoader.LoadShader("./Assets/Shaders/Default/Sprite.shader", Tower2)) return false;

	if (!AssetLoader.LoadSprite("./Assets/Textures/DisplaySquare.png", Square1)) return false;
	if (!AssetLoader.LoadShader("./Assets/Shaders/Default/Sprite.shader", Square1)) return false;

	if (!AssetLoader.LoadSprite("./Assets/Textures/DisplaySquare.png", Square2)) return false;
	if (!AssetLoader.LoadShader("./Assets/Shaders/Default/Sprite.shader", Square2)) return false;
	
	GameBG.GetComponent<Material>()->SetBlendMode(BlendFunc::Linear);
	GameBG.Transform.Position = vec3(0, 0, 0);

	SpriteTexture = AssetLoader.LoadTexture("./Assets/Textures/Alien.png");
	SpriteShader = AssetLoader.LoadShader("./Assets/Shaders/Default/Sprite.shader");

	TowerRed = AssetLoader.LoadTexture("./Assets/Textures/GnomeRed.png");
	TowerShader = AssetLoader.LoadShader("./Assets/Shaders/Default/Sprite.shader");
	
	TowerBlue = AssetLoader.LoadTexture("./Assets/Textures/GnomeBlue.png");
	
	ProjTexture = AssetLoader.LoadTexture("./Assets/Textures/shroomProjectile.png");
	ProjShader = AssetLoader.LoadShader("./Assets/Shaders/Default/Sprite.shader");
	
	
	if (!SpriteTexture) return false;
	if (!SpriteShader) return false;

	GameGrid.Generate();
	GameGrid.SetPathOccupied("./Assets/TextFiles/pathCoords.txt");

	//Setup Font Properties
	MousePosText.GetComponent<Material>()->SetBlendMode(BlendFunc::Linear);
	MousePosText.GetComponent<Text>()->ScaleX = 0.5f;
	MousePosText.GetComponent<Text>()->ScaleY = 0.5f;
	MousePosText.Transform.Position = vec3(50, 50, 1);

	HealthText.GetComponent<Material>()->SetBlendMode(BlendFunc::Linear);
	HealthText.GetComponent<Text>()->ScaleX = 0.25f;
	HealthText.GetComponent<Text>()->ScaleY = 0.25f;
	HealthText.Transform.Position = vec3(108, 675, 1);
	HealthText.GetComponent<Text>()->String = "Lives Left: " + std::to_string(PlayerHealth);

	GoldText.GetComponent<Material>()->SetBlendMode(BlendFunc::Linear);
	GoldText.GetComponent<Text>()->ScaleX = 0.25f;
	GoldText.GetComponent<Text>()->ScaleY = 0.25f;
	GoldText.Transform.Position = vec3(108, 645, 1);
	GoldText.GetComponent<Text>()->String = "Gold: " + std::to_string(PlayerGold);
	
	//Setup Entity Properties
	Path AlienPath;
	AlienPath.AddNode(vec2(802, 720));
	AlienPath.AddNode(vec2(810, 652));
	AlienPath.AddNode(vec2(1058, 648));
	AlienPath.AddNode(vec2(1079, 220));
	AlienPath.AddNode(vec2(734, 250));
	AlienPath.AddNode(vec2(608, 512));
	AlienPath.AddNode(vec2(349, 493));
	AlienPath.AddNode(vec2(348, 143));
	AlienPath.AddNode(vec2(0, 117));
	
	Tower1.GetComponent<Material>()->SetBlendMode(BlendFunc::Linear);
	Tower1.GetComponent<Sprite>()->SetCenteredX(true);
	Tower1.GetComponent<Sprite>()->SetCenteredY(true);
	Tower1.Transform.Scale = (vec3(50, 50, 1));
	Tower1.Transform.Position = vec3(400, 660, 1);

	Square1.GetComponent<Material>()->SetBlendMode(BlendFunc::Linear);
	Square1.GetComponent<Sprite>()->SetCenteredX(true);
	Square1.GetComponent<Sprite>()->SetCenteredY(true);
	Square1.Transform.Scale = (vec3(53, 53, 1));
	Square1.AddComponent<Tower>();
	Square1.AddComponent<Collider>(vec2(53, 53), UIELEMENT);
	Square1.Transform.Position = vec3(400, 660, 0.3);

	Tower2.GetComponent<Material>()->SetBlendMode(BlendFunc::Linear);
	Tower2.GetComponent<Sprite>()->SetCenteredX(true);
	Tower2.GetComponent<Sprite>()->SetCenteredY(true);
	Tower2.Transform.Scale = (vec3(50, 50, 1));
	Tower2.Transform.Position = vec3(531, 660, 1);
	
	Square2.GetComponent<Material>()->SetBlendMode(BlendFunc::Linear);
	Square2.GetComponent<Sprite>()->SetCenteredX(true);
	Square2.GetComponent<Sprite>()->SetCenteredY(true);
	Square2.Transform.Scale = (vec3(53, 53, 1));
	Square2.AddComponent<Collider>(vec2(53, 53), UIELEMENT);
	Square2.AddComponent<Tower>()->Cost = 200;
	Square2.Transform.Position = vec3(531, 660, 0.3);

	UI.push_back(&Square1);
	UI.push_back(&Square2);
	

	//Add to be rendered.
	MainGroup.AddEntity(GameBG);
	MainGroup.AddEntity(MousePosText);
	MainGroup.AddEntity(GoldText);
	MainGroup.AddEntity(HealthText);
	MainGroup.AddEntity(Square1);
	MainGroup.AddEntity(Square2);
	MainGroup.AddEntity(Tower1);
	MainGroup.AddEntity(Tower2);
	MakeAlienWave(30, 20, AlienPath);

	//Setup Camera
	MainCamera.AddComponent<Camera>()->SetOrthograpic(Console::GetScreenHeight(), 0, 0, Console::GetScreenWidth(), -1, 1000);
	MainCamera.Transform.Position = vec3(0.0f, 0.0f, 0.0f);
	
	//Setup up renderer
	MainRenderPass.SetCamera(MainCamera);
	MainRenderPass.SetGroup(MainGroup);
	
	//Setup background color
	//SetClearColor(0.35f, 0.7f, 0.9f, 0.0f); //cornflower blue
	SetClearColor(0,0,0, 1);
	return true;
}

void Game::Exit()
{
	AssetLoader.Unload();
}

void Game::Update(float deltaTime)
{
		
	if (BuildMode)
	{
		if (Input::GetMouseButton(LButton) && CanPlaceTower)
		{
			if (GameGrid.CanBuild(vec2(Input::GetMouseX(), Input::GetMouseY())))
			{
				ToBuild->Transform.Position = vec3(Input::GetMouseX(), Input::GetMouseY(), 1);
				GameGrid.SetAreaOccupied(vec2(Input::GetMouseX(), Input::GetMouseY()));
				//PlayerGold -= ToBuild->GetComponent<Tower>()->Cost;
				MainGroup.RemoveEntity(*ToBuild);
				Towers.push_back(ToBuild);
				MainGroup.AddEntity(*Towers.back());
				ToBuild = nullptr;
				CanPlaceTower = false;
				BuildMode = false;
			}
		}
		
		else if (!Input::GetMouseButton(LButton))
		{
			CanPlaceTower = true;
		}
	}

	else
	{
		if (Input::GetMouseButton(LButton) && CheckTower())
		{
			BuildMode = true;
			ToBuild = MakeTower(TOWERRED);
			MainGroup.AddEntity(*ToBuild);
		}
	}

	//Exit Build Mode
	if (Input::GetKeyBoardButton(Esc))
	{
		BuildMode = false;
		MainGroup.RemoveEntity(*ToBuild);
		ToBuild = nullptr;
	}

	if (Input::GetKeyBoardButton(Space))
	{
		startpath = !startpath;
	}
	
	if (startpath) 
	{
		
		auto aliens = Alien::GetAll();

		for (auto alien : aliens)
		{
			alien->Update(deltaTime);
		}
	}
	
	EventManager::DrainEventQueue();

	if (ToBuild != nullptr)
	{
		ToBuild->Transform.Position = vec3(Input::GetMouseX(), Input::GetMouseY(), 1);
	}
	
	Tower1.Transform.RotateZ(.5);
	Tower2.Transform.RotateZ(.5);

	HealthText.GetComponent<Text>()->String = "Lives Left: " + std::to_string(PlayerHealth);
	GoldText.GetComponent<Text>()->String = "Gold: " + std::to_string(PlayerGold);
	
	SoundSystem::Update();
}

void Game::Draw()
{
	ClearBackBuffer();

	MainRenderPass.Render();

	SwapBuffers();
}
