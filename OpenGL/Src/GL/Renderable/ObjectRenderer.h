#pragma once
#include <vector>

#include <GL/Shader.h>

class ObjectRenderer
{
public: 
	ObjectRenderer(Shader shader) : m_Shader(shader) {}

protected:
	virtual void InitRenderData() = 0;
	Shader m_Shader;
};

