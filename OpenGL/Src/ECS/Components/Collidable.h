#pragma once

#include <memory>
#include <variant>
#include <array>

#include <glm/vec3.hpp>

enum class CollisionType {Ball, Cube};

struct CollisionShape {
	virtual ~CollisionShape() {};
};

struct CollisionSurface {
	std::array<glm::vec3, 4> corners_ = 
	{
		glm::vec3( 1.0f,  1.0f, 1.0f),
		glm::vec3( 1.0f, -1.0f, 1.0f),
		glm::vec3(-1.0f,  1.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f, 1.0f)
	};
	glm::vec3 normal_ = glm::vec3(0.0f, 0.0f, 1.0f);
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