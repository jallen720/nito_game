#include "Nito_Game/Systems/Parent_Switcher.hpp"

#include <string>
#include <map>
#include "Nito/APIs/Input.hpp"
#include "Cpp_Utils/Collection.hpp"
#include "Cpp_Utils/Map.hpp"


using std::string;
using std::map;

// Nito/APIs/ECS.hpp
using Nito::Entity;
using Nito::get_component;

// Nito/APIs/Input.hpp
using Nito::Keys;
using Nito::Button_Actions;
using Nito::set_key_handler;

// Cpp_Utils/Collection.hpp
using Cpp_Utils::for_each;

// Cpp_Utils/Map.hpp
using Cpp_Utils::remove;


namespace Nito_Game
{


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Data
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static map<Entity, string *> entity_parent_ids;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Interface
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void parent_switcher_init()
{
    set_key_handler(
        "parent_switcher_control_handler",
        {
            Keys::F,
            Button_Actions::PRESS,
            [&]() -> void
            {
                for_each(entity_parent_ids, [](const Entity /*entity*/, string * parent_id) -> void
                {
                    *parent_id = *parent_id == "Player" ? "Bot_0" : "Player";
                });
            },
        });
}


void parent_switcher_subscribe(const Entity entity)
{
    entity_parent_ids[entity] = (string *)get_component(entity, "parent_id");
}


void parent_switcher_unsubscribe(const Entity entity)
{
    remove(entity_parent_ids, entity);
}


} // namespace Nito_Game
