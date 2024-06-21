use std::{process::Command, vec};

use bevy_ecs::{component::Component, world::World};
use godot::{engine::{IMultiMeshInstance3D, MultiMeshInstance3D, VisualInstance3D}, prelude::*};



#[derive(Component)]
struct cPosition(Vector3);
#[derive(Component)]
struct cVelocity(Vector3);
#[derive(Component)]
struct cRid(Rid);
#[derive(Component)]
struct cID(i32);




#[derive(GodotClass)]
#[class(base=MultiMeshInstance3D)]
pub struct RsEcsNode{
    base: Base<MultiMeshInstance3D>,
    world: World,
}

#[godot_api]
impl IMultiMeshInstance3D for RsEcsNode{
    fn init(base:Base<MultiMeshInstance3D>) -> Self{
        RsEcsNode { 
            base, 
            world : World::new(),
        }
    }
}

#[godot_api]
impl RsEcsNode{
    #[func]
    fn spawnEntity(
        &mut self, 
        rid : Rid,  id:i32, x :f32, y:f32 , z:f32, vx:f32 , vy:f32, vz:f32){
            let bundle = (
                cPosition(Vector3{x:x, y:y, z:z}),
                cVelocity(Vector3{x:vx, y:vy, z:vz}),
                cRid(rid),
                cID(id),
            );
        
            self.world.spawn(bundle);
    }

    #[func]
    fn updateMesh(&mut self){
        for mut w in self.world.iter_entities_mut(){
            let mut pos = w.get_mut::<cPosition>().unwrap().0;
            let mut vel = w.get_mut::<cVelocity>().unwrap().0;
            let rid = w.get::<cRid>().unwrap().0;
            let id = w.get::<cID>().unwrap().0;

            pos += vel;   
            w.get_mut::<cPosition>().unwrap().0 = pos;

            if pos.y < 0.0 || pos.y > 10.0 {
                vel.y = -vel.y;
                w.get_mut::<cVelocity>().unwrap().0 = vel;
            } 

            let c = (pos - Vector3{x:-50.0, y:0.0, z:-50.0})/Vector3{x:100.0, y:10.0, z:100.0};

            godot::classes::RenderingServer::singleton().multimesh_instance_set_color(
                rid, 
                id, 
                Color::from_rgb(c.x, c.y, c.z) );
            godot::classes::RenderingServer::singleton().multimesh_instance_set_transform(
                rid, 
                id, 
                godot::prelude::Transform3D{
                    basis: Basis::IDENTITY,
                    origin: Vector3 { x: pos.x, y: pos.y, z: pos.z }
                });
            
                
                
        }
    }
}