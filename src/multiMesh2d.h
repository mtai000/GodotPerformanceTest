#pragma once
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/world3d.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/multi_mesh_instance2d.hpp>
#include <vector>
#include <godot_cpp/variant/vector2.hpp>
using namespace godot;

    class MultiMesh2DTest : public MultiMeshInstance2D
    {
	GDCLASS(MultiMesh2DTest, MultiMeshInstance2D);

    private:
    	std::vector<Vector2> velocityArray;
    	std::vector<Vector2> positionArray;
		std::vector<RID> ridArray;

    protected:
        static void _bind_methods();

    public:
        MultiMesh2DTest();
        ~MultiMesh2DTest();
        void spawn_entity(RID, float x, float y, float vel_x, float vel_y);
		void updateMesh();
        int spawned;
    };
