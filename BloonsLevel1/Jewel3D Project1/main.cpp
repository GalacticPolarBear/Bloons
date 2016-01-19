#include <Jewel_OS/Windows/Console.h>
#include <Jewel_OS/EventManager.h>
#include <Jewel_Rendering/Primitives.h>
#include <Jewel_Resource/TextureData.h>
#include <Jewel_Resource/ConfigTable.h>
#include <Jewel_Sound/SoundSystem.h>
#include <Jewel_Input/InputKeyboard.h>
#include <Jewel_Utilities/Logging.h>
#include <Jewel_Utilities/Random.h>

#include "Game.h"

using namespace Jwl;

Game *TheGame = nullptr;

void Update(float deltaTime)
{
	TheGame->Update(deltaTime);
}

void Draw()
{
	TheGame->Draw();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
#ifdef _DEBUG
	CreateConsoleWindow();
#endif

	Log("-Started Execution-");

	//Register default configuration values
	ConfigTable config;
	config.SetDefaultBool("bordered", true);
	config.SetDefaultBool("resizable", false);
	config.SetDefaultBool("fullscreen", false);
	config.SetDefaultBool("vsync", false);
	config.SetDefaultInt("resolution_x", 1280);
	config.SetDefaultInt("resolution_y", 720);
	config.SetDefaultInt("openGL_Major", 3);
	config.SetDefaultInt("openGL_Minor", 3);
	config.SetDefaultInt("MSAA", 1);
	config.SetDefaultString("texture_filter", "trilinear");
	config.SetDefaultInt("anisotropic_level", 2);

	if (!config.LoadConfig("./Settings.cfg"))
	{
		Warning("Could not load \"Settings.cfg\". Generating a new default.");

		if (!config.SaveConfig("./Settings.cfg"))
		{
			Warning("Failed to Generate a new Settings.cfg file.");
		}
	}

	/* Resolve 'auto' settings */
	RECT desktop;
	bool desktopResolutionOkay = GetWindowRect(GetDesktopWindow(), &desktop);

	if (config.GetInt("resolution_x") == 0)
	{
		config.SetInt("resolution_x", desktopResolutionOkay ? desktop.right : 1280);
	}

	if (config.GetInt("resolution_y") == 0)
	{
		config.SetInt("resolution_y", desktopResolutionOkay ? desktop.bottom : 720);
	}

	//Apply texture Settings
	{
		TextureData::SetDefaultAnisotropicLevel(config.GetFloat("anisotropic_level"));

		std::string filterMode = config.GetString("texture_filter");
		if (filterMode == "trilinear")
		{
			TextureData::SetDefaultFilterMode(TextureFilterMode::Trilinear);
		}
		else if (filterMode == "bilinear")
		{
			TextureData::SetDefaultFilterMode(TextureFilterMode::Bilinear);
		}
		else if (filterMode == "linear")
		{
			TextureData::SetDefaultFilterMode(TextureFilterMode::Linear);
		}
		else
		{
			TextureData::SetDefaultFilterMode(TextureFilterMode::Point);
		}
	}
	
	//Seed RNG
	SeedRandomNumberGenerator();

	/* Initialize Core Systems */
	if (!Console::Init(hInstance))
	{
		return EXIT_FAILURE;
	}
	Log("Initialized Console.");

	if (!EventManager::Init())
	{
		return EXIT_FAILURE;
	}
	Log("Initialized Event Manager.");

	if (!Input::Init())
	{
		return EXIT_FAILURE;
	}
	Log("Initialized Input.");

	if (!SoundSystem::Init())
	{
		return EXIT_FAILURE;
	}
	Log("Initialized Sound System.");

	Console::SetVSync(config.GetBool("vsync"));
	
	/* Create Window */
	if (!Console::CreateGameWindow("Jewel3D Project", 
		config.GetInt("resolution_x"), config.GetInt("resolution_y"), 
		config.GetBool("fullscreen"), config.GetBool("bordered"), config.GetBool("resizable"),
		config.GetInt("openGL_Major"), config.GetInt("openGL_Minor")))
	{
		MoveConsoleWindowToForeground();
		ErrorBox("Failed to create window. See \"Log_Output.txt\" for details.");
		return EXIT_FAILURE;
	}
	Log("Initialized Window. ( OpenGL " + Console::GetOpenGLVersionString() + " )");

	if (!Primitives::Load())
	{
		return EXIT_FAILURE;
	}
	Log("Initialized Primitives.");

	/* Initialize Game */
	TheGame = new Game(config);
	if (!TheGame->Init())
	{
		ErrorBox("Failed to initialize Game. See \"Log_Output.txt\" for details.");
		return EXIT_FAILURE;
	}
	Log("Initialized Game.");

	/* Start Game Loop */
	Console::GameLoop(&Update, &Draw);

	Log("Clean up...");
	delete TheGame;
	Primitives::Unload();
	SoundSystem::Unload();
	Input::Unload();
	EventManager::Unload();
	Console::Unload();

	Log("-Execution Finished-");

#ifdef _DEBUG
	DestroyConsoleWindow();
#endif

	return EXIT_SUCCESS;
}
