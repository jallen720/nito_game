#pragma once


#include "Nito/ECS.hpp"


namespace Nito_Game
{


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Interface
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void bot_ai_subscribe(const Nito::Entity entity);
void bot_ai_update(const float delta_time);


} // namespace Nito_Game
