#include "Nito_Game/Systems/Demo_Button.hpp"

#include "Nito/Components.hpp"


// Nito/ECS.hpp
using Nito::Entity;
using Nito::get_component;

// Nito/Components.hpp
using Nito::Button;


namespace Nito_Game
{


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Interface
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void demo_button_subscribe(const Entity entity)
{
    auto button = (Button *)get_component(entity, "button");

    button->click_handler = [=]() -> void
    {
        printf("Hello, world! (from entity %d)\n", entity);
    };
}


} // namespace Nito_Game
