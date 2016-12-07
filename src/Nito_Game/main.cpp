#include <string>
#include <vector>
#include <map>
#include "Nito/Engine.hpp"
#include "Nito/APIs/ECS.hpp"
#include "Nito/APIs/Input.hpp"
#include "Nito/APIs/Window.hpp"
#include "Cpp_Utils/Collection.hpp"
#include "Cpp_Utils/JSON.hpp"

#include "Nito_Game/Systems/Bot_AI.hpp"
#include "Nito_Game/Systems/Camera_Controller.hpp"
#include "Nito_Game/Systems/Controller.hpp"
#include "Nito_Game/Systems/Depth_Handler.hpp"
#include "Nito_Game/Systems/Parent_Switcher.hpp"
#include "Nito_Game/Systems/Scene_Load_Button.hpp"


using std::string;
using std::vector;
using std::map;

// Nito/Engine.hpp
using Nito::add_update_handler;
using Nito::run_engine;
using Nito::get_component_allocator;
using Nito::get_component_deallocator;
using Nito::Update_Handler;
using Nito::Component_Handlers;
using Nito::System_Entity_Handlers;

// Nito/APIs/ECS.hpp
using Nito::set_component_handlers;
using Nito::set_system_entity_handlers;

// Nito/APIs/Input.hpp
using Nito::Keys;
using Nito::Button_Actions;
using Nito::set_key_handler;

// Nito/APIs/Window.hpp
using Nito::close_window;

// Cpp_Utils/Container.hpp
using Cpp_Utils::for_each;

// Cpp_Utils/JSON.hpp
using Cpp_Utils::JSON;


namespace Nito_Game
{


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Data
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static vector<Update_Handler> game_update_handlers
{
    depth_handler_update,
    controller_update,
    bot_ai_update,
    camera_controller_update,
};


static map<string, const System_Entity_Handlers> game_system_entity_handlers
{
    {
        "controller",
        {
            controller_subscribe,
            controller_unsubscribe,
        },
    },
    {
        "bot_ai",
        {
            bot_ai_subscribe,
            bot_ai_unsubscribe,
        },
    },
    {
        "camera_controller",
        {
            camera_controller_subscribe,
            camera_controller_unsubscribe,
        },
    },
    {
        "scene_load_button",
        {
            scene_load_button_subscribe,
            scene_load_button_unsubscribe,
        },
    },
    {
        "depth_handler",
        {
            depth_handler_subscribe,
            depth_handler_unsubscribe,
        },
    },
    {
        "parent_switcher",
        {
            parent_switcher_subscribe,
            parent_switcher_unsubscribe,
        },
    },
};


static map<string, const Component_Handlers> game_component_handlers
{
    {
        "target_id",
        {
            get_component_allocator<string>(),
            get_component_deallocator<string>(),
        },
    },
    {
        "scene_to_load",
        {
            get_component_allocator<string>(),
            get_component_deallocator<string>(),
        },
    },
    {
        "speed",
        {
            get_component_allocator<float>(),
            get_component_deallocator<float>(),
        },
    },
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Interface
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int run()
{
    parent_switcher_init();
    for_each(game_update_handlers, add_update_handler);

    for_each(
        game_system_entity_handlers,
        [](const string & name, const System_Entity_Handlers & system_entity_handlers) -> void
        {
            set_system_entity_handlers(name, system_entity_handlers.subscriber, system_entity_handlers.unsubscriber);
        });

    for_each(game_component_handlers, [](const string & type, const Component_Handlers & component_handlers) -> void
    {
        set_component_handlers(type, component_handlers.allocator, component_handlers.deallocator);
    });

    set_key_handler(
        "exit",
        {
            Keys::ESCAPE,
            Button_Actions::PRESS,
            close_window,
        });

    return run_engine();
}


} // namespace Nito_Game


int main()
{
    return Nito_Game::run();
}
