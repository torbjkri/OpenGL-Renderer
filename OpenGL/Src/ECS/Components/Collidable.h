#pragma once

#include <memory>

struct CollisionShape {
	float radius_;
};

struct CollisionBox : CollisionShape {
};

struct CollisionBall : CollisionShape {
};


struct Collidable {
	float radius_;
};