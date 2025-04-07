project('AABBCollision', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'])

# Find SFML dependency
sfml_dep = dependency('sfml-graphics', required : true)

executable('aabb_collision',
           'main.cpp',
           dependencies : [sfml_dep],
           install : true) 
