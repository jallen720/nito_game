#include "Nito_Game/Systems/Bot_AI.hpp"

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "Nito/Components.hpp"
#include "Nito/Engine.hpp"


using std::vector;
using std::string;

// glm/glm.hpp
using glm::vec3;
using glm::normalize;
using glm::distance;

// Nito/ECS.hpp
using Nito::Entity;
using Nito::get_component;
using Nito::get_entity;

// Nito/Components.hpp
using Nito::Transform;

// Nito/Engine.hpp
using Nito::get_delta_time;


namespace Nito_Game
{


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Data
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static vector<Transform *> entity_transforms;
static vector<Transform *> entity_target_transforms;
static vector<float *> entity_speeds;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Interface
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void bot_ai_subscribe(const Entity entity)
{
    auto target = (string *)get_component(entity, "target");
    entity_transforms.push_back((Transform *)get_component(entity, "transform"));
    entity_target_transforms.push_back((Transform *)get_component(get_entity(*target), "transform"));
    entity_speeds.push_back((float *)get_component(entity, "speed"));
}


void bot_ai_update()
{
    float delta_time = get_delta_time();

    for (auto i = 0u; i < entity_transforms.size(); i++)
    {
        Transform * transform = entity_transforms[i];
        Transform * target_transform = entity_target_transforms[i];
        float movement_value = delta_time * *entity_speeds[i];

        // Don't move entity if the movement value will cause it to move past its target, preventing "jittering".
        if (distance(transform->position, target_transform->position) >= movement_value)
        {
            transform->position += normalize(target_transform->position - transform->position) * movement_value;
        }
    }
}


} // namespace Nito_Game
