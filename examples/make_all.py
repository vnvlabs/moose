import os
import sys

direct = os.path.dirname(os.path.realpath(__file__))
command = " ".join(sys.argv[1:])

def run_make_vnv(directory):
    try:
        os.chdir(directory)
        print(f"Running {command} in {directory}")
        os.system(command)
    except Exception as e:
        print(f"Error in {directory}: {e}")
    finally:
        os.chdir("..")  # Change back to the original working directory

def run_make_vnv_in_all_directories():
    current_directory = direct
    subdirectories = [d for d in os.listdir(current_directory) if os.path.isdir(d)]

    for directory in subdirectories:
        run_make_vnv(directory)

if __name__ == "__main__":
    run_make_vnv_in_all_directories()