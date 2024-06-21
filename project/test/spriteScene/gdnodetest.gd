extends Node2D

var velocity
# Called when the node enters the scene tree for the first time.
func _ready():
	velocity = randi() % 200  - 100
	position = Vector2(randi()%1920,randi()%1080)
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	position.y = velocity * delta + position.y
	if(position.y > 1080 or position.y < 0):
		velocity = -velocity
	pass
