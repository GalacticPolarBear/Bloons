#include "Game.h"

#include <Jewel_OS/Windows/Console.h>
#include <Jewel_Input/InputKeyboard.h>
#include <Jewel_Utilities/Logging.h>
#include <Jewel_Utilities/Rendering.h>
#include <Jewel_Sound/SoundSystem.h>
#include <Jewel_Entity/Components/Camera.h>
#include <Jewel_Entity/Components/Material.h>
#include <Jewel_Entity/Components/Sprite.h>
#include <Jewel_Entity/Components/Text.h>
#include <Jewel_Utilities\Random.h>
#include <Jewel_Rendering\Primitives.h>
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

	if (!AssetLoader.LoadFont("./Assets/Fonts/georgia_64.font", MousePosText)) return false;
	if (!AssetLoader.LoadShader("./Assets/Shaders/Default/Font.shader", MousePosText)) return false;
	
	//Setup Font Properties
	MousePosText.GetComponent<Material>()->SetBlendMode(BlendFunc::Linear);
	MousePosText.GetComponent<Text>()->String="fuck is this?";
	MousePosText.GetComponent<Text>()->ScaleX = 0.5f;
	MousePosText.GetComponent<Text>()->ScaleY = 0.5f;


	//Setup Sprite with Materials and centered position
	AlienSprite.GetComponent<Material>()->SetBlendMode(BlendFunc::Linear);
	AlienSprite.GetComponent<Sprite>()->SetCenteredX(true);
	AlienSprite.GetComponent<Sprite>()->SetCenteredY(true);
	AlienSprite.Transform.Scale(vec3(50,50,1));
	AlienSprite.Transform.Position = vec3(802, 720,0);
	AlienSprite.AddComponent<Alien>();

	
	
	//AlienSprite.GetComponent<Alien>()->AlienPath.AddNode(vec2(802,720));
	AlienSprite.GetComponent<Alien>()->AlienPath.AddNode(vec2(810,652));
	AlienSprite.GetComponent<Alien>()->AlienPath.AddNode(vec2(1058,648));
	AlienSprite.GetComponent<Alien>()->AlienPath.AddNode(vec2(1079,220));
	AlienSprite.GetComponent<Alien>()->AlienPath.AddNode(vec2(734,250));
	AlienSprite.GetComponent<Alien>()->AlienPath.AddNode(vec2(608,512));
	AlienSprite.GetComponent<Alien>()->AlienPath.AddNode(vec2(349,493));
	AlienSprite.GetComponent<Alien>()->AlienPath.AddNode(vec2(348,143));
	AlienSprite.GetComponent<Alien>()->AlienPath.AddNode(vec2(0,117));
	
	
	//Add to the Rendergroup for display
	MainGroup.AddEntity(AlienSprite);
	MainGroup.AddEntity(MousePosText);
	
	//Setup Camera
	MainCamera.AddComponent<Camera>()->SetOrthograpic(Console::GetScreenHeight(), 0, 0, Console::GetScreenWidth(), -1, 1000);
	MainCamera.Transform.Position = vec3(0.0f, 0.0f, 0.0f);
	
	//Setup up renderer
	MainRenderPass.SetCamera(MainCamera);
	MainRenderPass.SetGroup(MainGroup);
	
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
	
	MousePosText.GetComponent<Text>()->String = "Mouse X = " + std::to_string(Input::GetMouseX()) + " Mouse Y = " + std::to_string(Input::GetMouseY());
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

	MainCamera.GetComponent<Camera>()->Bind();
	auto points = AlienSprite.GetComponent<Alien>()->AlienPath.GetNodes();

	for (int i = 0; i < points.size() - 1; ++i)
	{
		Primitives::DrawLine(vec3(points[i].x, points[i].y, 0), vec3(points[i + 1].x, points[i + 1].y, 0), vec4(0, 0, 1, 1));
	}
	SwapBuffers();
}
