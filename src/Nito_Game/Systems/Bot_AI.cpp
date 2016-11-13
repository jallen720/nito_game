#include "Nito_Game/Systems/Bot_AI.hpp"

#include <map>
#include <string>
#include <glm/glm.hpp>
#include "Nito/Components.hpp"
#include "Nito/APIs/Window.hpp"
#include "Cpp_Utils/Collection.hpp"
#include "Cpp_Utils/Map.hpp"


using std::map;
using std::string;

// glm/glm.hpp
using glm::vec3;
using glm::normalize;
using glm::distance;

// Nito/APIs/ECS.hpp
using Nito::Entity;
using Nito::get_component;
using Nito::get_entity;

// Nito/Components.hpp
using Nito::Transform;

// Nito/APIs/Window.hpp
using Nito::get_delta_time;

// Cpp_Utils/Collection.hpp
using Cpp_Utils::for_each;

// Cpp_Utils/Map.hpp
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
    const Transform * target_transform;
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
void bot_ai_subscribe(const Entity entity)
{
    const auto entity_target_id = (string *)get_component(entity, "target_id");

    entity_states[entity] =
    {
        (Transform *)get_component(entity, "transform"),
        (Transform *)get_component(get_entity(*entity_target_id), "transform"),
        (float *)get_component(entity, "speed"),
    };
}


void bot_ai_unsubscribe(const Entity entity)
{
    remove(entity_states, entity);
}


void bot_ai_update()
{
    const float delta_time = get_delta_time();

    for_each(entity_states, [&](const Entity /*entity*/, Entity_State & entity_state) -> void
    {
        Transform * transform = entity_state.transform;
        const Transform * target_transform = entity_state.target_transform;
        const float movement_value = delta_time * *entity_state.speed;

        // Don't move entity if the movement value will cause it to move past its target, preventing "jittering".
        if (distance(transform->position, target_transform->position) >= movement_value)
        {
            transform->position += normalize(target_transform->position - transform->position) * movement_value;
        }
    });
}


} // namespace Nito_Game
