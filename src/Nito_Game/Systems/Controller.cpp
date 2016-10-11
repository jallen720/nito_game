#include <GL/glew.h>

#include "Nito_Game/Systems/Controller.hpp"

#include <map>
#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Cpp_Utils/Collection.hpp"
#include "Nito/Components.hpp"
#include "Nito/Window.hpp"


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


namespace Nito_Game
{


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Data
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static vector<Transform *> entity_transforms;
static vector<float *> entity_speeds;
static GLFWwindow ** window;


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
    static const map<int, const vec3> key_directions
    {
        { GLFW_KEY_W , vec3( 0.0f, 1.0f, 0.0f) },
        { GLFW_KEY_S , vec3( 0.0f,-1.0f, 0.0f) },
        { GLFW_KEY_D , vec3( 1.0f, 0.0f, 0.0f) },
        { GLFW_KEY_A , vec3(-1.0f, 0.0f, 0.0f) },
    };


    // Get speed modifier based on whether the left shift key is down.
    int shift_key_state = glfwGetKey(*window, GLFW_KEY_LEFT_SHIFT);
    float speed_modifier = (shift_key_state == GLFW_PRESS || shift_key_state == GLFW_REPEAT) ? 2.0f : 1.0f;
    float delta_time = get_delta_time();


    for (auto i = 0u; i < entity_transforms.size(); i++)
    {
        for_each(key_directions, [&](const int key, const vec3 & direction) -> void
        {
            int key_state = glfwGetKey(*window, key);

            if (key_state == GLFW_PRESS || key_state == GLFW_REPEAT)
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


void controller_init()
{
    window = get_window();
}


} // namespace Nito_Game
