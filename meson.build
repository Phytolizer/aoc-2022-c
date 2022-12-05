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
    'src' / 'dec02.c',
    include_directories: include_directories('include'),
    install: true,
)

aoc_dep = declare_dependency(
    link_with: aoc_lib,
    include_directories: include_directories('include'),
)

executable(
    'aoc-2022',
    'src' / 'main.c',
    install: true,
    dependencies: aoc_dep,
)

data = configuration_data()
data.set('PROJECT_DIR', meson.current_source_dir())

configure_file(
    input: 'config.h.in',
    output: 'aoc2022_config.h',
    configuration: data,
)

test_exe = executable(
    'aoc-2022-test',
    'test' / 'main.c',
    dependencies: aoc_dep,
)

test(
    'aoc-2022-test',
    test_exe,
    timeout: 10,
)
