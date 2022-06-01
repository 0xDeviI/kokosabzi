# this file compiles ransomware to generate executable bin file.

import subprocess

def run_command(command: str):
    subprocess.run(command, shell=True)

def real_args(args: list):
    args.pop(0)
    return args

if __name__ == "__main__":
    run_command("g++ -o bin/kokosabzi kokosabzi.cpp -std=c++17 -lssl -lcrypto")