#pragma once
#include <flecs.h>
#include <flecs_module.h>
#include <godot_cpp/classes/ref.hpp>

namespace FlecsModule
{
    class World : public godot::RefCounted
    {
        GDCLASS(World, godot::RefCounted);

    protected:
        static void _bind_methods();
        flecs::world world;

    public:
        World();
        ~World();
        void progress();
        flecs::world *get_world();
        godot::String to_json();
    };
}
