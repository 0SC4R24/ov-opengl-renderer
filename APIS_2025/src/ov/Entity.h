///
/// OV-OpenGL-Renderer
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

	void setPosition(glm::vec4 position)
	{ 
		m_position = position;
		computeModelMatrix();
	}

	void setRotation(glm::vec4 rotation)
	{ 
		m_rotation = rotation;
		computeModelMatrix();
	}

	void setScale(glm::vec4 scale)
	{ 
		m_scale = scale;
		computeModelMatrix(); 
	}

public: // Methods
	// Compute model matrix
	virtual void computeModelMatrix()
	{
		glm::mat4 modelMatrix = glm::mat4(1.0f);

		modelMatrix = glm::translate(modelMatrix, glm::vec3(m_position));

		modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		modelMatrix = glm::scale(modelMatrix, glm::vec3(m_scale));

		m_modelMatrix = modelMatrix;
	}

	// Checks for movement of the entity every frame
	virtual void step(double deltaTime) = 0;
};