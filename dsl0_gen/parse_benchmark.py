import re
import srsly


def parse_benchmark_file(file_path):
    # Read the file
    with open(file_path, "r") as file:
        content = file.read()

    # Split by the separator markers
    function_blocks = re.split(r"/\*{10,}\*/", content)

    # Process each function block
    functions = []
    for block in function_blocks:
        if not block.strip():
            continue

        # Extract parameter headers and function body
        param_headers = []
        lines = block.strip().split("\n")
        code_start_idx = 0

        # Parse the parameter headers
        for i, line in enumerate(lines):
            param_match = re.match(r"//\s+(\w+)\s+(\w+)\s+(\d+)", line)
            if param_match:
                param_name, param_type, param_size = param_match.groups()
                param_headers.append((param_name, param_type, int(param_size)))
            elif line.startswith("void slow_performance"):
                code_start_idx = i
                break

        # Extract function body
        function_body = "\n".join(lines[code_start_idx:])

        # Add to the list of functions
        functions.append({"params": param_headers, "code": function_body})

    return functions


def main():
    file_path = "benchmark_L.c"
    functions = parse_benchmark_file(file_path)

    # Print the parsed results
    for i, func in enumerate(functions):
        print(f"Function {i+1}:")
        print("Parameters:")
        for param in func["params"]:
            print(f"  {param}")
        print("Code:")
        print(f"  {func['code'][:100]}...")  # Print first 100 chars of code
        print()
    srsly.write_jsonl("benchmark_L_100.jsonl", functions)


if __name__ == "__main__":
    main()
