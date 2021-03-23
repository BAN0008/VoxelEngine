project('VoxelEngine', 'cpp')

source = [
	'src/Main.cpp',
	'src/Renderer.cpp',
	'src/Shader.cpp',
	'src/VertexBuffer.cpp'
]

glfw = dependency('glfw3')

executable('VoxelEngine', source, dependencies: glfw, override_options : 'cpp_std=c++17')
