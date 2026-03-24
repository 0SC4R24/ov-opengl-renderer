///
/// OV-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

typedef struct
{
	unsigned int vertexBufferId; // VBO: Buffer containing buffer data (GPU ID)
	unsigned int vertexArrayId; // VAO: VBO snapshot configurations with glVertexAttribPointer (GPU ID)
	unsigned int vertexIndexArrayId; // IBO: Index buffer object, vertex order (GPU ID)
} bufferObject_t;
