#pragma once

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>


using namespace godot;

class Demo : public Sprite2D {
	GDCLASS(Demo, Sprite2D);

protected:
	static void _bind_methods();

private:
	int Velocity;

public:
	Demo(){
		Velocity = rand() % 200 - 100;
		//godot::UtilityFunctions::print(get_position());
	};
	~Demo(){};

	void _ready() override;
	void _process(double delta) override;
};
