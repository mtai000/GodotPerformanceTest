#pragma once
#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

void initialize_gdextension_types();
void uninitialize_gdextension_types();

/* yes, the word in the middle must be the same as the module folder name */
