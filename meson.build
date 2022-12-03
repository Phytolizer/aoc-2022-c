project(
    'aoc-2022',
    'c',
    version: '2022.0.0',
    default_options: [
        'c_std=c11',
        'warning_level=3',
        'default_library=static',
    ],
)

add_project_arguments('-Wmissing-prototypes', language: 'c')

executable(
    'aoc-2022',
    'src' / 'main.c',
    'src' / 'better_getline.c',
    'src' / 'string.c',
    'src' / 'dec01.c',
    include_directories: 'include',
    install: true,
)
