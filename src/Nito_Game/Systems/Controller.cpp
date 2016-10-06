#include <GL/glew.h>

#include "Nito_Game/Systems/Controller.hpp"

#include <map>
#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Cpp_Utils/Collection.hpp"
#include "Nito/Components.hpp"


using std::map;
using std::vector;

// glm/glm.hpp
using glm::vec3;

// Cpp_Utils/Container.hpp
using Cpp_Utils::for_each;

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


void controller_update(const float delta_time)
{
    static const map<int, const vec3> key_directions
    {
        { GLFW_KEY_W, vec3( 0.0f, 1.0f, 0.0f) },
        { GLFW_KEY_S, vec3( 0.0f,-1.0f, 0.0f) },
        { GLFW_KEY_D, vec3( 1.0f, 0.0f, 0.0f) },
        { GLFW_KEY_A, vec3(-1.0f, 0.0f, 0.0f) },
    };

    for (auto i = 0u; i < entity_transforms.size(); i++)
    {
        for_each(key_directions, [&](const int key, const vec3 & direction) -> void
        {
            int key_state = glfwGetKey(*window, key);

            if (key_state == GLFW_PRESS || key_state == GLFW_REPEAT)
            {
                entity_transforms[i]->position += direction * delta_time * *entity_speeds[i];
            }
        });
    }
}


void controller_init(GLFWwindow ** _window)
{
    window = _window;
}


} // namespace Nito_Game
