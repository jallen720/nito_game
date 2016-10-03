#include "Nito_Game/Systems/Bot_AI.hpp"

#include <vector>
#include <glm/glm.hpp>
#include "Nito/Components.hpp"


using std::vector;

// glm/glm.hpp
using glm::vec3;

// Nito/ECS.hpp
using Nito::Entity;
using Nito::get_component;

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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Interface
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void bot_ai_subscribe(const Entity entity)
{
    entity_transforms.push_back((Transform *)get_component(entity, "transform"));
}


void bot_ai_update(const float delta_time)
{
    static const vec3 direction(1.0f, 1.0f, 0.0f);

    for (Transform * entity_transform : entity_transforms)
    {
        entity_transform->position += direction * delta_time;
    }
}


} // namespace Nito_Game
