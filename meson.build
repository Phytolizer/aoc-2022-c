project(
    'aoc-2022',
    'c',
    version: '2022.0.0',
    default_options: [
        'c_std=gnu11',
        'warning_level=3',
        'default_library=static',
    ],
)

add_project_arguments('-Wmissing-prototypes', language: 'c')

aoc_lib = library(
    'aoc2022',
    'src' / 'better_getline.c',
    'src' / 'string.c',
    'src' / 'dec01.c',
    include_directories: 'include',
    install: true,
)

aoc_dep = declare_dependency(
    link_with: aoc_lib,
    include_directories: 'include',
)

executable(
    'aoc-2022',
    'src' / 'main.c',
    install: true,
    dependencies: aoc_dep,
)

executable(
    'aoc-2022-test',
    'test' / 'main.c',
    dependencies: aoc_dep,
)
