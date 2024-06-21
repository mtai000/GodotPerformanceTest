extends Node2D

@export var NODENUM := 40*1000
@export var testType := 0


@onready var fpsInfo = ""
@onready var extscene = preload("res://test/subScene/gdextnode.tscn")
@onready var scene = preload("res://test/subScene/gdnodetest.tscn")

# Called when the node enters the scene tree for the first time.
func _ready():
	if(testType == 0):
		fpsInfo = "GDTest: Entity: {number}\n FPS:{fps}"
	if(testType == 1):
		fpsInfo = "GDExtTest: Entity: {number}\n FPS:{fps}"
	for i in range(NODENUM):
		var subnode 
		if(testType == 0):
			subnode = scene.instantiate()
		elif(testType == 1):
			subnode = extscene.instantiate()
		$group.add_child(subnode)	

	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	
	$CanvasLayer/TextEdit.text = fpsInfo.format({"fps":str(Engine.get_frames_per_second()), "number":str(NODENUM)})
