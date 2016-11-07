#include "Nito_Game/Systems/Controller.hpp"

#include <map>
#include <vector>
#include <glm/glm.hpp>
#include "Cpp_Utils/Collection.hpp"
#include "Nito/Components.hpp"
#include "Nito/Window.hpp"
#include "Nito/Input.hpp"


using std::map;
using std::vector;

// glm/glm.hpp
using glm::vec3;
using glm::normalize;

// Cpp_Utils/Container.hpp
using Cpp_Utils::for_each;

// Nito/ECS.hpp
using Nito::Entity;
using Nito::get_component;

// Nito/Components.hpp
using Nito::Transform;

// Nito/Window.hpp
using Nito::get_window;
using Nito::get_delta_time;

// Nito/Input.hpp
using Nito::Keys;
using Nito::Key_Actions;
using Nito::get_key_action;


namespace Nito_Game
{


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Data
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static vector<Transform *> entity_transforms;
static vector<float *> entity_speeds;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Interface
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void controller_subscribe(const Entity entity)
{
    entity_transforms.push_back((Transform *)get_component(entity, "transform"));
    entity_speeds.push_back((float *)get_component(entity, "speed"));
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
    float delta_time = get_delta_time();
    Key_Actions shift_key_action = get_key_action(Keys::LEFT_SHIFT);

    float speed_modifier =
        (shift_key_action == Key_Actions::PRESS || shift_key_action == Key_Actions::REPEAT)
        ? 2.0f
        : 1.0f;

    for (auto i = 0u; i < entity_transforms.size(); i++)
    {
        for_each(key_directions, [&](const Keys key, const vec3 & direction) -> void
        {
            Key_Actions key_action = get_key_action(key);

            if (key_action == Key_Actions::PRESS || key_action == Key_Actions::REPEAT)
            {
                entity_transforms[i]->position +=
                    normalize(direction) *
                    delta_time *
                    *entity_speeds[i] *
                    speed_modifier;
            }
        });
    }
}


} // namespace Nito_Game
