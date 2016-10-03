#include <string>
#include <vector>
#include <map>
#include "Nito/Engine.hpp"
#include "Nito/ECS.hpp"
#include "Cpp_Utils/Container.hpp"

#include "Nito_Game/Systems/Controller.hpp"
#include "Nito_Game/Systems/Bot_AI.hpp"


using std::string;
using std::vector;
using std::map;

// Nito/Engine.hpp
using Nito::get_window;
using Nito::add_update_handler;
using Nito::run_engine;
using Nito::Update_Handler;

// Nito/ECS.hpp
using Nito::set_component_handler;
using Nito::set_system_subscribe_handler;
using Nito::Component_Handler;
using Nito::System_Subscribe_Handler;

// Cpp_Utils/Container.hpp
using Cpp_Utils::for_each;


namespace Nito_Game
{


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Data
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static vector<Update_Handler> update_handlers
{
    controller_update,
    bot_ai_update,
};


static map<string, const System_Subscribe_Handler> system_subscribe_handlers
{
    { "controller" , controller_subscribe },
    { "bot_ai"     , bot_ai_subscribe     },
};


static map<string, const Component_Handler> component_handlers
{

};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Interface
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int run()
{
    controller_init(get_window());
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
