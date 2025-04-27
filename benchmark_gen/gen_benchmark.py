from gen_unfilled_code import gen_unfilled_code
from gen_code import generate_execute_code

import os
import subprocess
import json
import argparse

def benchmark_gen(file_path, execute = False, result_file = './result.txt'):
    # Load the benchmark description
    with open(file_path, "r", encoding="utf-8") as f:
        for line in f:
            desc = json.loads(line.strip())

            # Generate unfilled code
            tmp_folder = gen_unfilled_code(desc)

            # Generate filled code
            dst_folder = generate_execute_code(tmp_folder)

            if execute:
                print(f"Executing benchmark in {dst_folder}...")
                execute_test(dst_folder, result_file)

def execute_test(dst_folder, result_file):
    original_dir = os.getcwd()
    try:
        os.chdir(dst_folder)
        result = subprocess.run(
            ["python", "benchmark.py"],
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True
        )
        with open(result_file, "a", encoding="utf-8") as f:
            f.write(f"=== Result from {dst_folder} ===\n")
            f.write(result.stdout)
            f.write("\n\n")
    except subprocess.CalledProcessError as e:
        print(f"Error while running benchmark.py in {dst_folder}: {e}")
    finally:
        os.chdir(original_dir)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate benchmark code from descriptions.")
    parser.add_argument("--file_path", type=str, required=True, help="Path to the benchmark description JSON file.")
    parser.add_argument("--execute", action="store_true", help="Whether to execute the test after generation.")
    parser.add_argument("--result_file", type=str, default="./result.txt", help="Path to store the result output.")
    args = parser.parse_args()

    dst_folder = benchmark_gen(args.file_path, args.execute, args.result_file)