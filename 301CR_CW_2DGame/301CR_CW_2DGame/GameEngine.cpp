#include "GameEngine.h"
#include "EventHandler.h"
#include "Data_Sub.h"

Graphic_Sub graphics;
Input_Sub input;
bool GameEngine::isRunning;
Score_Sub scores;
Sound_Sub sounds;
UI_Sub UIs;
//Cons & Destrucor
GameEngine::GameEngine()
{
	std::cout << "Game is running" << std::endl;
	GameEngine::isRunning = true;
	scores.InitScore("Data/Highscore.html");
	graphics.InitGraphicsLua(Data_Sub::GetLuaFile("Data/window.lua"));
	graphics.InitModels(Data_Sub::GetLuaFile("Data/level1.lua"));
	
	sounds.InitSound(Data_Sub::GetLuaFile("Data/sound.lua"));
	UIs.InitUI(Data_Sub::GetLuaFile("Data/UI.lua"));
	input.InitInput(Data_Sub::GetLuaFile("Data/controls.lua"));

	Update();
}

GameEngine::~GameEngine()
{
	scores.~Score_Sub();
}




void GameEngine::Update()
{
	while (isRunning)
	{
		input.UpdateSubsystem();
		graphics.UpdateSubsystem();
		scores.UpdateSubsystem();
		sounds.UpdateSubsystem();
		UIs.UpdateSubsystem();
		Event_Handler();
		EventHandler::ClearEvent();
	}
}

// When the player press f2 button, 
// EventHandler get LoadLevel Event, when the the eventhandler get that event
// close the currnet game and call LoadNextLevel fuction.
// The game has 3 levels and these are in levelList lua file.
// When the LoadNextLevel is called, get random level between 1,2 and 3.
// This function can re initialize subsystems which can start new game.
void GameEngine::LoadNextLevel(lua_State* lua_level_file)
{
	lua_r levels = luabridge::getGlobal(lua_level_file, "lvl");

	lua_r Level_List = levels["All"];
	lua_r num_level = levels["number"];

	std::vector<std::string> levelTemp;

	for (int i = 0; i < num_level.cast<int>(); i++)
	{
		int j = 97 + i;
		char index = j;
		levelTemp.push_back(Level_List[index]);
	}

	int random = rand() % num_level.cast<int>();

	char newlevel[100];

	// Need to change the string to char.
	strcpy_s(newlevel, levelTemp[random].c_str());
	
	graphics.InitGraphicsLua(Data_Sub::GetLuaFile("Data/window.lua"));
	graphics.InitModels(Data_Sub::GetLuaFile(newlevel));
	UIs.InitUI(Data_Sub::GetLuaFile("Data/UI.lua"));
	system("cls");
	isRunning = true;
}


void GameEngine::Event_Handler()
{
	for (Event* event : EventHandler::GetEvents())
	{
		switch (event->GetEventType())
		{
		case EventType::Quit:
			isRunning = false;
			std::cout << " Quit Event Done " << std::endl;
			//delete event;
			break;
		case EventType::LoadLevel:
			graphics.UnloadLevel();
			isRunning = false;
			LoadNextLevel(Data_Sub::GetLuaFile("Data/levelList.lua"));
			break;
		default:
			break;
		}

	}

}


