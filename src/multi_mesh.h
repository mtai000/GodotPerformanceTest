#pragma once

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/multi_mesh_instance3d.hpp>
#include <random>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <vector>
using namespace godot;

class MultiMeshTest : public MultiMeshInstance3D {
	GDCLASS(MultiMeshTest, MultiMeshInstance3D);

protected:
	static void _bind_methods();

private:
	std::vector<Vector3> velocityArray;
	std::vector<Vector3> positionArray;


	//inline float get_random_float() {
	//	static std::random_device dev;
	//	static std::mt19937 rng(dev());
	//	static std::uniform_real_distribution<float> dist(0.f, 1.f); // distribution in range [1, 6]

	//	return dist(rng);
	//}

public:
	MultiMeshTest(){
	};
	~MultiMeshTest(){};

	void spawn_entity(int, float, float, float, float, float, float);
	//void spawnEntity(int count);
	void updateMesh();

	void _ready() override;
	void _process(double delta) override;
};
