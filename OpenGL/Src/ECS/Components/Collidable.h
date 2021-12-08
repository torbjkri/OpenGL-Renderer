#pragma once

#include <memory>
#include <variant>

enum class CollisionType {Ball, Cube};

struct CollisionShape {
	virtual ~CollisionShape() {};
};

template<typename T>
struct CollisionShapeCRTP : public CollisionShape {
	virtual CollisionShape* Get() { return static_cast<T*>(this); }
};

struct CollisionBox : public CollisionShape {
};

struct CollisionBall : public CollisionShape {
	float radius_;
};


struct Collidable {
	std::variant<CollisionBall, CollisionBox> shape_;
};