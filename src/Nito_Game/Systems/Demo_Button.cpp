#include "Nito_Game/Systems/Demo_Button.hpp"

#include <map>
#include <string>
#include "Nito/Components.hpp"
#include "Nito/APIs/Scene.hpp"
#include "Cpp_Utils/Map.hpp"


using std::map;
using std::string;

// Nito/APIs/ECS.hpp
using Nito::Entity;
using Nito::get_component;

// Nito/Components.hpp
using Nito::Button;

// Nito/APIs/Scene.hpp
using Nito::set_scene_to_load;

// Cpp_Utils/Map.hpp
using Cpp_Utils::remove;


namespace Nito_Game
{


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Data
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static map<Entity, Button *> entity_buttons;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Interface
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void demo_button_subscribe(const Entity entity)
{
    auto button = (Button *)get_component(entity, "button");
    const auto scene_to_load = (string *)get_component(entity, "scene_to_load");
    entity_buttons[entity] = button;

    button->click_handler = [=]() -> void
    {
        set_scene_to_load(*scene_to_load);
    };
}


void demo_button_unsubscribe(const Entity entity)
{
    static const auto dud = []() -> void {};

    entity_buttons[entity]->click_handler = dud;
    remove(entity_buttons, entity);
}


} // namespace Nito_Game
