#include "demo.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/time.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/rect2.hpp>
#include "multi_mesh.h"

void MultiMeshTest::_bind_methods() {
	ClassDB::bind_method(D_METHOD("spawn_entity", "id", "x", "y", "z", "vel_x", "vel_y", "vel_z"), &MultiMeshTest::spawn_entity);
	ClassDB::bind_method(D_METHOD("updateMesh"), &MultiMeshTest::updateMesh);
}

using namespace godot;

void MultiMeshTest::spawn_entity(int id, float x , float y , float z, float vx, float vy, float vz) {
	//int count = RenderingServer::get_singleton()->multimesh_get_visible_instances(get_base());
	//if (entityCount >= count) {
	//	return;
	//}
	velocityArray.push_back(godot::Vector3(vx, vy, vz));
	positionArray.push_back(godot::Vector3(x, y, z));
}
//
//void MultiMeshTest::spawnEntity(int count) {
//	for (int i = 0; i < count; i++) {
//		spawn_entity(i,
//				get_random_float() * 100.f - 50.f,
//				get_random_float() * 8.f + 1.f,
//				get_random_float() * 100.f - 50.f,
//				0,
//				get_random_float() * 0.4f - 0.5f,
//				0);
//		
//	}
//}

void MultiMeshTest::updateMesh() {
	for (int i = 0; i < positionArray.size(); i++) {
		positionArray[i] += velocityArray[i];
		if (positionArray[i].y < 0 || positionArray[i].y > 10)
			velocityArray[i].y = -velocityArray[i].y;

		auto c = (positionArray[i] - godot::Vector3(-50.0,0.0,-50.0))/godot::Vector3(100,10,100);

		RenderingServer::get_singleton()->multimesh_instance_set_color(get_base(), i, Color(c.x,c.y,c.z));
		RenderingServer::get_singleton()->multimesh_instance_set_transform(get_base(), i, Transform3D(Basis(), positionArray[i]));
	}
}

void MultiMeshTest::_ready() {
	
}

void MultiMeshTest::_process(double delta) {
	
}
