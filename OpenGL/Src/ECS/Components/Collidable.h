#pragma once

#include <memory>
#include <variant>
#include <array>

#include <glm/vec3.hpp>

enum class CollisionType {Ball, Cube};

struct CollisionShape {
	virtual ~CollisionShape() {};
};

struct CollisionBox : public CollisionShape {
	glm::vec3 size_ = glm::vec3(1.0f);
};

struct CollisionBall : public CollisionShape {
	float radius_;
};


struct Collidable {
	std::variant<CollisionBall, CollisionBox> shape_;
};