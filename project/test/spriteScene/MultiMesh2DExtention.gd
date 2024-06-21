extends Node2D

var rng = RandomNumberGenerator.new()
var entityCount = 0
@onready var r = $MultiMeshInstance2D
# Called when the node enters the scene tree for the first time.
func _ready():
	entityCount = r.multimesh.instance_count
	spawnEntity(entityCount)
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	r.updateMesh()
	$CanvasLayer/TextEdit.text = "FPS:" + str(Engine.get_frames_per_second()) + "\n" + str(entityCount) 
	pass
	



func spawnEntity(count):
	for i in count:
		r.spawn_entity(r.multimesh,
		rng.randi_range(0,1920),
		rng.randi_range(0,1080),
		0,
		rng.randi_range(-20, 20))
		#r.spawn_entity(world,str("Entity",entityCount),
		#rng.randf_range(-50,50),rng.randf_range(0,1),0,
		#0,rng.randf_range(0,0.01),0)
