#include "demo.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/time.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/rect2.hpp>

void Demo::_bind_methods() {
	//ClassDB::bind_method(D_METHOD("SetVelocity","velocity"), &Demo::SetVelocity);
	//ClassDB::bind_method(D_METHOD("InitPos", "pos"), &Demo::InitPos);
}

using namespace godot;

void Demo::_ready() {
	Vector2 pos = Vector2(rand() % 1920, rand() % 1080);
	set_position(pos);
}

void Demo::_process(double delta){
	set_position(Vector2(get_position().x, Velocity * delta + get_position().y));
	if (get_position().y > 1080.f || get_position().y < 0.f) {
		Velocity = -Velocity;
	}
}

