project('VoxelEngine', 'cpp')

source = [
	'src/Main.cpp',
	'src/Renderer.cpp',
	'src/Shader.cpp',
	'src/VertexBuffer.cpp',
	'src/TextureArray.cpp',
	'src/third_party/stb_image.cpp'
]

glfw = dependency('glfw3')

executable('VoxelEngine', source, include_directories: 'src/third_party', dependencies: glfw, override_options : 'cpp_std=c++17')
