use godot::{engine::{IMultiMeshInstance3D, MultiMeshInstance3D, VisualInstance3D}, prelude::*};
use lazy_static::*;
use std::sync::Mutex;

#[derive(GodotClass)]
#[class(base=MultiMeshInstance3D)]
pub struct RsNode{
    base: Base<MultiMeshInstance3D>,
    positionVec : Vec<Vector3>,
    velocityVec : Vec<Vector3>,
    ridVec:Vec<Rid>,

}

#[godot_api]
impl IMultiMeshInstance3D for RsNode{
    fn init(base:Base<MultiMeshInstance3D>) -> Self{
        RsNode { base, 
        positionVec : Vec::new(),
        velocityVec: Vec::new(),
        ridVec : Vec::new(),}
    }
}


#[godot_api]
impl RsNode{
    #[func]
    fn updateMesh(&mut self){
        for i in 0..self.positionVec.len() {
            let rid = self.ridVec[i];
            self.positionVec[i] += self.velocityVec[i];
            if self.positionVec[i].y < 0.0 || self.positionVec[i].y > 10.0 {
                self.velocityVec[i].y = -self.velocityVec[i].y;
            } 
    
            let c = (self.positionVec[i] - Vector3{x:-50.0, y:0.0, z:-50.0})/Vector3{x:100.0, y:10.0, z:100.0};

            godot::classes::RenderingServer::singleton().multimesh_instance_set_color(
                rid, 
                i as i32, 
                Color::from_rgb(c.x, c.y, c.z) );
            godot::classes::RenderingServer::singleton().multimesh_instance_set_transform(
                rid, 
                i as i32, 
                godot::prelude::Transform3D{
                    basis: Basis::IDENTITY,
                    origin: Vector3 { x: self.positionVec[i].x, y: self.positionVec[i].y, z: self.positionVec[i].z }
                });
        }
    }

    #[func]
    fn spawnEntity(&mut self, rid : Rid,  id:i32, x :f32, y:f32 , z:f32, vx:f32 , vy:f32, vz:f32){
        self.ridVec.push(rid);
        self.positionVec.push(Vector3{x: x, y:y, z:z});
        self.velocityVec.push(Vector3{x:vx, y:vy, z:vz});        
    }
}