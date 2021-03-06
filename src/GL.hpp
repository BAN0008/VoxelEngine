#pragma once
#include <GLFW/glfw3.h>

namespace GL
{
	inline void(*Enable)(GLenum cap);
	inline void(*CullFace)(GLenum mode);
	inline void(*FrontFace)(GLenum mode);
	inline void(*Clear)(GLbitfield mask);
	inline void(*ClearColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	inline void(*Viewport)(GLint x, GLint y, GLsizei width, GLsizei height);
	inline GLuint(*CreateShader)(GLenum shaderType);
	inline void(*ShaderSource)(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
	inline void(*CompileShader)(GLuint shader);
	inline void(*GetShaderiv)(GLuint shader, GLenum pname, GLint* params);
	inline void(*GetShaderInfoLog)(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog);
	inline void(*DeleteShader)(GLuint shader);
	inline GLuint(*CreateProgram)(void);
	inline void(*DeleteProgram)(GLuint program);
	inline void(*AttachShader)(GLuint program, GLuint shader);
	inline void(*DetachShader)(GLuint program, GLuint shader);
	inline void(*LinkProgram)(GLuint program);
	inline void(*GetProgramiv)(GLuint program, GLenum pname, GLint* params);
	inline void(*GetProgramInfoLog)(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog);
	inline void(*UseProgram)(GLuint program);
	inline void(*ProgramUniform1i)(GLuint program, GLint location, GLint v0);
	inline void(*ProgramUniform3f)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
	inline void(*ProgramUniform3fv)(GLuint program, GLint location, GLsizei count, const GLfloat* value);
	inline void(*ProgramUniformMatrix4fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	inline void(*CreateVertexArrays)(GLsizei n, GLuint* arrays);
	inline void(*DeleteVertexArrays)(GLsizei n, const GLuint* arrays);
	inline void(*BindVertexArray)(GLuint array);
	inline void(*CreateBuffers)(GLsizei n, GLuint* buffers);
	inline void(*DeleteBuffers)(GLsizei n, const GLuint* buffers);
	inline void(*NamedBufferData)(GLuint buffer, GLsizeiptr size, const void* data, GLenum usage);
	inline void(*NamedBufferSubData)(GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data);
	inline void(*VertexArrayVertexBuffer)(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
	inline void(*EnableVertexArrayAttrib)(GLuint vaobj, GLuint index);
	inline void(*VertexArrayAttribBinding)(GLuint vaobj, GLuint attribindex, GLuint bindingindex);
	inline void(*VertexArrayAttribFormat)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
	inline void(*DrawArrays)(GLenum mode, GLint first, GLsizei count);
	inline void(*CreateTextures)(GLenum target, GLsizei n, GLuint* textures);
	inline void(*DeleteTextures)(GLsizei n, const GLuint* textures);
	inline void(*TextureStorage2D)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
	inline void(*TextureStorage3D)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
	inline void(*TextureSubImage3D)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels);
	inline void(*TextureParameteri)(GLuint texture, GLenum pname, GLint param);
	inline void(*BindTextureUnit)(GLuint unit, GLuint texture);
	inline void(*CreateFramebuffers)(GLsizei n, GLuint* framebuffers);
	inline void(*DeleteFramebuffers)(GLsizei n, GLuint* framebuffers);
	inline void(*BindFramebuffer)(GLenum target, GLuint framebuffer);
	inline void(*NamedFramebufferParameteri)(GLuint framebuffer, GLenum pname, GLint param);
	inline void(*NamedFramebufferTexture)(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
	inline void(*NamedFramebufferRenderbuffer)(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
	inline void(*CreateRenderbuffers)(GLsizei n, GLuint* renderbuffers);
	inline void(*DeleteRenderbuffers)(GLsizei n, GLuint* renderbuffers);
	inline void(*NamedRenderbufferStorage)(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height);
}