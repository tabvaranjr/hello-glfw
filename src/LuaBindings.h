//
// Created by pclement on 16-11-29.
//

#ifndef HELLO_GLFW_LUABINDINGS_H
#define HELLO_GLFW_LUABINDINGS_H

namespace sol { class state; }

namespace LuaBindings
{
    void generate(sol::state& lua);
};


#endif //HELLO_GLFW_LUABINDINGS_H
