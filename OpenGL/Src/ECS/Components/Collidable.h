#pragma once

#include <memory>

struct CollisionShape {};

struct CollisionBox : CollisionShape {
	float radius_;
};

struct CollisionBall : CollisionShape {
	float radius_;
};


struct Collidable {
	std::unique_ptr<CollisionShape> shape_;
};