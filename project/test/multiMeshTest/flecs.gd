extends Node

var world:World
var entityCount:int
var rng
@onready var r:Rendering = $Rendering

func _ready() -> void:
	world = World.new()
	rng = RandomNumberGenerator.new()
	spawnEntity(200 * 1000)

func _process(_delta):
	#spawnEntity(100)
	world.progress()
	$CanvasLayer/TextEdit.text = "FPS:" + str(Engine.get_frames_per_second()) + "\n" + str(entityCount) 


func spawnEntity(count):
	for i in count:
		r.spawn_entity(world,str("Entity",entityCount),
		rng.randf_range(-50.0, 50.0),
		rng.randf_range( 1, (entityCount + i) / 500000*10),
		rng.randf_range(-50.0, 50),
		0,
		rng.randf_range(-0.5, -0.1),
		0)
		#r.spawn_entity(world,str("Entity",entityCount),
		#rng.randf_range(-50,50),rng.randf_range(0,1),0,
		#0,rng.randf_range(0,0.01),0)
		entityCount+=1
