#include "multiMesh2d.h"

MultiMesh2DTest::MultiMesh2DTest() {
}

MultiMesh2DTest::~MultiMesh2DTest() {
}

void MultiMesh2DTest::spawn_entity(RID id, float x, float y, float vx, float vy) {
	velocityArray.push_back(godot::Vector2(vx, vy));
	positionArray.push_back(godot::Vector2(x, y));
	ridArray.push_back(id);
}

void MultiMesh2DTest::updateMesh() {
	for (int i = 0; i < positionArray.size(); i++) {
		positionArray[i] += velocityArray[i];
		if (positionArray[i].y < 0 || positionArray[i].y > 1080)
			velocityArray[i].y = -velocityArray[i].y;

		RenderingServer::get_singleton()->multimesh_instance_set_transform_2d(ridArray[i], i,
				Transform2D(Vector2(10, 0), Vector2(0,10), positionArray[i]));
	}
}

void MultiMesh2DTest::_bind_methods() {
	ClassDB::bind_method(D_METHOD("spawn_entity", "rid", "x", "y", "vel_x", "vel_y"), &MultiMesh2DTest::spawn_entity);
	ClassDB::bind_method(D_METHOD("updateMesh"), &MultiMesh2DTest::updateMesh);
}
