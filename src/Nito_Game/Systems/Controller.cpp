#include "Nito_Game/Systems/Controller.hpp"

#include <map>
#include <glm/glm.hpp>
#include "Nito/Components.hpp"
#include "Nito/APIs/Window.hpp"
#include "Nito/APIs/Input.hpp"
#include "Cpp_Utils/Collection.hpp"
#include "Cpp_Utils/Map.hpp"


using std::map;

// glm/glm.hpp
using glm::vec3;
using glm::normalize;

// Nito/APIs/ECS.hpp
using Nito::Entity;
using Nito::get_component;

// Nito/Components.hpp
using Nito::Transform;

// Nito/APIs/Window.hpp
using Nito::get_delta_time;

// Nito/APIs/Input.hpp
using Nito::Keys;
using Nito::Key_Actions;
using Nito::get_key_action;

// Cpp_Utils/Collection.hpp
using Cpp_Utils::for_each;

/// Cpp_Utils/Map.hpp
using Cpp_Utils::remove;


namespace Nito_Game
{


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Data Structures
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Entity_State
{
    Transform * transform;
    const float * speed;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Data
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static map<Entity, Entity_State> entity_states;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Interface
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void controller_subscribe(const Entity entity)
{
    entity_states[entity] =
    {
        (Transform *)get_component(entity, "transform"),
        (float *)get_component(entity, "speed"),
    };
}


void controller_unsubscribe(const Entity entity)
{
    remove(entity_states, entity);
}


void controller_update()
{
    static const map<Keys, const vec3> key_directions
    {
        { Keys::W , vec3( 0.0f, 1.0f, 0.0f) },
        { Keys::S , vec3( 0.0f,-1.0f, 0.0f) },
        { Keys::D , vec3( 1.0f, 0.0f, 0.0f) },
        { Keys::A , vec3(-1.0f, 0.0f, 0.0f) },
    };


    // Get speed modifier based on whether the left shift key is down.
    const float delta_time = get_delta_time();
    const Key_Actions shift_key_action = get_key_action(Keys::LEFT_SHIFT);

    const float speed_modifier =
        (shift_key_action == Key_Actions::PRESS || shift_key_action == Key_Actions::REPEAT)
        ? 2.0f
        : 1.0f;

    for_each(entity_states, [&](const Entity /*entity*/, Entity_State & entity_state) -> void
    {
        for_each(key_directions, [&](const Keys key, const vec3 & direction) -> void
        {
            const Key_Actions key_action = get_key_action(key);

            if (key_action == Key_Actions::PRESS || key_action == Key_Actions::REPEAT)
            {
                entity_state.transform->position +=
                    normalize(direction) *
                    delta_time *
                    *entity_state.speed *
                    speed_modifier;
            }
        });
    });
}


} // namespace Nito_Game
