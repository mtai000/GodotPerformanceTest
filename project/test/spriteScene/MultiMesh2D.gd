extends Node2D

@onready var m_mesh = $MultiMeshInstance2D
var velocityArray = PackedVector2Array()
var positionArray = PackedVector2Array()
var rng = RandomNumberGenerator.new()
var entityCount = 0
# Called when the node enters the scene tree for the first time.
func _ready():
	entityCount = m_mesh.multimesh.instance_count
	for i in m_mesh.multimesh.instance_count:
		velocityArray.push_back( Vector2(0, rng.randi() % 20  - 10))
		positionArray.push_back( Vector2(rng.randi()%1920,rng.randi()%1080))
	
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	updateMesh()
	$CanvasLayer/TextEdit.text = "FPS:" + str(Engine.get_frames_per_second()) + "\n" + str(entityCount) 
	pass
	
func updateMesh():
	for i in entityCount:
		positionArray[i] += velocityArray[i]
		if(positionArray[i].y < 0 or positionArray[i].y > 1080):
			velocityArray[i].y = -velocityArray[i].y
			
		var transform : Transform2D
		transform.x = Vector2(10,0)
		transform.y = Vector2(0,10)
		transform.origin = positionArray[i]
		
		RenderingServer.multimesh_instance_set_transform_2d(m_mesh.multimesh,i,transform)
		#m_mesh.set_instance_color(i,Color(c.x,c.y,c.z))
	
	pass
