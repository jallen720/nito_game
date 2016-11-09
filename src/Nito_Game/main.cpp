#include <string>
#include <vector>
#include <map>
#include "Nito/Engine.hpp"
#include "Nito/Utilities.hpp"
#include "Nito/APIs/ECS.hpp"
#include "Cpp_Utils/Collection.hpp"
#include "Cpp_Utils/JSON.hpp"

#include "Nito_Game/Systems/Controller.hpp"
#include "Nito_Game/Systems/Bot_AI.hpp"
#include "Nito_Game/Systems/Camera_Controller.hpp"
#include "Nito_Game/Systems/Demo_Button.hpp"
#include "Nito_Game/Systems/Depth_Handler.hpp"
#include "Nito_Game/Systems/Parent_Switcher.hpp"


using std::string;
using std::vector;
using std::map;

// Nito/Engine.hpp
using Nito::add_update_handler;
using Nito::run_engine;
using Nito::Update_Handler;

// Nito/APIs/ECS.hpp
using Nito::set_component_handler;
using Nito::set_system_subscribe_handler;
using Nito::Component;
using Nito::Component_Handler;
using Nito::System_Subscribe_Handler;

// Nito/Utilities.hpp
using Nito::string_component_handler;
using Nito::float_component_handler;

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
static vector<Update_Handler> update_handlers
{
    depth_handler_update,
    controller_update,
    bot_ai_update,
    camera_controller_update,
};


static map<string, const System_Subscribe_Handler> system_subscribe_handlers
{
    { "controller"        , controller_subscribe        },
    { "bot_ai"            , bot_ai_subscribe            },
    { "camera_controller" , camera_controller_subscribe },
    { "demo_button"       , demo_button_subscribe       },
    { "depth_handler"     , depth_handler_subscribe     },
    { "parent_switcher"   , parent_switcher_subscribe   },
};


static map<string, const Component_Handler> component_handlers
{
    {
        "target_id",
        string_component_handler
    },
    {
        "speed",
        float_component_handler
    }
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Interface
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int run()
{
    parent_switcher_init();
    for_each(update_handlers, add_update_handler);
    for_each(component_handlers, set_component_handler);
    for_each(system_subscribe_handlers, set_system_subscribe_handler);
    return run_engine();
}


} // namespace Nito_Game


int main()
{
    return Nito_Game::run();
}
