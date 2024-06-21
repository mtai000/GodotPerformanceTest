use godot::init::gdextension;
use godot::prelude::*;

mod rsnode;
mod ecs;

struct RustExtension;

#[gdextension]
unsafe impl ExtensionLibrary for RustExtension{

}


