#include "Nito_Game/Systems/Vertical_Depth_Modifier.hpp"

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
void vertical_depth_modifier_subscribe(const Entity entity)
{
    entity_transforms.push_back((Transform *)get_component(entity, "transform"));
}


void vertical_depth_modifier_update(const float /*delta_time*/)
{
    for (Transform * entity_transform : entity_transforms)
    {
        vec3 & entity_position = entity_transform->position;
        entity_position.z = -entity_position.y;
    }
}


} // namespace Nito_Game
