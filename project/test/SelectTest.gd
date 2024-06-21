extends Node2D


func _on_gd_test_pressed():
	var newScene :PackedScene= preload("res://test/spriteScene/gd_test.tscn")
	get_tree().change_scene_to_packed(newScene)
	pass # Replace with function body.


func _on_gdext_test_pressed():
	var newScene :PackedScene= preload("res://test/spriteScene/gdext_test.tscn")
	get_tree().change_scene_to_packed(newScene)
	pass # Replace with function body.


func _on_gdflecs_test_pressed():
	var newScene :PackedScene= preload("res://test/multiMeshTest/flecs_test.tscn")
	get_tree().change_scene_to_packed(newScene)
	pass # Replace with function body.


func _on_gdscript_test_pressed():
	var newScene :PackedScene= preload("res://test/multiMeshTest/base_test.tscn")
	get_tree().change_scene_to_packed(newScene)
	pass # Replace with function body.


func _on_gdext_test_2_pressed():
	var newScene :PackedScene= preload("res://test/multiMeshTest/gdext_test.tscn")
	get_tree().change_scene_to_packed(newScene)
	pass # Replace with function body.
