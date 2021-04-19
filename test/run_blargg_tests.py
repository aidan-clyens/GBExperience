import subprocess
import shlex
import os
import threading
import queue


test_directory = "test/test-roms/cpu_instrs/individual/"

gameboy_exe = "build/src/GameBoy_run"
args = ["--debug", "--headless"]


def get_test_files():
    return sorted([os.path.join(test_directory, d) for d in os.listdir(test_directory)])


def build(build_type):
    os.chdir("build")

    cmd = f"cmake .. -DCMAKE_BUILD_TYPE={build_type}"
    print(cmd)
    subprocess.call(shlex.split(cmd), shell=False)

    cmd = f"make"
    print(cmd)
    subprocess.call(shlex.split(cmd), shell=False)

    os.chdir("..")


def stdin_write(proc, line):
    ret = False
    line += "\n"
    try:
        proc.stdin.write(line.encode())
        ret = True
    except IOError as e:
        print(e)
        ret = False

    proc.stdin.flush()
    return ret


def run_test(file):
    file = file.replace(" ", "\ ")
    print(f"Testing: {os.path.basename(file)}")

    cmd = f"{gameboy_exe} {file} {' '.join(args)}"
    print(cmd)
    proc = subprocess.Popen(shlex.split(cmd), shell=False, stdout=subprocess.PIPE, stdin=subprocess.PIPE)

    running = True
    started = False
    sp_counter = 0

    test_passed = False
    while running:
        exit_code = proc.poll()
        if exit_code is not None:
            running = False

        output = proc.stdout.readline()
        output = output.decode()

        if "Starting" in output:
            stdin_write(proc, "bo 0x31")
            started = stdin_write(proc, "c")

        if started:
            if "SP" in output and "DFFF" in output:
                sp_counter += 1

            if "Stopped" in output:
                stdin_write(proc, "p A")

                output = proc.stdout.readline()
                output = output.decode()
                output = output.strip().split()
                test_passed = (output[2] == "0x0")

                stdin_write(proc, "c")

        if sp_counter == 2:
            running = False

    proc.stdin.close()
    proc.kill()
    proc.wait()

    return test_passed


def main():
    files = get_test_files()

    # build("Debug")

    for f in files:
        passed = run_test(f)
        print(passed)


if __name__ == '__main__':
    main()
