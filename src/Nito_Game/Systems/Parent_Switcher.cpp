#include "Nito_Game/Systems/Parent_Switcher.hpp"

#include <string>
#include <vector>
#include "Nito/APIs/Input.hpp"


using std::string;
using std::vector;

// Nito/APIs/ECS.hpp
using Nito::Entity;
using Nito::get_component;

// Nito/APIs/Input.hpp
using Nito::Keys;
using Nito::Key_Actions;
using Nito::set_control_handler;
using Nito::add_control_binding;


namespace Nito_Game
{


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Data
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static vector<string *> entity_parent_ids;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Interface
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void parent_switcher_init()
{
    static const string CONTROL_HANDLER_NAME = "parent_switcher_control_handler";

    set_control_handler(CONTROL_HANDLER_NAME, [&]() -> void
    {
        for (string * entity_parent_id : entity_parent_ids)
        {
            *entity_parent_id = *entity_parent_id == "Player" ? "Bot_0" : "Player";
        }
    });

    add_control_binding(Keys::F, Key_Actions::PRESS, CONTROL_HANDLER_NAME);
}


void parent_switcher_subscribe(const Entity entity)
{
    entity_parent_ids.push_back((string *)get_component(entity, "parent_id"));
}


} // namespace Nito_Game
