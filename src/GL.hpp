#pragma once
#include <GLFW/glfw3.h>

namespace GL
{
	inline void(*Clear)(GLbitfield mask);
	inline void(*Viewport)(GLint x, GLint y, GLsizei width, GLsizei height);
	inline GLuint(*CreateShader)(GLenum shaderType);
	inline void(*ShaderSource)(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
	inline void(*CompileShader)(GLuint shader);
	inline void(*GetShaderiv)(GLuint shader, GLenum pname, GLint* params);
	inline void(*GetShaderInfoLog)(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog);
	inline void(*DeleteShader)(GLuint shader);
	inline GLuint(*CreateProgram)(void);
	inline void(*AttachShader)(GLuint program, GLuint shader);
	inline void(*DetachShader)(GLuint program, GLuint shader);
	inline void(*LinkProgram)(GLuint program);
	inline void(*GetProgramiv)(GLuint program, GLenum pname, GLint* params);
	inline void(*GetProgramInfoLog)(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog);
	inline void(*UseProgram)(GLuint program);
	inline void(*DeleteProgram)(GLuint program);
	inline void(*CreateVertexArrays)(GLsizei n, GLuint* arrays);
	inline void(*DeleteVertexArrays)(GLsizei n, const GLuint* arrays);
	inline void(*BindVertexArray)(GLuint array);
	inline void(*CreateBuffers)(GLsizei n, GLuint* buffers);
	inline void(*DeleteBuffers)(GLsizei n, const GLuint* buffers);
	inline void(*NamedBufferData)(GLenum target, GLsizeiptr, const void* data, GLenum usage);
	inline void(*VertexArrayVertexBuffer)(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
	inline void(*EnableVertexArrayAttrib)(GLuint vaobj, GLuint index);
	inline void(*VertexArrayAttribBinding)(GLuint vaobj, GLuint attribindex, GLuint bindingindex);
	inline void(*VertexArrayAttribFormat)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
	inline void(*DrawArrays)(GLenum mode, GLint first, GLsizei count);
}