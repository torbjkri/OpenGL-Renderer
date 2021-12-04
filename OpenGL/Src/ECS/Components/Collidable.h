#pragma once

#include <memory>

struct CollisionShape {
	virtual ~CollisionShape() {};
};

struct CollisionBox : CollisionShape {
};

struct CollisionBall : CollisionShape {
	float radius_;
};


struct Collidable {
	std::shared_ptr<CollisionShape> shape_;
};