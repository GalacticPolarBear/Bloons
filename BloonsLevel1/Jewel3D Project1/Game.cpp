#include "Game.h"

bool startpath = false;
Game::Game(ConfigTable &config)
	: Config(config)
{
	EventManager::Subscribe(this, BULLET_COLL);
	EventManager::Subscribe(this, BUILD_COLL);
	EventManager::Subscribe(this, TOWER_COLL);
	EventManager::Subscribe(this, SCREEN_COLL);
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
		auto alienIndex = std::find(AllAliens.begin(), AllAliens.end(), alien);
		auto bulletIndex = std::find(Bullets.begin(), Bullets.end(), bullet);
		AllAliens[alienIndex - AllAliens.begin()]->
		//alien->GetComponent<Alien>()->Health -= bullet.
	}

    if (e->Type == BUILD_COLL)
	{
		//Need to enter build mode if the player has enough money to purchase a tower. 
		//Then create a tower and attach it to the player's cursor. 
		Entity *tower = reinterpret_cast<Entity *>(e->Int1);
		Entity *alien = reinterpret_cast<Entity *>(e->Int2);
		
		//auto alienIndex = std::find(AllAliens.begin(), AllAliens.end(), alien);
		//auto bulletIndex = std::find(Bullets.begin(), Bullets.end(), bullet);
	}

	if (e->Type == SCREEN_COLL)
	{
		PlayerHealth --;
		Entity *remove = static_cast<Entity*>(e->Void);
		auto alienIndex = std::find(AllAliens.begin(), AllAliens.end(), remove);
		MainGroup.RemoveEntity(*remove);
	    AllAliens.erase(alienIndex);
	}
}
void Game::MakeAlienWave(int num, int spacing, Path& path)
{
	if (num == 0)
		return;

	for (int i = 0; i < num; i++)
	{
		AllAliens.push_back(new Entity());

		AllAliens.back()->AddComponent<Sprite>();
		AllAliens.back()->AddComponent<Material>()->Program = SpriteShader;
		AllAliens.back()->GetComponent<Material>()->Textures.push_back(TextureSlot(SpriteTexture, 0));

		AllAliens.back()->GetComponent<Material>()->SetBlendMode(BlendFunc::Linear);
		AllAliens.back()->GetComponent<Sprite>()->SetCenteredX(true);
		AllAliens.back()->GetComponent<Sprite>()->SetCenteredY(true);

		AllAliens.back()->Transform.Scale = (vec3(50, 50, 1));
		AllAliens.back()->Transform.Position = vec3(802, 730 + (i * spacing) + 5,  (float)i / num);

		AllAliens.back()->AddComponent<Alien>();
		AllAliens.back()->GetComponent<Alien>()->AlienPath.SetPath(path);

		MainGroup.AddEntity(*AllAliens.back());
	}
}
void Game::MakeBullet(vec2 & Traj)
{
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
	AlienPath.AddNode(vec2(80, 117));
	
	Tower1.GetComponent<Material>()->SetBlendMode(BlendFunc::Linear);
	Tower1.GetComponent<Sprite>()->SetCenteredX(true);
	Tower1.GetComponent<Sprite>()->SetCenteredY(true);
	Tower1.Transform.Scale = (vec3(50, 50, 1));
	Tower1.Transform.Position = vec3(400, 660, 1);

	Square1.GetComponent<Material>()->SetBlendMode(BlendFunc::Linear);
	Square1.GetComponent<Sprite>()->SetCenteredX(true);
	Square1.GetComponent<Sprite>()->SetCenteredY(true);
	Square1.Transform.Scale = (vec3(53, 53, 1));
	Square1.Transform.Position = vec3(400, 660, 0.3);

	Tower2.GetComponent<Material>()->SetBlendMode(BlendFunc::Linear);
	Tower2.GetComponent<Sprite>()->SetCenteredX(true);
	Tower2.GetComponent<Sprite>()->SetCenteredY(true);
	Tower2.Transform.Scale = (vec3(50, 50, 1));
	Tower2.Transform.Position = vec3(531, 660, 1);

	Square2.GetComponent<Material>()->SetBlendMode(BlendFunc::Linear);
	Square2.GetComponent<Sprite>()->SetCenteredX(true);
	Square2.GetComponent<Sprite>()->SetCenteredY(true);
	Square2.Transform.Scale = (vec3(50, 50, 1));
	Square2.Transform.Position = vec3(531, 660, 0.3);

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
	if (Input::GetKeyBoardButton(Esc))
	{
		Console::Exit();
	}
	
	MousePosText.GetComponent<Text>()->String = "Mouse X = " + std::to_string(Input::GetMouseX()) + " Mouse Y = " + std::to_string(Input::GetMouseY());
		
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
