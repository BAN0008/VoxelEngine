project('VoxelEngine', 'cpp')

source = [
	'src/Main.cpp',
	'src/Renderer.cpp',
	'src/Shader.cpp',
	'src/VertexBuffer.cpp',
	'src/Texture.cpp',
	'src/TextureArray.cpp',
	'src/Framebuffer.cpp',
	'src/Renderbuffer.cpp',
	'src/Camera.cpp',
	'src/ChunkStorage.cpp',
	'src/third_party/stb_image.cpp'
]

glfw = dependency('glfw3', version: '>=3.3')

executable('VoxelEngine', source, include_directories: 'src/third_party', dependencies: glfw, override_options : 'cpp_std=c++17')
