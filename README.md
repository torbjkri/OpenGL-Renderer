# Whengine Renderer
I have long desired to have a graphics/OpenGL playground of my own. So this is Whengine, I'm not sure when it's hapening but hopefully sometime :P

There have been several iterations towards creating this. It started out quite simple following tutorials from [LearnOpenGL](https://learnopengl.com/).
I also watched quite a few of [TheCherno](https://www.youtube.com/c/TheChernoProject) and [VictorGordan](https://www.youtube.com/c/VictorGordan)'s YouTube videos.

The basis for all of this has all the time been experimentation. Try things out, and see how it looks, and what can be done with it. The scattered building blocks
I created initially became tedious really fast. So, to learn more I implemented an entity component system following  [Austin Morlan](https://austinmorlan.com/posts/entity_component_system/) reading about [Nomad Game Engine](https://savas.ca/nomad).

This has allowed me to quickly implement and try out new components and systems. Hopefully it will also make more complicated implementations more fun and easy in the future.


### ToDo:

Not hard todos but indications of things I want to implement or change

- Re-implement camera control 
	- Create an input handler component
	- May need an event system of sorts

- Implement ball-box collisions
	- Boxes need better surfaces/surface descriptions in collision body

- Improve ECS
	- One easy solution is to just change to [ENTT](https://github.com/skypjack/entt)
	- If not:
		- Improve signatures
			- How is inheritance covered?
			-  component manager should not control it
		- Implement observer pattern between parts to notify creation and destruction of entities.
			- This might come in along with input controls

- Lighting!
	- Need to get that specular niceness back
