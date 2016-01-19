#include "Game.h"

#include <Jewel_OS/Windows/Console.h>
#include <Jewel_Input/InputKeyboard.h>
#include <Jewel_Utilities/Logging.h>
#include <Jewel_Utilities/Rendering.h>
#include <Jewel_Sound/SoundSystem.h>
#include <Jewel_Entity/Components/Camera.h>
#include <Jewel_Entity/Components/Material.h>
#include <Jewel_Entity/Components/Sprite.h>
Game::Game(ConfigTable &config)
	: Config(config)
{
}

Game::~Game()
{
	Exit();
}

bool Game::Init()
{
	//Load game assets here...
	if (!AssetLoader.LoadShader("./Assets/Shaders/Default/Sprite.shader", AlienSprite)) return false;
	if (!AssetLoader.LoadSprite("./Assets/Textures/Alien.png", AlienSprite, false)) return false;

	//Setup Sprite with Materials and centered position
	AlienSprite.GetComponent<Material>()->SetBlendMode(BlendFunc::Linear);
	AlienSprite.GetComponent<Sprite>()->SetCenteredX(true);
	AlienSprite.GetComponent<Sprite>()->SetCenteredY(true);
	AlienSprite.Transform.Scale(vec3(50,50,1));
	AlienSprite.Transform.Position = vec3(Input::GetMouseX(), Input::GetMouseY(), 0);
	AlienSprite.AddComponent<Alien>();

	//[11:56:59 AM] Emi: left = -width/2, right = width/2, top = height/2, bottom = -height/2
    //[11:57 : 15 AM] Emi: and far / near as like 1000 and -1000

	//Add to the Rendergroup for display
	MainGroup.AddEntity(AlienSprite);
	//RootNode.Transform.AddChild(AlienSprite.Transform);
	float Top = Console::GetScreenHeight();
	float Bottom = -Console::GetScreenHeight();
	float Left = -Console::GetScreenWidth();
	float Right = Console::GetScreenWidth();

	//Setup Camera
	MainCamera.AddComponent<Camera>()->SetOrthograpic(Top, 0, 0, Right, -1, 1000);

	MainCamera.Transform.Position = vec3(0.0f, 0.0f, 0.0f);
	//MainCamera.Transform.RotateX(-20.0f);

	//Setup up renderer
	MainRenderPass.SetCamera(MainCamera);
	MainRenderPass.SetRenderGroup(MainGroup);
	
	//Setup background color
	SetClearColor(0.35f, 0.7f, 0.9f, 0.0f); //cornflower blue

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
	if (Input::GetKeyBoardButton(A))
	{
		AlienSprite.Transform.Position += vec3(-10, 0,0);
	}
	if (Input::GetKeyBoardButton(S))
	{
		AlienSprite.Transform.Position += vec3(0, -10, 0);
	}
	if (Input::GetKeyBoardButton(W))
	{
		AlienSprite.Transform.Position += vec3(0, 10, 0);
	}
	
	
	//Update game objects here...
	AlienSprite.GetComponent<Alien>()->Update(deltaTime);
	//AlienSprite.Transform.Position = vec3(Input::GetMouseX(), -(Input::GetMouseY() - Console::GetScreenHeight()), 0);
	//Keep sound subsystem up to date
	SoundSystem::Update();
}

void Game::Draw()
{
	ClearBackBuffer();

	MainRenderPass.Render();

	SwapBuffers();
}
