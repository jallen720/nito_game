#include "Nito_Game/Systems/Camera_Controller.hpp"

#include <vector>
#include <string>
#include "Nito/Components.hpp"


using std::vector;
using std::string;

// Nito/ECS.hpp
using Nito::Entity;
using Nito::get_entity;
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
static vector<Transform *> entity_target_transforms;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Interface
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void camera_controller_subscribe(const Entity entity)
{
    auto target_id = (string *)get_component(entity, "target_id");
    entity_transforms.push_back((Transform *)get_component(entity, "transform"));
    entity_target_transforms.push_back((Transform *)get_component(get_entity(*target_id), "transform"));
}


void camera_controller_update()
{
    for (auto i = 0u; i < entity_transforms.size(); i++)
    {
        entity_transforms[i]->position = entity_target_transforms[i]->position;
    }
}


} // namespace Nito_Game
