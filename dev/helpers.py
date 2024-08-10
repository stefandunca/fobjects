import sys
import os
import platform
import click

std_out = {'_out': sys.stdout, '_err': sys.stderr}

def echo(message):
    click.echo(f'DEV: {message}')

def get_work_finder():
    work_folder = ""

    def find_work(l, is_out_not_err):   # type: ignore
        nonlocal work_folder
        if l.startswith("WORK="):
            _, path = l.split("=", 1)
            work_folder = path.strip()
        return l

    return find_work, lambda: work_folder


# Expect of a form (line, is_out_not_err) -> processed_line
def capture_out(process: callable):
    return {
        '_out': lambda l: sys.stdout.write(process(l, True)),
        '_err': lambda l: sys.stderr.write(process(l, False))
    }


def open_folder(path):
    if platform.system() == "Windows":
        os.startfile(path)
    elif platform.system() == "Darwin":
        subprocess.run(["open", path], check=True)
    else:  # Assume linux
        subprocess.call(["xdg-open", path])
