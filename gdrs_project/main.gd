extends Node2D


# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


func _on_gdrust_test_pressed():
	var newScene :PackedScene= preload("res://gdrust.tscn")
	get_tree().change_scene_to_packed(newScene)
	pass # Replace with function body.


func _on_bevyecs_test_pressed():
	var newScene :PackedScene= preload("res://bevyecs.tscn")
	get_tree().change_scene_to_packed(newScene)
	pass # Replace with function body.