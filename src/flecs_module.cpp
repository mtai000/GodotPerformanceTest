#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include "flecs_module.h"

using namespace godot;

namespace FlecsModule {
	 godot_flecs::godot_flecs(flecs::world &ecs)
    {
        ecs.module<godot_flecs>();
        ecs.component<Position>();
        ecs.component<Velocity>();
        ecs.component<Color>();

        ecs.system<Position, const Velocity>("Move")
            .each([](Position &p, const Velocity &v)
                  {    
            p.x += v.x;
            p.y += v.y;
            p.z += v.z; });

        ecs.system<Velocity, const Position>("Bounce")
            .each([](Velocity &v, const Position &p)
            { 
            if(p.y < 0 || p.y > 10) {
                v.y = -v.y;
            } });

		 ecs.system<Color, const Position>("ColorIsPosition")
				.each([](flecs::iter &it, size_t index, Color &c, const Position &p) {    
            c.r = (p.x + 50.0) * 0.01;
            c.g = (p.y - 0.0) * 0.1;
            c.b = (p.z + 50) * 0.01; });

        ecs.system<const Color, const MultiMeshInstance>("RenderColor")
            .each([](flecs::iter &it, size_t index, const Color &c, const MultiMeshInstance &i)
                { 
                    RenderingServer::get_singleton()->multimesh_instance_set_color(i.id, index, godot::Color(c.r, c.g, c.b));
                });

        ecs.system<const Position, const MultiMeshInstance>("Render")
            .each([](flecs::iter &it, size_t index, const Position &p, const MultiMeshInstance &i)
                  { RenderingServer::get_singleton()->multimesh_instance_set_transform(i.id, index, Transform3D(Basis(), Vector3(p.x, p.y, p.z))); });
    }
}

 //namespace FlecsModule
