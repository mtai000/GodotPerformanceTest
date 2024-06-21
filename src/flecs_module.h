#pragma once

#include <flecs.h>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/world3d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

namespace FlecsModule
{
    struct Position
    {
        float x, y, z;
    };

    struct Velocity
    {
        float x, y, z;
    };

    struct Color
    {
        float r, g, b;
    };

    struct MultiMeshInstance
    {
        godot::RID id;
    };

    struct godot_flecs
    {
        godot_flecs(flecs::world &world); // Ctor that loads the module
    };

}
