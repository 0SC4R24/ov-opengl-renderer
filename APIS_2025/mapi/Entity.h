///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "common.h"

/// <summary>
/// Entity Interface
/// </summary>
class Entity
{
protected: // Attributes
	glm::vec4 m_position;
	glm::vec4 m_rotation;
	glm::vec4 m_scale;
	glm::mat4 m_modelMatrix;

public: // Getters & Setters
	const glm::vec4& getPosition()
	{ return m_position; }

	const glm::vec4& getRotation()
	{ return m_rotation; }

	const glm::vec4& getScale()
	{ return m_scale; }

	const glm::mat4& getModelMatrix()
	{ return m_modelMatrix; }

	void setPosition(glm::vec4& position)
	{ m_position = position; }

	void setRotation(glm::vec4& rotation)
	{ m_rotation = rotation; }

	void setScale(glm::vec4& scale)
	{ m_scale = scale; }

public: // Methods
	// Compute model matrix
	virtual void computeModelMatrix() = 0;

	// Checks for movement of the entity every frame
	virtual void step(double deltaTime) = 0;
};