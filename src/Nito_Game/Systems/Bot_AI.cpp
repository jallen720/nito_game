#include "Nito_Game/Systems/Bot_AI.hpp"

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "Nito/Components.hpp"


using std::vector;
using std::string;

// glm/glm.hpp
using glm::vec3;
using glm::normalize;

// Nito/ECS.hpp
using Nito::Entity;
using Nito::get_component;
using Nito::get_entity;

// Nito/Components.hpp
using Nito::Transform;


namespace Nito_Game
{


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Data
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static vector<Transform *> entity_transforms;
static vector<Transform *> entity_target_transforms;


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
}


void bot_ai_update(const float delta_time)
{
    for (auto i = 0u; i < entity_transforms.size(); i++)
    {
        Transform * entity_transform = entity_transforms[i];
        vec3 direction = normalize(entity_target_transforms[i]->position - entity_transform->position);
        entity_transform->position += direction * delta_time / 2.0f;
    }
}


} // namespace Nito_Game
