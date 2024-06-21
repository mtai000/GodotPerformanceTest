extends Node3D

var entityCount : int = 0
var rng

@onready var m_mesh = $MultiMeshInstance3D
var velocityArray = PackedVector3Array()
var positionArray = PackedVector3Array()
# Called when the node enters the scene tree for the first time.
func _ready():
	rng = RandomNumberGenerator.new()
	add_child(m_mesh)
	m_mesh.multimesh.set_buffer([])
	spawnEntity(40 * 1000)
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	#spawnEntity(100)
	updateMesh()
	$CanvasLayer/TextEdit.text = "FPS:" + str(Engine.get_frames_per_second()) + "\n" + str(entityCount) 
	pass

func _physics_process(delta):
	pass

func updateMesh():
	for i in entityCount:
		positionArray[i] += velocityArray[i]
		if(positionArray[i].y < 0 or positionArray[i].y > 10):
			velocityArray[i].y = -velocityArray[i].y
		
		var c = (positionArray[i] - Vector3(-50.0,0.0,-50.0))/Vector3(100.0,10.0,100.0)
		
		var transform : Transform3D
		transform.basis = Basis()
		transform.origin = positionArray[i]
		
		RenderingServer.multimesh_instance_set_color(m_mesh.multimesh,i,Color(c.x,c.y,c.z))
		RenderingServer.multimesh_instance_set_transform(m_mesh.multimesh,i,transform)
		#m_mesh.set_instance_color(i,Color(c.x,c.y,c.z))
		#m_mesh.set_instance_transform(i, transform)
	pass

func spawnEntity(count):
	for i in count:
		spawn_entity(entityCount,
		rng.randf_range(-50.0, 50.0),
		rng.randf_range( 1, 9),
		rng.randf_range(-50.0, 50),
		0,
		rng.randf_range(-0.5, -0.1),
		0)
		
		#r.spawn_entity(world,str("Entity",entityCount),
		#rng.randf_range(-50,50),rng.randf_range(0,1),0,
		#0,rng.randf_range(0,0.01),0)
		


func spawn_entity(id,x,y,z,vx,vy,vz):
	#var count = m_mesh.instance_count()
	#if(entityCount > count):
	#return

	velocityArray.push_back(Vector3(vx,vy,vz))
	positionArray.push_back(Vector3(x,y,z))
	
	entityCount+=1
	pass
