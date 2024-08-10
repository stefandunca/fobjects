import subprocess
import venv
import os

def install_dependencies():
    try:
        result = subprocess.run(
            ['pip', 'install', '-r', 'requirements.txt'], check=True)
    except subprocess.CalledProcessError as e:
        print(f'Installing failed with error code {e.returncode}')
        exit(1)

venv_dir = '.dev/venv'

def create_venv():
    if not os.path.exists(venv_dir):
        print('Creating virtual environment...')
        venv.create(venv_dir, with_pip=True)
        print('Virtual environment created.')

def activate_venv():
    activate_script = os.path.join(venv_dir, 'Scripts', 'activate') if os.name == 'nt' else os.path.join(venv_dir, 'bin', 'activate')
    activate_command = f'source {activate_script}' if os.name != 'nt' else f'{activate_script}.bat'
    print(f'Activating virtual environment: {activate_command}')
    subprocess.run(activate_command, shell=True, check=True)
    print(f'Use the following command to activate the virtual environment: {activate_command}')
