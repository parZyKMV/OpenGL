#include "VetexBuffer.h"

namespace neu
{
	VertexBuffer::VertexBuffer()
	{
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);
	}
	VertexBuffer::~VertexBuffer()
	{
		if (m_ibo) glDeleteBuffers(1, &m_ibo);
		if (m_vbo) glDeleteBuffers(1, &m_vbo);
		if (m_vao) glDeleteVertexArrays(1, &m_vao);
	}

	void VertexBuffer::Draw(GLenum primitiveType)
	{
		glBindVertexArray(m_vao);

		if (m_ibo)
		{
			glDrawElements(primitiveType, m_indexCount, m_indexType, 0);
		}
		else if (m_vbo)
		{
			glDrawArrays(primitiveType, 0, m_vertexCount);
		}

		glBindVertexArray(0); 
	}

	void VertexBuffer::CreateVertexBuffer(GLsizei totalSizeBytes, GLsizei vertexCount, GLvoid* data)
	{
		m_vertexCount = vertexCount;
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, totalSizeBytes, data, GL_STATIC_DRAW);
	}

	void VertexBuffer::CreateIndexBuffer(GLenum indexType, GLsizei count, GLvoid* data)
	{
		m_indexType = indexType;
		m_indexCount = count; 

		glGenBuffers(1, &m_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

		GLsizei indexSize = 0;
		switch (indexType)
		{
		case GL_UNSIGNED_BYTE:  indexSize = sizeof(GLubyte);  break;
		case GL_UNSIGNED_SHORT: indexSize = sizeof(GLushort); break;
		case GL_UNSIGNED_INT:   indexSize = sizeof(GLuint);   break;
		}

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * indexSize, data, GL_STATIC_DRAW);
	}


	
	void VertexBuffer::SetAttribute(int index, GLint size, GLsizei stride, GLuint offset)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
	}
}

