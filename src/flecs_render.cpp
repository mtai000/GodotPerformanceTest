#include "flecs_render.h"

namespace FlecsModule
{
    Rendering::Rendering()
    {
    }

    Rendering::~Rendering()
    {
    }

    void Rendering::spawn_entity(Ref<World> p_world, String name, float x, float y, float z, float vel_x, float vel_y, float vel_z)
    {
        auto count = RenderingServer::get_singleton()->multimesh_get_visible_instances(get_base());
        if (spawned >= count)
        {
            return;
        }

        p_world->get_world()->entity(name.utf8().get_data()).set<Position>({x, y, z}).set<Velocity>({vel_x, vel_y, vel_z}).set<MultiMeshInstance>({get_base()}).set<Color>({1, 1, 1});
        spawned++;
    }

    void Rendering::_bind_methods()
    {
        ClassDB::bind_method(D_METHOD("spawn_entity", "name", "x", "y", "z", "vel_x", "vel_y", "vel_z"), &Rendering::spawn_entity);
    }
}