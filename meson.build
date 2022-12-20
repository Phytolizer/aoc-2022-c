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

cc = meson.get_compiler('c')
if cc.has_argument('-Wmissing-prototypes')
    add_project_arguments('-Wmissing-prototypes', language: 'c')
endif

if target_machine.system() == 'windows'
    add_project_arguments('-D_CRT_SECURE_NO_WARNINGS', language: 'c')
endif

aoc_lib = library(
    'aoc2022',
    'src' / 'better_getline.c',
    'src' / 'string.c',
    'src' / 'dec01.c',
    'src' / 'dec02.c',
    'src' / 'dec03.c',
    'src' / 'dec04.c',
    'src' / 'dec05.c',
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
srcdir = meson.current_source_dir().replace('\\', '/')
data.set('PROJECT_DIR', srcdir)

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
