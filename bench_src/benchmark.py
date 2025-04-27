import subprocess
import os
import re

def benchmark(folder_path):
    try:
        cmd = 'make && ./benchmark'

        process = subprocess.Popen(
            cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, cwd=folder_path
        )

        stdout, stderr = process.communicate()

        output_text = stdout.decode('utf-8')
        error_text = stderr.decode('utf-8')

        wrong_matches = re.findall(r'The result of the (\d+)th function is not correct', output_text)

        for match in wrong_matches:
            print(f"{match}th function is not correct.")

        slow_match = re.search(r'Running: slow_performance\s+([0-9.]+) cycles', output_text)
        fast_match = re.search(r'Running: max_performance\s+([0-9.]+) cycles', output_text)

        slow_cycles = float(slow_match.group(1)) if slow_match else None
        fast_cycles = float(fast_match.group(1)) if fast_match else None

        if slow_cycles is None or fast_cycles is None:
            raise ValueError("Could not find performance data in the output.")

        print(f"slow_performance cycles: {slow_cycles}")
        print(f"max_performance cycles: {fast_cycles}")
        print(f"speed up ratio: {fast_cycles/slow_cycles}")

    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    folder_path = './'
    benchmark(folder_path)