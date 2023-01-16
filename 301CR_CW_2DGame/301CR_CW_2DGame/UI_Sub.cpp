#include "UI_Sub.h"
#include "Graphic_Sub.h"
#include "Data_Sub.h"
typedef luabridge::LuaRef lua_r;

UI_Sub::~UI_Sub()
{
    ImGui::SFML::Shutdown();
    delete mp_imguiWindow;
}
// Initialize the UI
void UI_Sub::InitUI(lua_State* lua_file)
{

    lua_r UI = luabridge::getGlobal(lua_file, "UI");
    lua_r title = UI["title"];
    lua_r width = UI["width"];
    lua_r height = UI["height"];

    std::string titleString = title.cast<std::string>();
    UI_Info.height = height.cast<int>();
    UI_Info.width = width.cast<int>();

	mp_imguiWindow = new sf::RenderWindow(UI_Info, titleString);
	mp_imguiWindow->setFramerateLimit(60);

	ImGui::SFML::Init(*mp_imguiWindow);


	
}

void UI_Sub::UpdateSubsystem()
{
    while (mp_imguiWindow->pollEvent(event)) {
        ImGui::SFML::ProcessEvent(*mp_imguiWindow, event);

        if (event.type == sf::Event::Closed) {
            mp_imguiWindow->close();
        }
    }

    ImGui::SFML::Update(*mp_imguiWindow, deltaTime.restart());

    // Print Player's current status and Keyinfo.
    ImGui::Begin("Player Status!");
    ImGui::Text("Player HP : %d", Player::Player_Hp);
    if(Score_Sub::GetCurrentScore() <= 99)
    {
        ImGui::Text("Player Current Score : %d", Score_Sub::GetCurrentScore());
    }
    else
    {
        ImGui::Text("Player Current Score : %d", 99);

    }
   
    ImGui::Text("Highest Score : %d", Score_Sub::GetHighestScore());
  
    
        ImGui::Text(" Up  : %c", 'w');
        ImGui::Text(" Right  : %c", 'd');
        ImGui::Text(" Left  : %c", 'a');
        ImGui::Text(" Down  : %c", 's');
        ImGui::Text(" Shooting  : %s", "space");
        ImGui::Text(" NextLevel  : %s", "F2");
        ImGui::Text(" Finish  : %s", "ESC");



    
    ImGui::End();

    mp_imguiWindow->clear();
  
    ImGui::SFML::Render(*mp_imguiWindow);
    mp_imguiWindow->display();
    HandleEvent();
}

void UI_Sub::HandleEvent()
{

    for (Event* event : EventHandler::GetEvents())
    {
        switch (event->GetEventType())
        {
        case EventType::Quit:
            ImGui::SFML::Shutdown();
            mp_imguiWindow->close();
            break;
        case EventType::LoadLevel:
            ImGui::SFML::Shutdown();
            mp_imguiWindow->close();
            break;

        default:
            break;
        }

    }
}







