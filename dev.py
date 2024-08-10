#!/usr/bin/env python3

import os
import platform


def fix_dependencies():
    from dev.setup_helpers import create_venv, activate_venv, install_dependencies

    create_venv()
    activate_venv()
    install_dependencies()


try:
    import click
    import sh

    from dev.helpers import *
except ImportError:
    user_input = input(
        'Dependencies are missing. Do you want to run setup? [y/n]: ')
    if user_input.lower() == 'y':
        fix_dependencies()
        exit(0)

generatorBinary = './build/main'
sourceFile = 'main.go'
commandRun = ""
runtime_dir = './runtime'
qmlruntime_dir = f"{runtime_dir}/qmlruntime"
qmlruntime_build_dir = f"{qmlruntime_dir}/build"


@click.group(invoke_without_command=True)
@click.option('--debug/--no-debug', default=False)
@click.pass_context
def cli(ctx, debug):
    global commandRun
    commandRun = ctx.invoked_subcommand
    ctx.ensure_object(dict)

    ctx.obj['DEBUG'] = debug

    if ctx.invoked_subcommand is None:
        echo('Running "build" command')
        build()
    return ctx


@cli.command(context_settings=dict(ignore_unknown_options=True,))
@click.pass_context
@click.option('--source', default=sourceFile, help='The source file to build.')
@click.option('--target', default=generatorBinary, help='The target directory for the binary.')
@click.option('--clean/--no-clean', default=False, help='Clean the build cache.')
@click.option('--regenerate/--no-regenerate', default=False, help='Regenerate the executable.')
@click.option('--open-build-folder', is_flag=True, help='Open the temporary go build folder to inspect the generated files.')
@click.option('--use-code/--use-os', is_flag=True, help='Use code to open build folder or filesystem.')
@click.argument('extra_args', nargs=-1)
def build(ctx, open_build_folder=False, use_code=False, source=sourceFile, target=generatorBinary, clean=False, regenerate=False, extra_args=[]):
    if clean:
        echo('Cleaning build cache')
        sh.go('clean', '-cache', *extra_args, **std_out)
        echo('Building')
    elif regenerate:
        echo(f'Removing executable "{target}"')
        sh.rm('-f', target, **std_out)

    # build C++ lib if require

    build_type = 'Debug' if ctx.obj['DEBUG'] else 'Release'

    # qt_dir = f"{runtime_dir}/qt"
    # qt_build_dir = f"{qt_dir}/build"
    # sh.cmake(
    #     '-B', qt_build_dir,
    #     '-S', qt_dir,
    #     '-G', 'Ninja', f'-DCMAKE_BUILD_TYPE={build_type}', **std_out
    # )
    # sh.cmake('--build', qt_build_dir, **std_out)

    # optionally open the build folder

    def get_work_folder(): return None
    out = std_out
    if open_build_folder:
        find_work, get_work_folder = get_work_finder()
        out = capture_out(find_work)

    try:
        sh.go('build', *extra_args, '-o', target, source, **out)
    except sh.ErrorReturnCode as e:
        pass
    finally:
        if open_build_folder and get_work_folder():
            if use_code:
                sh.code(get_work_folder(), **std_out)
            else:
                open_folder(get_work_folder())


def set_library_path(lib_path):
    system = platform.system()
    if system == "Linux":
        os.environ["LD_LIBRARY_PATH"] = f"{lib_path}:{
            os.environ.get('LD_LIBRARY_PATH', '')}"
    elif system == "Darwin":
        os.environ["DYLD_LIBRARY_PATH"] = f"{lib_path}:{
            os.environ.get('DYLD_LIBRARY_PATH', '')}"
    elif system == "Windows":
        os.environ["PATH"] = f"{lib_path};{os.environ.get('PATH', '')}"
    else:
        raise NotImplementedError(f"Unsupported OS: {system}")


@cli.command(context_settings=dict(ignore_unknown_options=True,))
@click.option('--source', default=sourceFile, help='The source file to run.')
@click.argument('extra_args', nargs=-1)
def run(source, extra_args):
    set_library_path(qmlruntime_build_dir)
    sh.go('run', source, *extra_args, **std_out)


@cli.command(context_settings=dict(ignore_unknown_options=True,))
@click.option('--source', default=sourceFile, help='The source file to run.')
@click.argument('extra_args', nargs=-1)
def test(source, extra_args):
    set_library_path(qmlruntime_build_dir)
    test_dirs = ["tests/..."]
    named_args = {"count": 1}
    sh.go('test', *test_dirs, "v", *extra_args, **named_args, **std_out)


def build_type_label(ctx):
    return 'Debug' if ctx.obj['DEBUG'] else 'Release'


def conan_dir(ctx, generators=False):
    extra = f'{build_type_label(ctx)}/generators' if generators else ''
    return f"{qmlruntime_build_dir}/conan/{extra}"


@cli.command("setup-runtime")
@click.pass_context
@click.option('--clean/--no-clean', default=False)
def setup_runtime(ctx, clean):
    echo('Installing conan dependencies')

    if clean:
        sh.rm('-rf', qmlruntime_build_dir, **std_out)
        from dev.setup_helpers import venv_dir
        sh.rm('-rf', venv_dir, **std_out)

    build_type = f"build_type={build_type_label(ctx)}"

    fix_dependencies()

    sh.conan('install', qmlruntime_dir, '-s', build_type, '--build=missing',
             f'-of={conan_dir(ctx)}', **std_out)

    echo('Installing go dependencies')

    sh.go('mod', 'tidy', **std_out)


@cli.command("build-runtime")
@click.pass_context
def build_runtime(ctx):
    echo('Build and run cpp tests')

    build_type = 'Debug' if ctx.obj['DEBUG'] else 'Release'

    sh.cmake(
        '-G', 'Ninja', '-B', qmlruntime_build_dir,
        '-S', qmlruntime_dir, f'-DCMAKE_BUILD_TYPE={build_type}', '--preset', 'conan-release', **std_out
    )
    sh.cmake('--build', qmlruntime_build_dir, **std_out)

    test_qmlruntime_path = f'{qmlruntime_build_dir}/tests/test_qmlruntime'
    sh.Command(test_qmlruntime_path).bake(
        **{"--gtest_filter": '"RuntimeTest.*"'}, **std_out)()


if __name__ == '__main__':
    try:
        cli()
    except sh.ErrorReturnCode as e:
        echo(f'Command "{commandRun}" exited with {e.exit_code}')
